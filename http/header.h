#pragma once
#include "cube\http\def.h"
#include <map>
#include <vector>
BEGIN_CUBE_HTTP_NS

//http message header class
class header {
public:
	header() : _name(""), _value("") { }
	virtual ~header() {}


	const std::string &name() const { return _name; }
	void name(const std::string &name) { _name = name; }

	const std::string &value() const { return _value; }
	void value(const std::string &value) { _value = value; }

private:
	std::string _name;
	std::string _value;
};

//http message headers class
class headers {
public:
	headers() {}
	virtual ~headers() {}

	int count() const;
	bool has(const std::string &name);
	
	void set(const header &header);
	const header &get(int pos) const;
	const header &get(const std::string &name) const;

	void sets(const std::vector<header> &headers);
	const std::vector<header> &gets(const std::string &name) const;
	
	const std::vector<header> &gets() const;

private:
	std::vector<header> _vheaders;
	std::map<std::string, std::vector<header>> _mheaders;
};
END_CUBE_HTTP_NS
