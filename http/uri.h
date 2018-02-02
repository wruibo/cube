#pragma once
#include "cube\http\addr.h"
#include "cube\http\param.h"
BEGIN_CUBE_HTTP_NS
//uri structure
//uri->[scheme:][//authority][/path][?query][#fragment]
//authority->[host:port]
class uri {
public:
	uri() : _scheme(""), _auth(""), _path(""), _query(""), _fragment("") {}
	virtual ~uri() {}

	//pack/parse uri with data string
	std::string pack() const;
	int parse(const char *data, int sz, std::string *err = 0);

	/*
	*	get uri items
	*/
	const std::string& protocol() const { return _scheme; }
	const std::string& scheme() const { return _scheme; }
	const std::string& auth() const { return _auth; }
	const std::string& path() const { return _path; }
	const std::string& query() const { return _query; }
	const std::string& fragment() const { return _fragment; }

	const addr& addr() const { return _addr; }
	const params& params() const { return _params; }

private:
	std::string _scheme; //uri scheme string
	std::string _auth; //uri authority string
	std::string _path; //uri path string
	std::string _query; //uri query string
	std::string _fragment; //uri fragment string

	http::addr _addr; //uri address
	http::params _params; //parameters in query string
};

END_CUBE_HTTP_NS
