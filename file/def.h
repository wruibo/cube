#pragma once
#include <string>
#define BEGIN_CUBE_FD_NS namespace cube {namespace fd {
#define END_CUBE_FD_NS }}

BEGIN_CUBE_FD_NS
typedef unsigned char byte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef __int64	int64;
typedef unsigned __int64 uint64;

//find result for find file method
typedef class findres {
public:
	findres(const std::string& name, int64 size, int64 ctime, int64 atime, int64 wtime, unsigned attrib) :
		name(name), size(size), ctime(ctime), atime(atime), wtime(wtime), attrib(attrib) {
	}
	~findres() {}

	std::string name; //file name
	int64  size; //file size
	int64  ctime; // create time, -1 for FAT file systems
	int64  atime; // last access time, -1 for FAT file systems
	int64  wtime; //last write time
	unsigned  attrib; //file attribute
} findres_t;

//file stat results
typedef class filestat {
public:
	filestat() {}
	filestat(ushort mode, int64 size, int64 ctime, int64 atime, int64 wtime) :
		mode(mode), size(size), ctime(ctime), atime(atime), mtime(mtime) {
	}
	~filestat() {}

	ushort mode; //file mode
	int64   size; //file size
	int64	ctime; // create time
	int64	atime; // last access time
	int64	mtime; //last modify time
} filestat_t;
END_CUBE_FD_NS
