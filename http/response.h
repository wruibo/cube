#pragma once
#include "cube\http\feed.h"
#include "cube\http\status.h"
#include "cube\http\header.h"
#include "cube\http\entity.h"
#include "cube\http\charset.h"
BEGIN_CUBE_HTTP_NS
//response head
class rphead {
	friend class response;
public:
	rphead() : _feed(nullptr) {}
	~rphead() {}

	http::status &status() { return _status; }
	const http::status &status() const { return _status; }

	http::header &header() { return _header; }
	const http::header &header() const { return _header; }

private:
	int read(char *data, int sz, std::string *err = 0);
	int write(const char *data, int sz, std::string *err = 0);

	bool done() const;

private:
	//response status
	http::status _status;
	//response header
	http::header _header;

	//head data stream
	std::unique_ptr<crlfeed> _feed;
};

//response body
class rpbody {
	friend class response;
public:
	rpbody() : _entity(nullptr) {}
	~rpbody() {}

private:
	int read(char *data, int sz, std::string *err = 0);
	int write(const char *data, int sz, std::string *err = 0);

	bool done() const;

private:
	//body entity
	std::unique_ptr<entity> _entity;
};

//response class
class response {
	friend class rpstream;
public:
	response() {}
	virtual ~response() {}

	/*
	*	informational: 1xx
	*/
	void info(int code);

	/*
	*	success: 2xx
	*/
	void succ(int code);

	/*
	*	client error: 4xx
	*@param code: in, client error code
	*@return:
	*	void
	*/
	void cerr(int code);

	/*
	*	server error: 5xx
	*@param code: in, server error code
	*@return:
	*	void
	*/
	void serr(int code);

	/*
	*	jump to new location, code: 3xx
	*@param code: in, redirect code
	*@param url: in, new location
	*/
	void jump(const char *url, bool permanent = true);

	/*
	*	success response with file/json/data, code: 200 OK
	*@param path: in, local file path
	*@param data: in, data to response
	*@param sz: in, data size
	*@return:
	*	void
	*/
	void file(const char *path, const char *charset = charset::default.c_str());
	void json(const char *data, int sz, const char *charset = charset::utf8.c_str());
	void data(const char *data, int sz, const char *charset = charset::default.c_str());

public:
	http::status &status() { return _head.status(); }
	const http::status &status() const { return _head.status(); }

	http::header &header() { return _head.header(); }
	const http::header &header() const { return _head.header(); }

private:
	/*
	*	take data from request buffer
	*@param data: in/out, data to take to
	*@param sz: in, data size
	*@return:
	*	size taked, <0 when error
	*/
	int read(char *data, int sz);

	/*
	*	feed data to request buffer
	*@param data: in, data to feed
	*@param sz: in, data size
	*@return:
	*	size feeded, <0 when error
	*/
	int write(const char *data, int sz);

	/*
	*	check if request transfering has done
	*@return:
	*	true - request has done, false - not done
	*/
	bool done() const { return _head.done() && _body.done(); }

private:
	//response head
	rphead _head;
	//response body
	rpbody _body;
};
END_CUBE_HTTP_NS
