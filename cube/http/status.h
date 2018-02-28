#pragma once
#include "cube\http\def.h"
BEGIN_CUBE_HTTP_NS
class status {
public:
	status() : _code(""), _reason(""), _version("1.1") {}
	virtual ~status() {}

	void code(const std::string &code) {
		_code = code;
	}

	void reason(const std::string &reason) {
		_reason = reason;
	}

private:
	//response code
	std::string _code;
	//response description
	std::string _reason;
	//http version
	std::string _version;
};
END_CUBE_HTTP_NS
