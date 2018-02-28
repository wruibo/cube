#include "cube\str\str.h"
BEGIN_CUBE_STR_NS
bool empty(const char* str) {
	if (str != 0 && *str == 0) {
		return true;
	}
	return false;
}
END_CUBE_STR_NS
