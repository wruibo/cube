#pragma once
#include "cube\http\response.h"
BEGIN_CUBE_HTTP_NS
//http response stream
class rpstream {
public:
	rpstream() {}
	~rpstream() {}

	/*
	*	take data from response buffer
	*@param data: in/out, data to take to
	*@param sz: in, data size
	*@return:
	*	size taked
	*/
	int read(char *data, int sz);

	/*
	*	feed data to response buffer
	*@param data: in, data to feed
	*@param sz: in, data size
	*@return:
	*	size feeded
	*/
	int write(const char *data, int sz);

	/*
	*	check if response transfering has done
	*@return:
	*	true - response has done, false - not done
	*/
	bool done() const;
public:
	http::response &response() { return _response; }
	const http::response &response() const { return _response; }

private:
	//response object
	http::response _response;
};
END_CUBE_HTTP_NS
