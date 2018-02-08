#pragma once
#include "cube\http\message.h"
BEGIN_CUBE_HTTP_NS
//response class
class response : public message {
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
	const std::string &code() { return _code; }
	void code(const std::string &code) { _code = code; }

	const std::string &reason() { return _reason; }
	void reason(const std::string &reason) { _reason = reason; }

private:
	//response code
	std::string _code;
	//response description
	std::string _reason;
};
END_CUBE_HTTP_NS
