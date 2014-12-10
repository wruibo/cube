#ifndef _KTIMER_ITEM_H
#define _KTIMER_ITEM_H
#include "ktask.h"

namespace fsk{
	class ktimeval{
	public:
		/*constructors*/
		ktimeval();
		ktimeval(const ktimeval &tv);
		ktimeval(time_t tv_sec, time_t tv_usec=0);

		~ktimeval();

		void normalize();

		const ktimeval operator+(const ktimeval &tv) const;

		const ktimeval operator-(const ktimeval &tv) const;


		/*set & get time value*/
		inline void sec(const time_t s)
		{
			_tv_sec = s;
		}

		inline const time_t sec() const
		{
			return _tv_sec;
		}

		inline void usec(const time_t us)
		{
			_tv_usec = us;
		}

		inline const time_t usec() const
		{
			return _tv_usec;
		}

		/*rewrite the operators of time value class*/
		inline bool operator==(const ktimeval &tv) const
		{
			return _tv_sec==tv._tv_sec && _tv_usec==tv._tv_usec;
		}

		inline bool operator>(const ktimeval &tv) const
		{
			return _tv_sec>tv._tv_sec || (_tv_sec==tv._tv_sec&&_tv_usec>tv._tv_usec);
		}

		inline bool operator<(const ktimeval &tv) const
		{
			return _tv_sec<tv._tv_sec || (_tv_sec==tv._tv_sec&&_tv_usec<tv._tv_usec);
		}

		inline bool operator!=(const ktimeval &tv) const
		{
			return _tv_sec!=tv._tv_sec || _tv_usec!=tv._tv_usec; 
		}

		inline time_t toms() const
		{
			return _tv_sec*1000 + _tv_usec/1000;
		}

	private:
		time_t	_tv_sec; //time in seconds
		time_t	_tv_usec; //time in micro seconds
	};

	class ktimeritem{
	public:
		ktimeritem(int timerid, ktask *t, const ktimeval &expire, const ktimeval &interval);
		~ktimeritem();

		inline const int timerid() const
		{
			return _timerid;
		}

		inline void timerid(const int id)
		{
			_timerid = id;
		}

		inline ktask * task() const
		{
			return _task;
		}

		inline const ktimeval& expire() const
		{
			return _expire;
		}

		inline void expire(const ktimeval& next)
		{
			_expire = next;
		}

		inline const ktimeval& interval() const
		{
			return _interval;
		}

		inline void interval(const ktimeval &interval)
		{
			_interval = interval;
		}

		inline bool repeat() const
		{
			if(_interval != ktimeval(0, 0))
				return true;
			return false;
		}

	private:
		//timer item id
		int _timerid;
		//task to execute when timer expired
		ktask *_task;
		//next expire time point
		ktimeval _expire;
		//timer interval, set to 0 if one time task
		ktimeval _interval;
	};
}
#endif
