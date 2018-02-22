#pragma once
#include "cube\http\entity.h"
#include "cube\http\header.h"
#include <list>
#include <memory>
BEGIN_CUBE_HTTP_NS
class message {
public:
	message() : _start_line(""), _entity(0) {
	}

	virtual ~message() {
		if (_entity != 0) {
			delete _entity;
			_entity = 0;
		}
	}

public:
	const std::string &get_start_line() {
		return _start_line;
	}

protected:
	//message start line
	std::string _start_line;
	//message header lines
	std::list<std::string> _header_lines;
	//message entity object
	http::entity * _entity;
};
END_CUBE_HTTP_NS
