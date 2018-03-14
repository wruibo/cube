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
	int set_start_line(const std::string &data);
	int add_header_line(const std::string &data);
	int end_header_data();
	int add_entity_data(const char *data, int sz);
	int end_entity_data();

public:
	const http::query &query() const;
	const http::headers &headers() const;
	const http::entity &entity() const;

private:
	//http request query
	http::query _query;
	//http request headers
	http::headers _headers;
	//http request entity
	http::entity _entity;
};
END_CUBE_HTTP_NS
