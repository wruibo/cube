#ifndef _CUBE_TIMER_H
#define _CUBE_TIMER_H

#include "ktimer_list.h"

#ifdef WIN32
#include "win/ktimer.h"
#else
#include "linux/ktimer.h"
#endif

#endif

