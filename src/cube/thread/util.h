#ifndef _CUBE_THREAD_UTIL_H
#define _CUBE_THREAD_UTIL_H
namespace cube{
	namespace thread{
		/**
		*	make current thread to sleep for @milliseconds
		*/
		extern void sleep(unsigned long milliseconds);

		/**
		*	get the current thread id
		*/
		extern unsigned long get_current_thread_id();
	}
}
#endif
