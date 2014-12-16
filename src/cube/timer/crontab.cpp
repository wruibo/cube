#include "cube/timer/crontab.h"

namespace cube{
	namespace timer{
		int crontab::_global_cron_id = 0;
		crontab::crontab(void)
		{
		}

		crontab::~crontab(void)
		{

		}

		int crontab::init()
		{
			/*start cron task thread*/
			int err = _thread.start(this);
			if(err != 0)
				return -1;

			return 0;
		}

		int crontab::schedule(task *t, int min/* =-1 */, int hour/* =-1 */, int mday/* =-1 */, int mon/* =-1 */, int wday/* =-1 */)
		{
			cube::thread::scope_lock<cube::thread::mutex> lock(_mutex);
			/*increase the global crontab item id*/
			_global_cron_id++;

			/*generate the cron item*/
			_items.push_back(new cron_t(_global_cron_id,t,min,hour,mday,mon,wday));

			return _global_cron_id;
		}

		int crontab::remove(int tid)
		{
			cube::thread::scope_lock<cube::thread::mutex> lock(_mutex);
			std::list<cron_t*>::iterator iter=_items.begin(), iterend=_items.end();
			while(iter != iterend)
			{
				if((*iter)->id() == tid)
				{
					delete *iter;
					_items.erase(iter++);
					break;
				}
				else
					iter++;
			}

			return 0;
		}

		int crontab::destroy()
		{
			/*stop the crontab thread first*/
			_thread.stop();
			
			/*clear the crontab items*/
			this->clear();

			return 0;
		}

		int crontab::clear()
		{
			cube::thread::scope_lock<cube::thread::mutex> lock(_mutex);
			std::list<cron_t*>::iterator iter=_items.begin(), iterend=_items.end();
			while(iter != iterend)
			{
				delete *iter;
				iter++;
			}
			_items.clear();

			return 0;
		}		

		int crontab::wait()
		{
			/*get the current time*/
			time_t now = time(0);
			struct tm *t = localtime(&now);

			/*wait for the first second of a minute*/
			cube::thread::sleep(1000*(60-t->tm_sec));
			return 0;
		}

		int crontab::check()
		{
			/*get the current time*/
			time_t now = time(0);
			struct tm *t = localtime(&now);
			
			cube::thread::scope_lock<cube::thread::mutex> lock(_mutex);
			std::list<cron_t*>::iterator iter=_items.begin(), iterend=_items.end();
			while(iter != iterend)
			{
			
				iter++;
			}

			return 0;
		}

		void crontab::loop()
		{
			this->wait();
			
			this->check();
		}
	}
}