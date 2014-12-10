#include "cube/timer/ktimer_item.h"
namespace fsk{
	ktimeval::ktimeval():_tv_sec(0),_tv_usec(0)
	{

	}

	ktimeval::ktimeval(const ktimeval &tv)
	{
		_tv_sec = tv._tv_sec;
		_tv_usec = tv._tv_usec;
	}

	ktimeval::ktimeval(time_t tv_sec, time_t tv_usec/* =0 */)
	{
		_tv_sec = tv_sec;
		_tv_usec = tv_usec;
		normalize();
	}

	ktimeval::~ktimeval()
	{

	}

	const ktimeval ktimeval::operator+(const ktimeval &tv) const
	{
		ktimeval ret;
		ret._tv_sec = _tv_sec + tv._tv_sec;
		ret._tv_usec = _tv_usec + tv._tv_usec;

		ret.normalize();

		return ret;
	}

	const ktimeval ktimeval::operator-(const ktimeval &tv) const
	{
		ktimeval ret;
		ret._tv_sec = _tv_sec - tv._tv_sec;
		ret._tv_usec = _tv_usec - tv._tv_usec;

		ret.normalize();

		return ret;
	}

	void ktimeval::normalize()
	{/*!!we do not consider overflow now!!*/
		const static time_t microsec_per_sec = 1000000;

		/*first normalize the micro seconds*/
		if(_tv_usec <= -microsec_per_sec)
		{
			while(_tv_usec <= -microsec_per_sec)
			{
				_tv_sec = _tv_sec - 1;
				_tv_usec += microsec_per_sec;
			}
		}
		else if(_tv_usec >= microsec_per_sec)
		{
			while(_tv_usec >= microsec_per_sec)
			{
				_tv_sec = _tv_sec + 1;
				_tv_usec -= microsec_per_sec;
			}
		}
		else
			;

		/*then normalize the seconds*/
		if(_tv_sec > 0)
		{
			if(_tv_usec < 0)
			{
				_tv_sec = _tv_sec - 1;
				_tv_usec = microsec_per_sec + _tv_usec;
			}
		}
		else if(_tv_sec < 0)
		{
			if(_tv_usec > 0)
			{
				_tv_sec = _tv_sec + 1;
				_tv_usec = _tv_usec - microsec_per_sec;
			}
		}
		else
			;
	}

	ktimeritem::ktimeritem(int timerid, ktask *t, const ktimeval &expire, const ktimeval &interval): 
	_timerid(timerid), _task(t), _expire(expire), _interval(interval)
	{

	}

	ktimeritem::~ktimeritem()
	{

	}
}
