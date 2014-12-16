#include "cube/timer/util.h"
#include <Windows.h>

namespace cube{
	namespace timer{

		/**
		*	translate the "struct tm" to "SYSTEMTIME"
		*/
		SYSTEMTIME tm2systime(struct tm* tm)
		{
			SYSTEMTIME st;
			st.wYear = tm->tm_year;
			st.wMonth = tm->tm_mon+1;
			st.wDay = tm->tm_mday;
			st.wDayOfWeek = tm->tm_wday;
			st.wHour = tm->tm_hour;
			st.wMinute = tm->tm_min;
			st.wSecond = tm->tm_sec;
			st.wMilliseconds = 0;

			return st;
		}

		/**
		*	get the file time in million seconds at 1970.1.1
		*/
		uint64_t mftime19700101()
		{
			struct tm t1970;
			memset(&t1970, 0, sizeof(struct tm));

			t1970.tm_year = 1970;
			t1970.tm_mon = 0;
			t1970.tm_mday = 1;
			
			return mftime(&t1970);
		}

		uint64_t mftime(struct tm* tm/* = 0*/)
		{
			FILETIME ftm;
			if(tm != 0){
				SYSTEMTIME st = tm2systime(tm);
				SystemTimeToFileTime(&st, &ftm);
			}else{
				GetSystemTimeAsFileTime(&ftm);
			}
			return *((uint64_t*)&ftm)/10000;
		}

		uint64_t mtime(struct tm* tm/* = 0*/)
		{
			return mftime()-mftime19700101();
		}
	}
}
