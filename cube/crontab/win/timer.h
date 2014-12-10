#ifndef _WIN_KTIMER_H
#define _WIN_KTIMER_H
#include <windows.h>
#include <process.h>
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
		static unsigned __stdcall thread_timer(void *arg);

	private:
		//actual timer instance
		timer_type _timer;

		//lock for using the timer
		CRITICAL_SECTION  _cs;

		//condition variable for timer thread
		HANDLE _cond;

		/*variable for timer thread*/
		bool _stop_timer_thread;
		unsigned int _id_thread_timer;
		HANDLE _hthread_timer;
	};

	template<class timer_type>
	ktimer<timer_type>::ktimer():
		_stop_timer_thread(true),
		_id_thread_timer(-1),
		_hthread_timer(NULL)
	{
	}

	template<class timer_type>
	ktimer<timer_type>::~ktimer()
	{
	}

	template<class timer_type>
	int ktimer<timer_type>::initialize()
	{
		/*initialize critical section & condition variable*/
		InitializeCriticalSection(&_cs);
		_cond = CreateEvent(NULL, FALSE, FALSE, NULL);
		if(_cond == NULL)
			return -1;

		/*start timer thread*/
		unsigned int thread_id = -1;
		_stop_timer_thread = false;
		_hthread_timer = (HANDLE*)_beginthreadex(0, 0, thread_timer, this, 0, &thread_id);
		if(_hthread_timer == NULL)
			return -1;
		_id_thread_timer = thread_id;

		return 0;
	}

	template<class timer_type>
	int ktimer<timer_type>::schedule(ktask *t, const ktimeval &delay, const ktimeval &interval)
	{
		EnterCriticalSection(&_cs);
	
		/*schedule the timer task first*/
		int timerid = _timer.schedule(t, delay, interval);
		
		/*wake up the timer thread*/
		SetEvent(_cond);

		LeaveCriticalSection(&_cs);

		return timerid;
	}

	template<class timer_type>
	int ktimer<timer_type>::cancel(int timerid)
	{
		EnterCriticalSection(&_cs);
		int err = _timer.cancel(timerid);
		LeaveCriticalSection(&_cs);

		return err;
	}

	template<class timer_type>
	int ktimer<timer_type>::reset(int timerid, const ktimeval &interval)
	{
		EnterCriticalSection(&_cs);
		int err = _timer.reset(timerid, interval);
		LeaveCriticalSection(&_cs);

		return err;
	}

	template<class timer_type>
	int ktimer<timer_type>::destroy()
	{
		/*stop the timer thread first*/
		_stop_timer_thread = true;
		SetEvent(_cond);

		DWORD res = WaitForSingleObject(_hthread_timer, INFINITE);
		if(res != WAIT_OBJECT_0)
			return -1;

		/*delete the critical section & condition variable*/
		DeleteCriticalSection(&_cs);
		CloseHandle(_cond);

		return 0;
	}

	template<class timer_type>
	int ktimer<timer_type>::cond_wait()
	{
		int err = 0;
		ktimeval tv;
		
		EnterCriticalSection(&_cs);
		err = _timer.first(tv);
		LeaveCriticalSection(&_cs);

		if(err != 0)
		{
			DWORD res = WaitForSingleObject(_cond, INFINITE);
			if(res != WAIT_OBJECT_0)
				return -1;
		}
		else
		{
			ktimeval now;
			gettimeofday(&now);
			ktimeval sleeptv = tv-now;
			if(sleeptv > ktimeval(0, 0))
			{
				DWORD res = WaitForSingleObject(_cond, (DWORD)sleeptv.toms());
				if(res != WAIT_OBJECT_0 || res != WAIT_TIMEOUT)
					return -1;
			}
		}

		return 0;
	}

	template<class timer_type>
	int ktimer<timer_type>::expire_all()
	{
		EnterCriticalSection(&_cs);

		ktimeval now;
		gettimeofday(&now);

		int num = _timer.expire(now);

		LeaveCriticalSection(&_cs);

		return num;
	}

	template<class timer_type>
	unsigned ktimer<timer_type>::thread_timer(void *arg)
	{
		ktimer<timer_type> *timer = (ktimer<timer_type>*)arg;
		while(!timer->_stop_timer_thread)
		{
			//first wait
			timer->cond_wait();

			//timer up or new timer task added
			timer->expire_all();
		}

		_endthreadex(0);
		return 0;
	}
}
#endif
