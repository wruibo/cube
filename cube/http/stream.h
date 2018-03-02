#pragma once
#include <fstream>
#include <sstream>
#include "cube\http\buffer.h"
#include "cube\http\request.h"
#include "cube\http\response.h"
BEGIN_CUBE_HTTP_NS
//stream interface
class stream {
public:
	/*
	*	read data from stream
	*@param data: in/out, output buffer
	*@param sz: in, output buffer size
	*@return:
	*	data size read from stream
	*/
	virtual int read(char *data, int sz) = 0;

	/*
	*	write data into stream
	*@param data: in, data to write
	*@param sz: in, data size
	*@return:
	*	data size write into stream
	*/
	virtual int write(const char *data, int sz) = 0;

	/*
	*	set the next read position in stream
	*@param pos: in, read position in stream
	*@return:
	*	0-success, <0-failed
	*/
	virtual int seekr(int pos) = 0;

	/*
	*	set the next write position in stream
	*@param pos: in, write position in stream
	*@return:
	*	0-success, <0-failed
	*/
	virtual int seekw(int pos) = 0;

	/*
	*	test if end of read, means no more data could be read from stream
	*@return:
	*	bool
	*/
	virtual bool endr() const = 0;

	/*
	*	test if end of write, means no more data could be write into stream
	*@return:
	*	bool
	*/
	virtual bool endw() const = 0;

	/*
	*	get stream data size
	*@return:
	*	data size in bytes
	*/
	virtual int size() = 0;

	/*
	*	get stream data
	*@return:
	*	stream data
	*/
	virtual std::string data() = 0;
};

//data stream
class data_stream : public stream {
public:
	data_stream(int maxsz = INT_MAX) : _rpos(0), _wpos(0), _maxsz(maxsz), _data(""){}
	virtual ~data_stream() {}

	int read(char *data, int sz);

	int write(const char *data, int sz);

	int seekr(int pos);

	int seekw(int pos);

	bool endr() const;

	bool endw() const;

	int size();

	std::string data();

private:
	//current read pos
	int _rpos;
	//current write pos
	int _wpos;
	//max stream size
	int _maxsz;

	//stream data
	std::string _data;
};

//file stream
class file_stream : public stream {
public:
	file_stream(const std::string &path, int mode) : _file(path, mode) {}
	virtual ~file_stream() {}

	int read(char *data, int sz);

	int write(const char *data, int sz);

	int seekr(int pos);

	int seekw(int pos);

	bool endr() const;

	bool endw() const;

	int size();

	std::string data();

private:
	//file path
	std::string _path;
	//file stream
	std::fstream _file;
};

//carriage return/line stream
class crlf_stream : public stream{
public:
	crlf_stream() {}
	virtual ~crlf_stream() {}

	int read(char *data, int sz);

	int write(const char *data, int sz);

	bool endr() const;

	bool endw() const;

	int size();

	std::string data();
private:
	//stream data
	std::string _data;

	//carriage return/line buffer
	line_buffer _line_buffer;
};

//http request data stream
class http_request_stream : public stream{
public:
	http_request_stream() {}
	virtual ~http_request_stream() {}

	int read(char *data, int sz);

	int write(const char *data, int sz);

	bool endr() const;

	bool endw() const;

	int size();

	std::string data();
private:
	//head stream
	stream *_head_stream;
	//body stream
	stream *_body_stream;
};

//http response packer stream
class http_response_stream : public stream{
public:
	http_response_stream() {}
	virtual ~http_response_stream() {}

	int read(char *data, int sz);

	int write(const char *data, int sz);

	bool endr() const;

	bool endw() const;

	int size();

	std::string data();

private:
	//head stream
	stream *_head_stream;
	//body stream
	stream *_body_stream;
};
END_CUBE_HTTP_NS
