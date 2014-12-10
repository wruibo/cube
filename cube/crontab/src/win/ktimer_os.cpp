#include "cube/timer/ktimer_os.h"
#include <Windows.h>

namespace fsk{
	int gettimeofday(ktimeval *now)
	{
		/*get the system time as file time*/
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);

		/*translate the file time to time stamp value*/
		ULARGE_INTEGER ns100;
		ns100.HighPart = ft.dwHighDateTime;
		ns100.LowPart = ft.dwLowDateTime;

		ULARGE_INTEGER adj;
		adj.HighPart = 0x19db1de;
		adj.LowPart = 0xd53e8000;

		ns100.QuadPart -= adj.QuadPart;

		now->sec(ns100.QuadPart/10000000);
		now->usec((ns100.QuadPart%10000000)/10);

		return 0;
	}
}
