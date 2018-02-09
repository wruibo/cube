#pragma once
#include "cube\http\def.h"
#include <string>
#include <vector>
BEGIN_CUBE_HTTP_NS
static const int BUFSZ = 4096;
//name value pair
class nvpair {
public:
	nvpair() : _name(""), _value("") {}
	nvpair(const std::string &name, const std::string &value) : _name(name), _value(value) {}
	virtual ~nvpair() {}


	const std::string &name() const { return _name; }
	void name(const std::string &name) { _name = name; }

	const std::string &value() const { return _value; }
	void value(const std::string &value) { _value = value; }

private:
	std::string _name;
	std::string _value;
};

//parameter
class param : public nvpair {
public:
	param(){}
	param(const std::string &name, const std::string &value) : nvpair(name, value) {}
	virtual ~param() {}

public:
	std::string pack() const;
	int parse(const std::string &data, std::string *err);
};

//parameters
class params {
public:
	params() {}
	virtual ~params() {}

	bool has(const std::string &name) const;
	
	params& add(const param &param) { _params.push_back(param); return *this; }
	params& add(const std::string &name, const std::string &value) { _params.push_back(param(name, value));  return *this;}

	std::string get(const std::string &name) const;
	std::string get(const std::string &name, const char *default) const;
	
	std::vector<std::string> gets(const std::string &name) const;

public:
	std::string pack() const;
	int parse(const std::string &data, std::string *err);

private:
	std::vector<param> _params;
};

//uniform resource identifier
class uri {
public:
	uri() : _scheme(""), _user(""), _pwd(""), _host(""), _port(""), _path(""), _query(""), _fragment("") {}
	virtual ~uri() {}

	const std::string& scheme() const { return _scheme; }
	uri &scheme(const std::string &scheme) { _scheme = scheme; return *this; }


	const std::string& user() const { return _user; }
	uri &user(const std::string &user) { _user = user; return *this; }

	const std::string& pwd() const { return _pwd; }
	uri &pwd(const std::string &pwd) { _pwd = pwd; return *this; }

	const std::string& host() const { return _host; }
	uri &host(const std::string &host) { _host = host; return *this; }

	const std::string& port() const { return _port; }
	uri &port(const std::string &port) { _port = port; return *this; }

	const std::string& path() const { return _path; }
	uri &path(const std::string &path) { _path = path; return *this; }

	const std::string& query() const { return _query; }
	uri &query(const std::string &query) { _query = query; return *this; }

	const std::string& fragment() const { return _fragment; }
	uri &fragment(const std::string &fragment) { _fragment = fragment; return *this; }

public:
	std::string pack() const;
	int parse(const std::string &data, std::string *err);

private:
	std::string _scheme;

	std::string _user;
	std::string _pwd;

	std::string _host;
	std::string _port;

	std::string _path;
	std::string _query;
	std::string _fragment;
};
END_CUBE_HTTP_NS
