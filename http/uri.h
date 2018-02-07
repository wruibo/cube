/*
*	uri - uniform resource identifier
*form:
*	scheme:[//[user[:password]@]host[:port]][/path][?query][#fragment]
*examples:
*	abc://username:password@example.com:123/path/data?key=value#fragid1
*/
#pragma once
#include "cube\http\def.h"
#include <map>
#include <vector>
BEGIN_CUBE_HTTP_NS
class param {
public:
	param() : _name(""), _value("") {}
	virtual ~param() {}

	const std::string &name() const { return _name; }
	void name(const std::string &name) { _name = name; }

	const std::string &value() const { return _value; }
	void value(const std::string &value) { _value = value; }

public:
	std::string pack() const;
	int parse(const std::string &data, std::string *err);

private:
	std::string _name;
	std::string _value;
};

class params {
public:
	params() {}
	virtual ~params() {}

	bool has(const std::string &name) const;
	std::string get(const std::string &name) const;
	std::string get(const std::string &name, const char *default) const;
	std::vector<std::string> gets(const std::string &name) const;

public:
	std::string pack() const;
	int parse(const std::string &data, std::string *err);

private:
	std::multimap<std::string, param> _params;
};

class uri {
public:
	uri() : _scheme(""), _user(""), _pwd(""), _host(""), _port(""), _path(""), _query(""), _fragment("") {}
	virtual ~uri() {}

	const std::string& scheme() const { return _scheme; }
	const std::string& user() const { return _user; }
	const std::string& pwd() const { return _pwd; }
	const std::string& host() const { return _host; }
	const std::string& port() const { return _port; }
	const std::string& path() const { return _path; }
	const std::string& query() const { return _query; }
	const std::string& fragment() const { return _fragment; }

	const params& params() const { return _params; }

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

	http::params _params;
};
END_CUBE_HTTP_NS
