#include "cube\fd\fd.h"
#include "cube\fd\path.h"
#include "cube\str\part.h"
#include <io.h>
BEGIN_CUBE_FD_NS
////////////////////////////////////////////////file/directory class//////////////////////////////////////////////////
const char* SEP = "\\";

bool exist(const std::string &path) {
	if (_access(path.c_str(), 0) == 0) {
		return true;
	}
	return false;
}

bool isdir(const std::string &path) {
	struct _stat stat;
	if (_stat(path.c_str(), &stat) == 0 && (stat.st_mode&S_IFDIR) == S_IFDIR) {
		return true;
	}

	return false;
}

bool isfile(const std::string &path) {
	struct _stat stat;
	if (_stat(path.c_str(), &stat) == 0 && (stat.st_mode&S_IFREG) == S_IFREG) {
		return true;
	}

	return false;
}

int stat(int fd, filestat &fstat) {
	//get file stat
	struct _stat st;
	int err = _fstat(fd, &st);
	if (err != 0)
		return -1;

	//set return stat
	fstat.mode = st.st_mode;
	fstat.size = st.st_size;
	fstat.atime = st.st_atime;
	fstat.ctime = st.st_ctime;
	fstat.mtime = st.st_mtime;

	return 0;
}

int stat(const std::string &path, filestat &fstat) {
	int fd = ::_open(path.c_str(), 0);
	if (fd < 0)
		return -1;

	int err = stat(fd, fstat);
	::_close(fd);

	return err;
}

int size(int fd, size_t &sz) {
	long len = _filelength(fd);
	if (len == -1)
		return -1;
	sz = len;
	return 0;
}

size_t size(const std::string &path) {
	size_t sz = 0;
	int err = size(path, sz);
	if (err != 0) {
		throw error("file: %s, get size failed.", path.c_str());
	}

	return sz;
}

int size(const std::string &path, size_t &sz) {
	int fd = ::_open(path.c_str(), 0);
	if (fd < 0)
		return -1;

	int err = size(fd, sz);
	::_close(fd);

	return err;
}

std::string ext(const std::string &name) {
	size_t pos = name.rfind('.');
	if (pos != std::string::npos) {
		return name.substr(pos);
	}

	return "";
}

std::string name(const std::string &path) {
	std::vector<std::string> subpaths = str::part(path.c_str(), "\\/");
	if (subpaths.size() > 0) {
		return subpaths[subpaths.size() - 1];
	}

	return "";
}

std::string path(const std::string &path) {
	std::vector<std::string> subpaths = str::part(path.c_str(), "\\/");
	if (subpaths.size() > 0) {
		std::string filename = subpaths[subpaths.size() - 1];
		return path.substr(0, path.length() - filename.length());
	}
	return "";
}

std::vector<findres> find(const std::string &path, const char* spec/* = "*"*/, int attrib/* = attrib::ALL*/, bool onlyvisible/* = true*/, bool onlyname/* = true*/) {
	std::vector<findres> results;
	struct _finddata_t fdata;
	intptr_t hd = 0;

	std::string paths = path::make(path, spec);
	if ((hd = _findfirst(paths.c_str(), &fdata)) != -1) {
		do {
			if ((attrib == attrib::ALL || (fdata.attrib & (unsigned)attrib) != 0) && (onlyvisible && *fdata.name != '.')) {
				if (onlyname) {
					results.push_back(findres(fdata.name, fdata.size, fdata.time_create, fdata.time_access, fdata.time_write, fdata.attrib));
				} else {
					results.push_back(findres(path::make(path, fdata.name).c_str(), fdata.size, fdata.time_create, fdata.time_access, fdata.time_write, fdata.attrib));
				}
			}
		} while (_findnext(hd, &fdata) == 0);
		_findclose(hd);
	}

	return results;
}

std::vector<std::string> finds(const std::string &path, const char* spec/* = "*"*/, int attrib/* = attrib::ALL*/, bool onlyvisible/* = true*/, bool onlyname/* = true*/) {
	std::vector<std::string> results;
	struct _finddata_t fdata;
	intptr_t hd = 0;

	std::string paths = path::make(path, spec);
	if ((hd = _findfirst(paths.c_str(), &fdata)) != -1) {
		do {
			if ((attrib == attrib::ALL || (fdata.attrib & (unsigned)attrib) != 0) && (onlyvisible && *fdata.name != '.')) {
				if (onlyname) {
					results.push_back(fdata.name);
				} else {
					results.push_back(path::make(path, fdata.name));
				}
			}
		} while (_findnext(hd, &fdata) == 0);
		_findclose(hd);
	}
	return results;
}

std::vector<std::string> dirs(const std::string &path, bool onlyvisible/* = true*/, bool onlyname/* = true*/) {
	return finds(path, "*", attrib::DIR, onlyvisible, onlyname);
}

std::vector<std::string> files(const std::string &path, bool onlyvisible/* = true*/, bool onlyname/* = true*/) {
	return finds(path, "*", attrib::FILE, onlyvisible, onlyname);
}

END_CUBE_FD_NS
