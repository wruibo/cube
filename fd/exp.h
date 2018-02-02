#pragma once
#include "cube\fd\def.h"
#include <exception>
BEGIN_CUBE_FD_NS
//cube exception
class cexception : public std::exception {
public:
	cexception() : _msg("unkown exception") {}
	explicit cexception(const char *format, ...);
	virtual ~cexception() {}

	char const* what() const;

public:
	std::string _msg;
};

template<class T> void throw_assign(std::string *dest, const std::string &val) {
	if (dest != 0) {
		*dest = val;
	} else {
		throw T(val.c_str());
	}
}
END_CUBE_FD_NS
