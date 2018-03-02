#pragma once
#include <mutex>
#include <memory>
#include "cube\http\query.h"
#include "cube\http\header.h"
#include "cube\http\entity.h"
BEGIN_CUBE_HTTP_NS
//http request class
class request {
public:
	request() {}
	virtual ~request() {}

	const http::query &query() const { 
		return _query; 
	}

	const http::header &header() const {
		return _header;
	}

	const http::entity &entity() const {
		return _entity; 
	}

private:
	//http request query
	http::query _query;
	//http request header
	http::header _header;
	//http request entity
	http::entity _entity;
};
END_CUBE_HTTP_NS
