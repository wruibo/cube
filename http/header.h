#pragma once
#include "cube\http\base.h"
BEGIN_CUBE_HTTP_NS
//header element
class element : public nvpair {
public:
	element() {}
	element(const std::string &name, const std::string &value) : nvpair(name, value) {}
	element(const std::string &name, const std::string &value, const params &params) : nvpair(name, value), _params(params) {}
	virtual ~element() {}

	std::string get_param(const std::string &name) { return _params.get(name); }
	std::string get_param(const std::string &name, const char *default) { return _params.get(name, default); }

	element& add_param(const http::param &param) { _params.add(param); return *this; }
	element& add_param(const std::string &name, const std::string &value) { _params.add(name, value); return *this; }

	void set_params(const params &params) { _params = params; }
	const params &get_params() const { return _params; }

public:
	std::string pack() const;
	int parse(const std::string &data, std::string *err);

private:
	//parameter of element
	params _params;
};

//header elements
class elements {
public:
	elements() {}
	virtual ~elements() {}

	int has(const std::string &name) const;
	int count() const { return (int)_elements.size(); }

	elements& add(const element &element) { _elements.push_back(element); return *this; }

	element get(int index) const { return _elements[index]; }
	element get(const std::string &name) const;

public:
	std::string pack() const;
	int parse(const std::string &data, std::string *err);

private:
	std::vector<element> _elements;
};

//http message header class
class header : public nvpair {
public:
	header() { }
	header(const std::string &name, const std::string &value) : nvpair(name, value) {}
	virtual ~header() {}

	elements get_elements() const;

public:
	std::string pack() const;
	int parse(std::string *err);
	int parse(const std::string &data, std::string *err);
private:
};

//http message headers class
class headers {
public:
	headers() {}
	virtual ~headers() {}

	bool has(const std::string &name) const;

	int count() const;
	int count(const std::string &name) const;
		
	void set(const header &header);
	const header &get(const std::string &name) const;

	void set(const headers *headers);

public:
	std::string pack() const;
	int parse(const std::string &data, std::string *err);

private:
	std::vector<header> _headers;
};
END_CUBE_HTTP_NS
