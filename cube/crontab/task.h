#ifndef _CUTE_TIMER_TASK_H
#define _CUTE_TIMER_TASK_H
#include <time.h>

namespace cute{
	namespace timer{
		class task
		{
			public:
				virtual int run(const time_t now) = 0;
		};
	}
}
#endif


