#pragma once
#include <string>
#include <WinSock2.h>
#define BEGIN_CUBE_NET_NS namespace cube { namespace net{
#define END_CUBE_NET_NS }}

//socket handle
#ifndef socket_t
#define socket_t uint
#endif // !socket_t


BEGIN_CUBE_NET_NS
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef __int64	int64;
typedef unsigned __int64 uint64;
END_CUBE_NET_NS