#ifndef _CUTE_TIMER_ITEM_H
#define _CUTE_TIMER_ITEM_H
#include "cute/timer/task.h"

#define check_ret(s, e, v, r) do {if(v!=-1 && (v<s || v>e))	return r; } while (0);
#define check_up(c, s) (c==s || s==-1)

namespace cute{
	namespace timer{	
		/*time define*/
		const int FIRST_MINUTE = 0;
		const int LAST_MINUTE = 59;

		const int FIRST_HOUR = 0;
		const int LAST_HOUR = 23;

		const int FIRST_MDAY = 1;
		const int LAST_MDAY = 31;

		const int FIRST_MON = 1;
		const int LAST_MON = 12;

		const int FIRST_WDAY = 1;
		const int LAST_WDAY = 7;

		/*crontab task item structure*/
		class item{
		public:
			item():_tid(-1),_ref(0),_t(0),_min(-1),_hour(-1),_mday(-1),_mon(-1),_wday(-1)
			{

			}

			item(int tid, task *t, int min, int hour, int mday, int mon, int wday):
			_tid(tid),_ref(0),_t(t),_min(-1),_hour(-1),_mday(-1),_mon(-1),_wday(-1)
			{
				if(wday != -1)
				{
					_wday = wday;
					_mon = -1;
					_mday = -1;
					_hour = FIRST_HOUR;
					_min = FIRST_MINUTE;
				}

				if(mon != -1)
				{
					_mon = mon;
					_mday = FIRST_MDAY;
					_hour = FIRST_HOUR;
					_min = FIRST_MINUTE;
				}

				if(mday != -1)
				{
					_mday = mday;
					_hour = FIRST_HOUR;
					_min = FIRST_MINUTE;
				}

				if(hour != -1)
				{
					_hour = hour;
					_min = FIRST_MINUTE;
				}

				if(min != -1)
					_min = min;
			}

			~cronitem_t()
			{

			}

		public:
			int _tid; //task id of crontab task item
			int _ref; //reference number of the task
			task *_t; //crontab task to run

			int _min; //minute of hour
			int _hour; //hour of day
			int _mday; //day of month
			int _mon; //month of year
			int _wday; //day of week
		};
	}
}
#endif

