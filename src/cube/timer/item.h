#ifndef _CUBE_TIMER_ITEM_H
#define _CUBE_TIMER_ITEM_H
#include "cube/type/type.h"
#include "cube/timer/task.h"
#include "cube/timer/util.h"

namespace cube{
	namespace timer{
		/**
		*	timer item for record the timer task information
		*/
		class item{
		public:
			item(int id, task *t, const int delay, const int interval):_id(id), _task(t)
			{
				_expire = mtime() + delay;

				if(interval < 0)
				{
					_repeat = false;
					_interval = (uint64_t)-1;
				}
				else
				{
					_repeat = true;
					_interval = interval;
				}
			}

			~item(){}

			inline int id(){return _id;}
			inline bool is_repeat(){return _repeat;}
			inline task* get_task(){return _task;}
			inline uint64_t expire(){return _expire;}
			inline void expire(uint64_t expire){_expire = expire;}
			inline uint64_t interval(){return _interval;}
			inline void interval(int interval){_interval = interval;}

		private:
			//timer item id
			int _id;
			//repeat timer item flag
			bool _repeat;
			//task to execute when timer expired
			task *_task;
			//next expire time point
			uint64_t _expire;
			//timer interval, set to 0 if one time task
			uint64_t _interval;
		};

		/*data struct for cron task*/
		class cron_t{
		public:
			cron_t(int id, task *t, int min, int hour, int mday, int mon, int wday):
			  _id(id),_task(t),_min(min),_hour(hour),_mday(mday),_mon(mon),_wday(wday)
			{		
			}

			~cron_t()
			{
			}

			inline int id(){return _id;}

		private:
			int _id; //id of the cron task
			task *_task; //cron task

			int _min; //minute of hour
			int _hour; //hour of day
			int _mday; //day of month
			int _mon; //month of year
			int _wday; //day of week
		};
	}
}
#endif
