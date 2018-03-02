#pragma once
#include "cube\http\request.h"
BEGIN_CUBE_HTTP_NS
class parser {
public:
	static int parse(const std::string &data, http::request &req);

private:
	static int parse_request_line();
	static int parse_request_header();
};
END_CUBE_HTTP_NS