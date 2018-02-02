#pragma once
#include "cube\http\def.h"
#include <iostream>
BEGIN_CUBE_HTTP_NS
//http entity class
class entity {
public:
	/*
	*	take data from stream
	*@param data: in/out, data to take to
	*@param sz: in, data size
	*@return:
	*	size taked
	*/
	virtual int read(char *data, int sz) = 0;

	/*
	*	feed data to stream
	*@param data: in, data to feed
	*@param sz: in, data size
	*@return:
	*	size feeded
	*/
	virtual int write(const char *data, int sz) = 0;

	/*
	*	get feed data size in bytes
	*@return:
	*	data size in bytes
	*/
	virtual int size() const = 0;

	/*
	*	check if feed is end of read, which means all data has read
	*@return:
	*	true - no more data can be read, false - more data can be read
	*/
	virtual bool endr() const = 0;

	/*
	*	check if feed is end of write, which means no more data can be write
	*@reutrn:
	*	true - no more data can be write, false - more data can be write
	*/
	virtual bool endw() const = 0;

	/*
	*	check if feed is done, which means completed
	*@return:
	*	true - done, false - not done
	*/
	virtual bool done() const = 0;

	/*
	*	check if feed if empty, which means no data
	*/
	virtual bool empty() const = 0;
};


END_CUBE_HTTP_NS
