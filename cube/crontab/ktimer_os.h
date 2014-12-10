#ifndef _KTIMER_OS_H
#define _KTIMER_OS_H
#include "ktimer_item.h"

namespace fsk{
	/*
	*	set the @now with current timestamp if success.
	*	seconds since Jan. 1, 1970 elapse
	*return:
	*	0--success, <0--failed, and @now is not changed
	*/
	extern int gettimeofday(ktimeval *now);
}
#endif
