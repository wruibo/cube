#pragma once
#include "cube\http\def.h"
#include <map>
#include <vector>
BEGIN_CUBE_HTTP_NS

//http message header class
class header {
public:
	header() : _name(""), _value("") { }
	header(const std::string &name, const std::string &value) : _name(name), _value(value) {}
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
	static const header _empty_header;
public:
	headers() {}
	virtual ~headers() {}

	bool has(const std::string &name) const;

	int count() const;
	int count(const std::string &name) const;
		
	void set(const header &header);
	const header &get(const std::string &name) const;

	void set(const headers *headers);

private:
	std::multimap<std::string, header> _headers;
};
END_CUBE_HTTP_NS
