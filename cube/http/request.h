#pragma once
#include <mutex>
#include <memory>
#include "cube\http\query.h"
#include "cube\http\header.h"
#include "cube\http\entity.h"
#include "cube\http\message.h"
BEGIN_CUBE_HTTP_NS
//http request class
class request : public message {
public:
	request() {}
	virtual ~request() {}

	bool has_entity_done() const;
	int put_start_line(const char *data, int sz);
	int put_header_line(const char *data, int sz);
	int put_entity_data(const char *data, int sz);

public:
	const http::query &query() const;
	const http::header &header() const;
	const http::entity &entity() const;

private:
	//http request query
	http::query _query;
	//http request header
	http::header _header;
	//http request entity
	http::entity _entity;
};
END_CUBE_HTTP_NS
