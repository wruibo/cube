#pragma once
#include "cube\http\request.h"
BEGIN_CUBE_HTTP_NS
//http request stream
class rqstream {
public:
	rqstream() {}
	~rqstream() {}

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
	bool done() const;

public:
	http::request &request() { return _request; }
	const http::request &request() const { return _request; }

private:
	//request object
	http::request _request;
};
END_CUBE_HTTP_NS

