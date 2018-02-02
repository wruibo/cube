#pragma once
#include "cube\http\uri.h"
#include "cube\http\param.h"
#include "cube\http\version.h"
BEGIN_CUBE_HTTP_NS
//request query line class
//data: GET /path?param HTTP/1.1\r\n
class query {
public:
	query() : _method("") {}
	virtual ~query() {}

	//pack/parse query line with data string
	std::string pack() const;
	int parse(const char *data, std::string *err = 0);

	/*
	*	get query items parsed from data
	*/
	const std::string &method() const { return _method; }
	const std::string &path() const { return _uri.path(); }
	const params &params() const { return _uri.params(); }
	const std::string &fragment() const { return _uri.fragment(); }
	const std::string &version() const { return _version.code(); }

private:
	//request method
	std::string _method;
	//request uri
	http::uri _uri;
	//request http version
	http::version _version;
};
END_CUBE_HTTP_NS
