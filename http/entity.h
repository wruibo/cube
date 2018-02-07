#pragma once
#include "cube\http\header.h"
#include <vector>
#include <memory>
#include <iostream>
BEGIN_CUBE_HTTP_NS
//http entity class
class entity {
public:
	static entity *create(const headers *headers);

public:
	entity() : _size(-1), _transfered(0){}
	virtual ~entity() {}

	bool has_transfered() const;
	void set_transfered(std::streamsize sz);

	std::streamsize get_size() const;

public:
	virtual void set_headers(headers *headers);

	virtual std::shared_ptr<std::iostream> get_stream() const;

	const std::string &get_content_type() const;
	void set_content_type(const std::string &type);

	std::streamsize get_content_length() const;
	void set_content_length(std::streamsize sz);

private:
	//entity size in bytes
	std::streamsize _size;
	//data has transfered
	std::streamsize _transfered;
};

//form entity class
class entity_form : public entity {
public:
	entity_form() {}
	virtual ~entity_form() {}


private:
};

//data entity class
class entity_data : public entity {
public:
	entity_data() {}
	virtual ~entity_data() {}

};

//file entity class
class entity_file : public entity {
public:
	entity_file() {}
	virtual ~entity_file() {}

};

END_CUBE_HTTP_NS
