#include "cube/timer/ktimer_os.h"
#include <sys/time.h>

namespace fsk{
	int gettimeofday(ktimeval *now)
	{
		struct timeval tm;
		int err = ::gettimeofday(&tm, 0);
		if(err != 0)
			return -1;

		now->sec(tm.tv_sec);
		now->usec(tm.tv_usec);

		return 0;
	}
}
