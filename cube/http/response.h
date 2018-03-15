#pragma once
#include "cube\http\mime.h"
#include "cube\http\config.h"
#include "cube\http\status.h"
#include "cube\http\header.h"
#include "cube\http\entity.h"
#include "cube\http\cookie.h"
#include "cube\http\charset.h"
BEGIN_CUBE_HTTP_NS
class response {
public:
	response() { }
	virtual ~response() {}
	
	/*
	*	pack response content
	*/
	std::string pack() const;

public:
	/*
	*	set response status
	*/
	void status(http::status s);

	/*
	*	redirect to new location, code: 3xx
	*@param code: in, redirect code
	*@param url: in, new location
	*/
	void redirect(const char *url, bool permanent = true);

	/*
	*	set response content
	*@param data: in, data to response
	*@param sz: in, data size
	*@param
	*@return:
	*	void
	*/
	void content(const char *data, int sz, const char *type, const char *charset = config::default_charset);

	/*
	*	set response cookie
	*/
	void cookie(const std::string &name, const std::string &value, int maxage, const char *domain = config::domain, const char *path="/");

private:
	//response status
	http::status _status;
	//response header
	http::headers _headers;
	//response entity
	http::entity _entity;

	//response cookie
	http::cookies _cookies;
};
END_CUBE_HTTP_NS
