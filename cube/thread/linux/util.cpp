#include "cube/thread/util.h"
#include <unistd.h>
namespace cube{
	namespace thread{
		void sleep(unsigned long milliseconds)
		{
			usleep(milliseconds*1000);
		}
	}
}

