#ifndef _KTIMER_LIST_H
#define _KTIMER_LIST_H
#include <list>
namespace fsk{
	using namespace std;
	class ktimer_list
	{
	public:
		ktimer_list();
		~ktimer_list();

	public:
		virtual int schedule(ktask *t, const ktimeval &delay, const ktimeval &interval);

		virtual int cancel(int timerid);

		virtual int expire(const ktimeval &now);

		virtual int first(ktimeval &tv);

		/*
		*	reset the interval of timer @timerid
		*@timerid: which timer to reset interval
		*@interval: new interval to set
		*return:
		*	0--on success, <0--timer not exist
		*/
		virtual int reset(int timerid, const ktimeval &interval);

	private:
		int schedule(ktimeritem *item);

	private:
		//timers sorted by expire time point ascend
		list<ktimeritem*> _timers;
	};
}
#endif

