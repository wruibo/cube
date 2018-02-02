#pragma once
#include "cube\http\def.h"
BEGIN_CUBE_HTTP_NS
//address class
class addr {
public:
	addr() : _host(""), _port(0) {}
	virtual ~addr() {}

	//pack/parse address with data string
	std::string pack() const;
	int parse(const char *data, int sz, std::string *err = 0);


	//get/set address properties
	const std::string& host() { return _host; }
	void host(const std::string &host) { _host = host; }
	ushort port() { return _port; }
	void port(ushort port) { _port = port; }

private:
	//host address in url
	std::string _host;
	//port in url
	ushort _port;
};
END_CUBE_HTTP_NS
