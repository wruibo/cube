#ifndef _LINUX_KCRONTAB_H
#define _LINUX_KCRONTAB_H
#include <list>
#include <pthread.h>
#include "kcronitem.h"

namespace fsk{
	using namespace std;

	/*cron table class, singleton mode*/
	class kcrontab
	{
	public:
		virtual ~kcrontab(void);

		/*
		*	get the singleton instance of kernel cron table
		*/
		static kcrontab *instance();
		
		/*
		*	initialize the cron table object
		*
		*return:
		*	0--success, <0--failed
		*/
		int initialize();

		/*
		*	schedule a cron task, if the time item value set with -1 then the
		*time item is ignored.
		*
		*@param t task to schedule
		*@param min minute value of an hour for running the task, 0~59
		*@param hour hour value of a day for running the task, 0~23
		*@param mday day value of a month for running the task, 1~31
		*@param mon month value of a year for running the task, 1~12
		*@param wday day value of a week for running the task, 1~7
		*
		*return:
		*	task id in the cron tables or <0 indicate an error
		*/
		int schedule(ktask *t, int min=-1, int hour=-1, int mday=-1, int mon=-1, int wday=-1);

		/*
		*	remove a task from cron table by task id
		*@param tid task id return by @schedule method
		*return:
		*	0--success, <0--failed, >0--task not exist
		*/
		int remove(int tid);

		/*
		*	remove a task from cron table by task pointer
		*@param t task pointer passed to @schedule method
		*return:
		*	0--success, <0--failed, >0--task not exist
		*/
		int remove(ktask *t);

		/*
		*	destroy the cron table object
		*return:
		*	0--success, <0--failed
		*/
		int destroy();

	private:
		kcrontab(void);
		
		int add_job(cronitem_t *item);

		int del_job(cronitem_t *item);

		int clear_items();

		int clear_jobs();

		int cron_sleep();

	private:
		/*run the task item checking work*/
		int run_check(const time_t now);

		/*run the jobs which are time up in task items*/
		int run_jobs(const time_t now);

		/*thread function to check the cron task items*/
		static void* thread_check_func(void *arg);

		/*thread function to run the time up task jobs*/
		static void* thread_job_func(void *arg);

	private:
		/*singleton object*/
		static kcrontab *_inst;

		/*cron task items & lock*/
		list<cronitem_t*> _items;
		pthread_mutex_t  _cs_items;

		/*cron jobs wait to be run which item belongs to @_items*/
		list<cronitem_t*> _jobs;
		pthread_mutex_t  _cs_jobs;

		/*thread handle for cron task items*/
		pthread_t _hthread_items;
		bool _stop_check_thread;

		/*thread handle for cron job items*/
		pthread_t _hthread_jobs;
		bool _stop_job_thread;
	};
}
#endif

