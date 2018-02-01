#pragma once
#define BEGIN_CUBE_LOG_NS namespace cube { namespace log{
#define END_CUBE_LOG_NS }}

BEGIN_CUBE_LOG_NS
//log output option
typedef enum class out { console = 0, file = 1 } out;
//cut option for file output 
typedef enum class cut { none = 0, sized = 1, daily = 2 } cut;

//log level option
typedef enum class level { debug = 0, info = 1, warn = 2, error = 3, fatal = 4 } level;

typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef __int64	int64;
typedef unsigned __int64 uint64;
END_CUBE_LOG_NS
