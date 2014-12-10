#include "cube/timer/ktimer_list.h"
#include "cube/timer/ktimer_os.h"

namespace fsk{
	ktimer_list::ktimer_list()
	{

	}

	ktimer_list::~ktimer_list()
	{
		/*free the timer items*/
		list<ktimeritem*>::iterator iter=_timers.begin(), iterend=_timers.end();
		while(iter != iterend)
		{
			delete *iter;
			iter++;
		}
	}

	int ktimer_list::schedule(ktask *t, const ktimeval &delay, const ktimeval &interval)
	{
		/*generate timer id*/
		static int g_timerid = 0;
		g_timerid++;

		/*get current time stamp*/
		ktimeval now;
		int err = gettimeofday(&now);
		if(err != 0)
			return -1;

		/*compute the first expire time stamp & generate the timer item*/
		ktimeval expire = now + delay;
		ktimeritem *item = new ktimeritem(g_timerid, t, expire, interval);

		schedule(item);

		return g_timerid;
	}

	int ktimer_list::schedule(ktimeritem *item)
	{
		/*insert to the right position in the timer list*/
		list<ktimeritem*>::iterator iter=_timers.begin(), iterend=_timers.end();
		while(iter != iterend)
		{
			if((*iter)->expire() > item->expire())
				break;
			iter++;
		}
		_timers.insert(iter, item);

		return 0;
	}

	int ktimer_list::cancel(int timerid)
	{
		list<ktimeritem*>::iterator iter=_timers.begin(), iterend=_timers.end();

		while(iter != iterend)
		{
			if((*iter)->timerid() == timerid)
			{
				delete *iter;
				_timers.erase(iter);
				break;
			}

			iter++;
		}

		return 0;
	}

	int ktimer_list::expire(const ktimeval &now)
	{
		/*timer task expires*/
		int nexpires = 0;
		list<ktimeritem*> expires;

		/*scan the timer list from header*/
		list<ktimeritem*>::iterator iter=_timers.begin(), iterend=_timers.end();
		while(iter != iterend)
		{
			if(now < (*iter)->expire())
			{/*current timer task is not expired*/
				break;
			}
			else
			{/*current timer task has expired*/
				/*remove the expired timer task*/
				ktimeritem* item = *iter;
				_timers.erase(iter++);

				/*execute the timer task & move to expires list*/
				item->task()->run(now.sec());
				if(item->repeat())
				{
					item->expire(now+item->interval());
					expires.push_back(item);
				}
				else
					delete item;

				nexpires++;
			}
		}

		/*reschedule the expired repeat tasks*/
		iter=expires.begin(), iterend=expires.end();
		while(iter != iterend)
		{
			schedule(*iter);
			iter++;
		}

		return nexpires;
	}

	int ktimer_list::first(ktimeval &tv)
	{
		if(_timers.empty())
			return -1;

		tv = _timers.front()->expire();

		return 0;
	}

	int ktimer_list::reset(int timerid, const ktimeval &interval)
	{
		bool bexist = false;

		list<ktimeritem*>::iterator iter=_timers.begin(), iterend=_timers.end();
		while(iter != iterend)
		{
			if((*iter)->timerid() == timerid)
			{
				(*iter)->interval(interval);
				bexist = true;
				break;
			}

			iter++;
		}

		if(!bexist)//timer task not found
			return -1;

		return 0;
	}
}
