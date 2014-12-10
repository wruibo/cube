#include "cube/timer/linux/kcrontab.h"
#include <algorithm>
#include <unistd.h>

namespace fsk{
	kcrontab* kcrontab::_inst = NULL;
	kcrontab::kcrontab(void):_stop_check_thread(true),_stop_job_thread(true)
	{
	}

	kcrontab::~kcrontab(void)
	{

	}

	kcrontab * kcrontab::instance()
	{
		if(_inst == NULL)
			_inst = new kcrontab();
		return _inst;
	}

	int kcrontab::initialize()
	{
		/*initialize the task items & job items mutex*/
		int err = pthread_mutex_init(&_cs_items, 0);
		if(err != 0)
			return -1;

		err = pthread_mutex_init(&_cs_jobs, 0);
		if(err != 0)
			return -1;

		unsigned int thread_id = -1;
		/*start task items processing thread*/
		_stop_check_thread = false;
		err = pthread_create(&_hthread_items, 0, thread_check_func, this);
		if(err != 0)
			return -1;

		/*start job items processing thread*/
		_stop_job_thread = false;
		err = pthread_create(&_hthread_jobs, 0, thread_job_func, this);
		if(err != 0)
			return -1;

		return 0;
	}

	int kcrontab::schedule(ktask *t, int min/* =-1 */, int hour/* =-1 */, 
		int mday/* =-1 */, int mon/* =-1 */, int wday/* =-1 */)
	{
		/*check the cron arguments first*/
		check_ret(FIRST_MINUTE, LAST_MINUTE, min, -1);
		check_ret(FIRST_HOUR, LAST_HOUR, hour, -1);
		check_ret(FIRST_MDAY, LAST_MDAY, mday, -1);
		check_ret(FIRST_MON, LAST_MON, mon, -1);
		check_ret(FIRST_WDAY, LAST_WDAY, wday, -1);

		/*unique task id counter*/
		static int g_tid = 0; 

		/*lock task items*/
		pthread_mutex_lock(&_cs_items);	
		g_tid++; //add unique task id

		/*generate the cron item*/
		cronitem_t *item = new cronitem_t(g_tid,t,min,hour,mday,mon,wday);
		_items.push_back(item);

		pthread_mutex_unlock(&_cs_items);

		return g_tid;
	}

	int kcrontab::remove(int tid)
	{
		pthread_mutex_lock(&_cs_items);
		list<cronitem_t*>::iterator iter=_items.begin(), iterend=_jobs.end();
		while(iter != iterend)
		{
			if((*iter)->_tid == tid)
			{
				del_job(*iter);
				_items.erase(iter++);
			}
			else
				iter++;
		}
		pthread_mutex_unlock(&_cs_items);

		return 0;
	}

	int kcrontab::remove(ktask *t)
	{
		pthread_mutex_lock(&_cs_items);
		list<cronitem_t*>::iterator iter=_items.begin(), iterend=_jobs.end();
		while(iter != iterend)
		{
			if((*iter)->_t == t)
			{
				del_job(*iter);
				_items.erase(iter++);
			}
			else
				iter++;
		}
		pthread_mutex_unlock(&_cs_items);

		return 0;
	}

	int kcrontab::destroy()
	{
		/*stop the check thread first*/
		_stop_check_thread = true;
		int res = pthread_join(_hthread_items, 0);
		if(res != 0)
			return -1;

		/*stop the job thread second*/
		_stop_job_thread = true;
		res = pthread_join(_hthread_items, 0);
		if(res != 0)
			return -1;

		/*clear the jobs & items*/
		clear_jobs();
		clear_items();

		/*free the critical section*/
		pthread_mutex_destroy(&_cs_jobs);
		pthread_mutex_destroy(&_cs_items);

		return 0;
	}

	int kcrontab::add_job(cronitem_t *item)
	{
		pthread_mutex_lock(&_cs_jobs);
		list<cronitem_t*>::iterator iter = std::find(_jobs.begin(), _jobs.end(), item);
		if(iter == _jobs.end())
			_jobs.push_back(item);
		pthread_mutex_unlock(&_cs_jobs);
		return 0;
	}

	int kcrontab::del_job(cronitem_t *item)
	{
		pthread_mutex_lock(&_cs_jobs);
		list<cronitem_t*>::iterator iter=_jobs.begin(),iterend=_jobs.end();
		while(iter != iterend)
		{
			if(*iter == item)
			{
				_jobs.erase(iter);
				break;
			}
			else
				iter++;
		}
		pthread_mutex_unlock(&_cs_jobs);

		return 0;
	}

	int kcrontab::clear_items()
	{
		pthread_mutex_lock(&_cs_items);
		list<cronitem_t*>::iterator iter=_items.begin(), iterend=_items.end();
		while(iter != iterend)
		{
			delete *iter;
			iter++;
		}
		_items.clear();
		pthread_mutex_unlock(&_cs_items);

		return 0;
	}

	int kcrontab::clear_jobs()
	{
		pthread_mutex_lock(&_cs_jobs);
		list<cronitem_t*>::iterator iter=_jobs.begin(), iterend=_jobs.end();
		while(iter != iterend)
		{
			delete *iter;
			iter++;
		}
		_jobs.clear();
		pthread_mutex_unlock(&_cs_jobs);

		return 0;
	}

	int kcrontab::cron_sleep()
	{
		time_t now = time(0);
		struct tm *t = localtime(&now);
		sleep(60-t->tm_sec);

		return 0;
	}

	int kcrontab::run_check(const time_t now)
	{
		struct tm *t = localtime(&now);
		int min = t->tm_min;
		int hour = t->tm_hour;
		int mday = t->tm_mday;
		int mon = t->tm_mon+1;
		int wday = t->tm_wday;

		pthread_mutex_lock(&_cs_items);
		list<cronitem_t*>::iterator iter=_items.begin(), iterend=_items.end();
		while(iter != iterend)
		{
			cronitem_t *item = *iter;
			if((check_up(min, item->_min) && check_up(hour, item->_hour) &&
				check_up(mday, item->_mday) && check_up(mon, item->_mon)) ||
				(check_up(wday, item->_wday) && check_up(min, item->_min) 
				&& check_up(hour, item->_hour)))
				add_job(item);
			iter++;
		}
		pthread_mutex_unlock(&_cs_items);

		return 0;
	}

	int kcrontab::run_jobs(const time_t now)
	{
		pthread_mutex_lock(&_cs_jobs);
		list<cronitem_t*>::iterator iter=_jobs.begin(), iterend=_jobs.end();
		while(iter != iterend)
		{
			(*iter)->_t->run(now);
			_jobs.erase(iter++);
		}
		pthread_mutex_unlock(&_cs_jobs);

		return 0;
	}

	void* kcrontab::thread_check_func(void *arg)
	{
		kcrontab *cronobj = (kcrontab*)arg;
		while(!cronobj->_stop_check_thread)
		{
			cronobj->cron_sleep();
			time_t now = time(0);
			cronobj->run_check(now);
		}

		pthread_exit(0);
		return 0;
	}

	void* kcrontab::thread_job_func(void *arg)
	{
		kcrontab *cronobj = (kcrontab*)arg;
		while(!cronobj->_stop_job_thread)
		{
			time_t now = time(0);
			cronobj->run_jobs(now);
			sleep(1);
		}
		pthread_exit(0);
		return 0;
	}
}
