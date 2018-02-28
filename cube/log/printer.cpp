#include "cube\log\util.h"
#include "cube\log\strip.h"
#include "cube\log\printer.h"
#include <iostream>
BEGIN_CUBE_LOG_NS
//////////////////////////////console printer//////////////////////////////
void console_printer::print(const char *msg) {
	std::cout << msg;
}


//////////////////////////////file printer//////////////////////////////
file_printer::file_printer(const std::string &dir, const std::string &name, log::cut ct, uint fszlimit) : _dir(dir), _name(name), _cutopt(ct), _currday(0), _fszlimit(fszlimit), _currnum(0), _currfsz(fszlimit) {

}

file_printer::~file_printer() {
	if (_file.is_open()) {
		_file.flush();
		_file.close();
	}
}

void file_printer::print(const char *msg) {
	//get new message size
	int sz = (int)strlen(msg);

	//check if need to cut file
	check_and_cut(sz);

	//write to file
	if (_file.good()) {
		_file.write(msg, sz);
		_currfsz += sz;
	}
}

void file_printer::check_and_cut(int msgsz) {
	switch (_cutopt) {
	case log::cut::none:
		if (!_file.is_open()) {
			_file.open(next_normal_file(), std::ios::out | std::ios::app);
		}
		break;
	case log::cut::sized:
		if (!_file.is_open()) {
			_file.open(next_sized_file(msgsz), std::ios::out | std::ios::app);
		} else {
			if (_currfsz + msgsz > _fszlimit) {
				_file.close();
				_file.open(next_sized_file(msgsz), std::ios::out | std::ios::app);
			}
		}
		break;
	case log::cut::daily:
		if (!_file.is_open()) {
			_file.open(next_daily_file(), std::ios::out | std::ios::app);
		} else {
			if (_currday != today()) {
				_file.close();
				_file.open(next_daily_file(), std::ios::out | std::ios::app);
			}
		}
		break;
	default:
		break;
	}
}

std::string file_printer::next_normal_file() {
	if (!fexist(_dir)) {
		mkdirs(_dir);
	}

	return mkpath(_dir, _name);
}

std::string file_printer::next_daily_file() {
	if (!fexist(_dir)) {
		mkdirs(_dir);
	}

	return mkpath(_dir, _name + "." + now("%Y%m%d"));
}

std::string file_printer::next_sized_file(int msgsz) {
	//make log directory
	if (!fexist(_dir)) {
		mkdirs(_dir);
	}

	//get next sized file path
	_currnum++;
	std::string fpath = mkpath(_dir, format("%s.%d", _name.c_str(), _currnum));
	while (true) {
		if (fexist(fpath)) {
			size_t sz = 0;
			if (fsize(fpath, sz) == 0 && sz + msgsz < _fszlimit) {
				_currfsz = sz;
				break;
			}

		} else {
			_currfsz = 0;
			break;
		}
		_currnum++;
		fpath = mkpath(_dir, format("%s.%d", _name.c_str(), _currnum));
	}

	return fpath;
}
END_CUBE_LOG_NS