#pragma once
#include "cube\util\def.h"
BEGIN_CUBE_UTIL_NS
template <class V> void safe_assign(V *dest, const V &val) {
	if (dest != 0) {
		*dest = val;
	}
}

template <class V> void safe_append(V *dest, const V &val) {
	if (dest != 0) {
		dest->append(val);
	}
}

template <class T, class V> void safe_push(T *dest, const V &val) {
	if (dest != 0) {
		dest->push_back(val);
	}
}

template<class T> void safe_delete(T *&ptr) {
	if (ptr != 0) {
		delete ptr;
		ptr = 0;
	}
}
END_CUBE_UTIL_NS
