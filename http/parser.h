#pragma once
#include "cube\http\header.h"
BEGIN_CUBE_HTTP_NS
class parser {
public:
	static int parse_header(const std::string &str, header *header, std::string *err = 0);
};

END_CUBE_HTTP_NS
