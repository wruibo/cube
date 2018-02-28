#include "cube\log\util.h"
#include "cube\log\strip.h"
#include <io.h>
#include <time.h>
#include <direct.h>
#include <stdarg.h>
BEGIN_CUBE_LOG_NS
int today() {
	time_t t = ::time(0);
	struct ::tm *tt = ::localtime(&t);
	return tt->tm_mday;
}

std::string now(const char* format) {
	time_t t = ::time(0);
	struct ::tm *tt = ::localtime(&t);;

	const int bufsz = 128;
	char buf[bufsz] = { 0 };
	strftime(buf, bufsz - 1, format, tt);
	return std::string(buf);
}

std::string format(const char *format, ...) {
	/*this buffer is properly not safe*/
	static const int BUFSZ = 1024;
	char buf[BUFSZ] = { 0 };

	va_list va;
	va_start(va, format);
	vsnprintf(buf, BUFSZ, format, va);
	va_end(va);

	return std::string(buf);
}

bool fexist(const std::string &path) {
	if (_access(path.c_str(), 0) == 0) {
		return true;
	}
	return false;
}

int fsize(const std::string &path, size_t &sz) {
	int fd = ::_open(path.c_str(), 0);
	if (fd < 0)
		return -1;

	long len = _filelength(fd);
	::_close(fd);

	if (len == -1)
		return -1;

	sz = len;
	return 0;
}

bool isdir(const std::string &path) {
	struct _stat stat;
	if (_stat(path.c_str(), &stat) == 0 && (stat.st_mode&S_IFDIR) == S_IFDIR) {
		return true;
	}

	return false;
}

int mkdir(const std::string &path) {
	int err = _mkdir(path.c_str());
	if (err != 0 && errno != EEXIST) {
		return -1;
	}
	return 0;
}

int mkdirs(const std::string &path) {
	//check path parameter
	if (path == "") {
		return 0;
	}

	//directory already exist
	if (fexist(path) && isdir(path)) {
		return 0;
	}

	//get parent directory
	size_t pos1 = path.find_last_of('/'), pos2 = path.find_last_of('\\'), lastpos = std::string::npos;
	if (pos1 != std::string::npos && pos2 != std::string::npos) {
		size_t lpos = pos1 < pos2 ? pos1 : pos2, rpos = pos1 < pos2 ? pos2 : pos1, pos = lpos + 1;
		while (pos < rpos) {
			if (path[pos] != '\\' && path[pos] != '/')
				break;
			pos++;
		}
		lastpos = pos < rpos ? rpos : lpos;
	} else if (pos1 != std::string::npos)
		lastpos = pos1;
	else if (pos2 != std::string::npos)
		lastpos = pos2;
	else
		lastpos = std::string::npos;

	if (lastpos != std::string::npos) {
		// create parent directory
		std::string parent_path = path.substr(0, lastpos);
		int err = mkdirs(parent_path);
		if (err != 0)
			return -1;
	}

	//create current directory
	return mkdir(path);
}

std::string mkpath(const std::string &parent, const std::string &child) {
	const char* SEP = "\\";

	//trim parent's and child's left path seperators, add seperator between them
	return rstrip(rstrip(parent), SEP) + SEP + lstrip(rstrip(child), SEP);
}
END_CUBE_LOG_NS
