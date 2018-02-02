#pragma once
#include "cube\http\def.h"
BEGIN_CUBE_HTTP_NS
//http version class
//format: HTTP/1.1
class version {
public:
	version() : _name("HTTP"), _code("1.1") {}
	virtual ~version() {}

	//pack/parse version with data string
	std::string pack() const;
	int parse(const char *data, int sz, std::string *err = 0);

	/*
	*	get/set version items
	*/
	const std::string& name() const { return _name; }
	const std::string& code() const { return _code; }
private:
	//version name, must be "http"
	std::string _name;
	//http version code
	std::string _code;
};

END_CUBE_HTTP_NS
