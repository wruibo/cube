#ifndef _CUBE_TIMER_UTIL_H
#define _CUBE_TIMER_UTIL_H
#include <time.h>
#include "cube/type/type.h"
namespace cube{
	namespace timer{
		/**
		*	get the utc file time in million seconds since 1601.01.01
		*@return:
		*	million seconds of utc time since 1601.01.01
		*/
		extern uint64_t mftime(struct tm* tm = 0);

		/**
		*	get the unix timestamp in million seconds
		*@return:
		*	million seconds of utc time since 1970.01.01
		*/
		extern uint64_t mtime(struct tm* tm = 0);
	}
}
#endif
