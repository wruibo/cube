#pragma once
#include "cube\http\feed.h"
#include "cube\http\query.h"
#include "cube\http\header.h"
#include "cube\http\entity.h"
#include <mutex>
#include <memory>
BEGIN_CUBE_HTTP_NS
//request head
class rqhead {
	friend class request;
public:
	rqhead() : _feed(nullptr) {}
	~rqhead() {}

	http::query &query() { return _query; }
	const http::query &query() const { return _query; }

	http::header &header() { return _header; }
	const http::header &header() const { return _header; }

private:
	int read(char *data, int sz, std::string *err = 0);
	int write(const char *data, int sz, std::string *err = 0);

	bool done() const;

private:
	//request line
	http::query _query;
	//request header
	http::header _header;

	//head data stream
	std::unique_ptr<crlfeed> _feed;
};

//request body
class rqbody {
	friend class request;
public:
	rqbody() : _entity(nullptr) {}
	~rqbody() {}

private:
	int read(char *data, int sz, std::string *err = 0);
	int write(const char *data, int sz, std::string *err = 0);

	bool done() const;

private:
	//body entity
	std::unique_ptr<entity> _entity;
};

//http request class
class request {
	friend class rqstream;
public:
	request() {}
	virtual ~request() {}

	http::query &query() { return _head.query(); }
	const http::query &query() const { return _head.query(); }

	http::header &header() { return _head.header(); }
	const http::header &header() const { return _head.header(); }

private:
	int read(char *data, int sz);
	int write(const char *data, int sz);
	bool done() const { return _head.done() && _body.done(); }

private:
	//request head
	rqhead _head;
	//request entity
	rqbody _body;
};
END_CUBE_HTTP_NS
