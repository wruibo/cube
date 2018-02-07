#pragma once
#include "cube\http\entity.h"
#include "cube\http\header.h"
#include <list>
#include <memory>
BEGIN_CUBE_HTTP_NS
class message {
public:
	message() : _start_line(""), _entity(nullptr) {}
	virtual ~message() {}

protected:
	virtual int on_head_transfered(std::string *err) = 0;

public:
	bool has_body_entity() const;
	bool has_body_transfered() const;
	void set_body_transfered(std::streamsize sz);
	std::shared_ptr<std::iostream> get_body_stream() const;

	void set_head_transfered();
	bool has_head_transfered() const;
	void set_head_line(const std::string &line);
	
public:
	std::streamsize get_content_length() const;

protected:
	//http message start line
	std::string _start_line;
	//http message header lines
	std::list<std::string> _header_lines;

protected:
	//http message headers
	http::headers _headers;
	//http message body entity
	std::shared_ptr<http::entity> _entity;
};
END_CUBE_HTTP_NS
