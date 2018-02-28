#pragma once
#define BEGIN_CUBE_SVR_NS namespace cube { namespace svr{
#define END_CUBE_SVR_NS }}

#define BEGIN_CUBE_SVR_TCP_NS namespace cube { namespace svr{ namespace tcp {
#define END_CUBE_SVR_TCP_NS }}}

#define BEGIN_CUBE_SVR_HTTP_NS namespace cube { namespace svr{ namespace http {
#define END_CUBE_SVR_HTTP_NS }}}

BEGIN_CUBE_SVR_NS
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef __int64	int64;
typedef unsigned __int64 uint64;
END_CUBE_SVR_NS