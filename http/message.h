#pragma once
#include "cube\http\entity.h"
#include "cube\http\header.h"
#include <list>
BEGIN_CUBE_HTTP_NS
class message {
public:
	message() : _start_line(""){}
	virtual ~message() {}

private:
	//http message start line
	std::string _start_line;
	//http message headers
	std::list<std::string> _header_lines;
	//http message body
};
END_CUBE_HTTP_NS
