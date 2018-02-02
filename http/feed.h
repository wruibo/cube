#pragma once
#include "cube\http\def.h"
#include <memory>
#include <sstream>
BEGIN_CUBE_HTTP_NS
//feed interface
class feed {
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

	/*
	*	get next feed item
	*/
	virtual std::string next() = 0;
};

class crlfeed: public feed{
	static const std::string _tag;
public:
	crlfeed() : _pos(0), _done(false), _stream(std::unique_ptr<std::iostream>(new std::stringstream())) {}
	crlfeed(const std::string &data) : _pos(0), _done(false), _stream(std::unique_ptr<std::iostream>(new std::stringstream())) {
		_stream->write(data.c_str(), data.length());
		_done = true;
	}
	crlfeed(std::iostream *stream) : _pos(0), _stream(std::unique_ptr<std::iostream>(stream)) {}
	crlfeed(const std::string &data, std::iostream *stream) : _pos(0), _stream(std::unique_ptr<std::iostream>(stream)) {
		_stream->write(data.c_str(), data.length());
		_done = true;
	}
	virtual ~crlfeed() {}

	int read(char *data, int sz);

	int write(const char *data, int sz);

	int size() const;

	bool endr() const;

	bool endw() const;

	bool done() const;

	bool empty() const;

	std::string next();

private:
	//compare pos in crlf
	int _pos;

	//feed completed flag
	bool _done;

	//feed io stream
	std::unique_ptr<std::iostream> _stream;
};

END_CUBE_HTTP_NS
