#pragma once
#include "cube\http\request.h"
#include "cube\http\response.h"
#include <fstream>
#include <sstream>
BEGIN_CUBE_HTTP_NS
//CRLF string buffer
class crlfbuffer {
public:
	crlfbuffer() : _buffer("") {}
	virtual ~crlfbuffer() {}

	std::streamsize put(const char *data, std::streamsize sz);

	std::string data() const;

	const std::string &buffer() const;

	bool full() const;

	void clear();
private:
	std::string _buffer;
};

//http message stream
class httpstream {
public:
	httpstream(http::message *message) : _message(message), _head_stream(nullptr), _body_stream(nullptr) {}
	virtual ~httpstream() {}
	
	std::streamsize read(char *data, std::streamsize sz);

	std::streamsize write(const char *data, std::streamsize sz);

public:
	void make();

	bool full() const;

private:
	//CRLF string buffer
	crlfbuffer _crlfbuffer;

	//http message
	std::shared_ptr<http::message> _message;

	//http head data stream
	std::shared_ptr<std::iostream> _head_stream;
	//http body data stream
	std::shared_ptr<std::iostream> _body_stream;
};
END_CUBE_HTTP_NS