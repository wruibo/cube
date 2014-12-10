#ifndef _CUTE_TIMER_CRONTAB_H
#define _CUTE_TIMER_CRONTAB_H
#ifdef WIN32
#	include "win/crontab.h"
#else
#	include "linux/crontab.h"
#endif
#endif

