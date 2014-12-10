#ifndef _LINUX_KTIMER_H
#define _LINUX_KTIMER_H
#include <pthread.h>
#include "ktimer_os.h"

namespace fsk{
	template<class timer_type>
	class ktimer
	{
	public:
		ktimer();
		~ktimer();
		
		/*
		*	initialize timer object
		*return:
		*	0--on success, <0--error
		*/
		int initialize();

		/*
		*	schedule a timer task @t with delay time @delay of @interval
		*@t: timer task to execute when timer expire
		*@delay: delay time for the first time to execute the task
		*@interval: interval of the timer task, set to 0 for one time execute
		*return:
		*	timer id which is large than 0, or <0 when schedule timer failed
		*/
		int schedule(ktask *t, const ktimeval &delay, const ktimeval &interval);

		/*
		*	cancel a timer with specified timer id
		*@timerid: which timer to cancel
		*return:
		*	0--on success, <0--timer id not exist
		*/
		int cancel(int timerid);

		/*
		*	reset the interval of timer @timerid
		*@timerid: which timer to reset interval
		*@interval: new interval to set
		*return:
		*	0--on success, <0--timer not exist
		*/
		int reset(int timerid, const ktimeval &interval);

		/*
		* destroy the timer object
		*/
		int destroy();

	private:
		/*condition wait for expire operation*/
		int cond_wait();

		/*try to expire all time up timer tasks*/
		int expire_all();

		/*thread function for timers*/
		static void* thread_timer(void *arg);

	private:
		//actual timer instance
		timer_type _timer;

		//lock for using the timer
		pthread_mutex_t  _cs;

		//condition variable for timer thread
		pthread_cond_t _cv;

		/*variable for timer thread*/
		bool _stop_timer_thread;
		pthread_t _hthread_timer;
	};

	template<class timer_type>
	ktimer<timer_type>::ktimer():
		_stop_timer_thread(true),
		_hthread_timer(-1)
	{
	}

	template<class timer_type>
	ktimer<timer_type>::~ktimer()
	{
	}

	template<class timer_type>
	int ktimer<timer_type>::initialize()
	{
		/*initialize mutex & condition variable*/
		int err = pthread_mutex_init(&_cs, 0);
		if(err != 0)
			return -1;

		err = pthread_cond_init(&_cv, 0);
		if(err != 0)
			return -1;

		/*start timer thread*/
		_stop_timer_thread = false;
		err = pthread_create(&_hthread_timer, 0, thread_timer, this);
		if(err != 0)
			return -1;

		return 0;
	}

	template<class timer_type>
	int ktimer<timer_type>::schedule(ktask *t, const ktimeval &delay, const ktimeval &interval)
	{
		pthread_mutex_lock(&_cs);
	
		/*schedule the timer task first*/
		int timerid = _timer.schedule(t, delay, interval);
		
		/*wake up the timer thread*/
		pthread_cond_signal(&_cv);

		pthread_mutex_unlock(&_cs);

		return timerid;
	}

	template<class timer_type>
	int ktimer<timer_type>::cancel(int timerid)
	{
		pthread_mutex_lock(&_cs);
		int err = _timer.cancel(timerid);
		pthread_mutex_unlock(&_cs);

		return err;
	}

	template<class timer_type>
	int ktimer<timer_type>::reset(int timerid, const ktimeval &interval)
	{
		pthread_mutex_lock(&_cs);
		int err = _timer.reset(timerid, interval);
		pthread_mutex_unlock(&_cs);

		return err;
	}

	template<class timer_type>
	int ktimer<timer_type>::destroy()
	{
		/*stop the timer thread first*/
		_stop_timer_thread = true;
		pthread_cond_signal(&_cv);

		int err = pthread_join(_hthread_timer, 0);
		if(err != 0)
			return -1;

		/*delete the critical section & condition variable*/
		pthread_mutex_destroy(&_cs);
		pthread_cond_destroy(&_cv);

		return 0;
	}

	template<class timer_type>
	int ktimer<timer_type>::cond_wait()
	{
		pthread_mutex_lock(&_cs);
		ktimeval tv;
		int err = _timer.first(tv);
		if(err != 0)
			pthread_cond_wait(&_cv, &_cs);
		else
		{
			ktimeval now;
			gettimeofday(&now);
			if(tv > now)
			{
				struct timespec tp;
				tp.tv_sec = tv.sec();
				tp.tv_nsec = tv.usec()*1000;
				pthread_cond_timedwait(&_cv, &_cs, &tp);
			}
		}
		pthread_mutex_unlock(&_cs);

		return 0;
	}

	template<class timer_type>
	int ktimer<timer_type>::expire_all()
	{
		pthread_mutex_lock(&_cs);
		
		ktimeval now;
		gettimeofday(&now);		
		int num = _timer.expire(now);

		pthread_mutex_unlock(&_cs);

		return num;
	}

	template<class timer_type>
	void* ktimer<timer_type>::thread_timer(void *arg)
	{
		ktimer<timer_type> *timer = (ktimer<timer_type>*)arg;
		while(!timer->_stop_timer_thread)
		{
			//first wait
			timer->cond_wait();

			//timer up or new timer task added
			timer->expire_all();
		}

		pthread_exit(0);
		return 0;
	}
}
#endif

