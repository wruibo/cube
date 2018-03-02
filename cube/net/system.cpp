#include "cube\net\system.h"
#include <Windows.h>

BEGIN_CUBE_NET_NS
int get_cpu_cores() {
	SYSTEM_INFO si;
	::GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
}
END_CUBE_NET_NS