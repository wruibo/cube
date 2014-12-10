#ifndef _CUBE_TYPE_TYPE_H
#define _CUBE_TYPE_TYPE_H

#ifdef _WIN32
#include "cube/type/win/type.h"
#else
#include "cube/type/linux/type.h"
#endif

namespace cube{
	typedef unsigned char byte;
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned long ulong;
	typedef unsigned int uint;
}

#endif