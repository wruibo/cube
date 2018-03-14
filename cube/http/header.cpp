#include <algorithm>
#include "cube\log\log.h"
#include "cube\str\case.h"
#include "cube\str\part.h"
#include "cube\str\format.h"
#include "cube\http\header.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////element class///////////////////////////////////////

//////////////////////////////////////////field class///////////////////////////////////////
bool header::operator==(const header &header) const {
	return str::lower(name()) == str::lower(header.name());
}

bool header::operator==(const std::string &name) const {
	return str::lower(header::name()) == str::lower(name);
}

//////////////////////////////////////////header class/////////////////////////////////////////
std::string headers::get(const std::string &name) const {
	for (::size_t i = 0; i < _headers.size(); i++) {
		if (_headers[i] == name) {
			return _headers[i].value();
		}
	}

	return "";
}

std::string headers::get(const std::string &name, const char *default) const {
	for (::size_t i = 0; i < _headers.size(); i++) {
		if (_headers[i] == name) {
			return _headers[i].value();
		}
	}

	return std::string(default);
}

std::vector<std::string> headers::gets(const std::string &name) const {
	std::vector<std::string> res;
	for (::size_t i = 0; i < _headers.size(); i++) {
		if (_headers[i] == name) {
			res.push_back(_headers[i].value());
		}
	}
	return res;
}

int headers::add(const std::string &data) {
	//split header data
	std::vector<std::string> item;
	str::part(data.c_str(), ":", item, 2);
	if (item.size() != 2) {
		log::error("header: %s invalid header", data.c_str());
		return -1;
	}

	//add header
	add(item[0], item[1]);
	return 0;
}

void headers::add(const std::string &name, const std::string &value) {
	_headers.push_back(header(name, value));
}

void headers::set(const std::string &name, const std::string &value) {
	std::vector<header>::iterator iter = std::find(_headers.begin(), _headers.end(), name);
	if (iter != _headers.end()) {
		(*iter).value(value);
	} else {
		_headers.push_back(header(name, value));
	}
}

END_CUBE_HTTP_NS
