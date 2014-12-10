#include "cube/thread/util.h"
#include <windows.h>
namespace cube{
	namespace thread{
		void sleep(unsigned long milliseconds)
		{
			::Sleep(milliseconds);
		}

		unsigned long get_current_thread_id()
		{
			return ::GetCurrentThreadId();
		}
	}
}