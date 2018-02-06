/*
*	uri - uniform resource identifier
*form:
*	scheme:[//[user[:password]@]host[:port]][/path][?query][#fragment]
*examples:
*	abc://username:password@example.com:123/path/data?key=value#fragid1
*/
#pragma once
#include "cube\http\addr.h"
#include "cube\http\param.h"
BEGIN_CUBE_HTTP_NS

class auth {

};

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

class params {
public:
	params() {}
	virtual ~params() {}

	//pack/parse params with data string
	std::string pack() const;
	int parse(const char *data, int sz, std::string *err = 0);

	/*
	*	get param value by specfied key
	*@param key: in, param key
	*@param val: in/out, value of specified key
	*@return:
	*	value of param
	*/
	std::vector<std::string> get(const std::string &key) const;
	std::string get(const std::string &key, const char *default) const;
private:
	//params
	std::map<std::string, std::vector<std::string>> _params;
};

class uri {
public:
	uri() : _scheme(""), _auth(""), _path(""), _query(""), _fragment("") {}
	virtual ~uri() {}

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

public:
	/*
	*	pack uri object to string
	*/
	std::string pack() const;

	/*
	*	parse uri object from string
	*/
	int parse(const std::string &str, std::string *err = 0);

private:
	std::string _scheme;
	
	std::string _user;
	std::string _pwd;

	std::string _host;
	std::string _port;

	std::string _path;
	std::string _query;
	std::string _fragment;

	http::params _params; //parameters in query string
};
END_CUBE_HTTP_NS
