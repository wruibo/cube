#ifndef _KTIMER_BASE_H
#define _KTIMER_BASE_H
#include "ktimer_item.h"

namespace fsk{
	class ktimer_base
	{
	public:
		/*
		*	schedule a timer task @t with delay time @delay of @interval
		*@t: timer task to execute when timer expire
		*@delay: delay time for the first time to execute the task
		*@interval: interval of the timer task, set to 0 for one time execute
		*return:
		*	timer id which is large than 0, or <0 when schedule timer failed
		*/
		virtual int schedule(ktask *t, const ktimeval &delay, const ktimeval &interval) = 0;

		/*
		*	cancel a timer with specified timer id
		*@timerid: which timer to cancel
		*return:
		*	0--on success, <0--timer id not exist
		*/
		virtual int cancel(int timerid) = 0;

		/*
		*	expire timer, if the timer expire time point is not more than @now
		*then the timer is expired, and relate task will be execute.
		*@now: current time point
		*return:
		*	number of timer expired
		*/
		virtual int expire(const ktimeval &now) = 0;

		/*
		*	get the earliest expire time point of all timers
		*@tv: the earliest expire time point
		*return:
		*	0--@tv is set, <0--no timers
		*/
		virtual int first(ktimeval &tv) = 0;

		/*
		*	reset the interval of timer @timerid
		*@timerid: which timer to reset interval
		*@interval: new interval to set
		*return:
		*	0--on success, <0--timer not exist
		*/
		virtual int reset(int timerid, const ktimeval &interval) = 0;
	};
}
#endif
