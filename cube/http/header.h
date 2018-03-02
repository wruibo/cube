#pragma once
#include "cube\http\pair.h"
#include "cube\http\param.h"
BEGIN_CUBE_HTTP_NS
//field element
class element : public pair {
public:
	element() {}
	element(const std::string &name, const std::string &value) : pair(name, value) {}
	virtual ~element() {}
			
public:
	http::params &params() { return _params; }

private:
	//parameter of element
	http::params _params;
};

//header field
class field : public pair {
public:
	field() {}
	field(const std::string &name, const std::string &value) : pair(name, value) {}
	virtual ~field() {}

public:
	bool operator==(const field &field) const;
	bool operator==(const std::string &name) const;
};

//http header
class header {
public:
	header() {}
	virtual ~header() {}

	void add(const std::string &name, const std::string &value);
	void set(const std::string &name, const std::string &value);

private:
	std::vector<field> _fields;
};
END_CUBE_HTTP_NS
