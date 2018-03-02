#pragma once
#include "cube\http\status.h"
#include "cube\http\header.h"
#include "cube\http\entity.h"
#include "cube\http\cookie.h"
BEGIN_CUBE_HTTP_NS
class response {
public:
	response() { }
	virtual ~response() {}

public:
	http::status &status() {
		return _status; 
	}

	http::header &header() {
		return _header; 
	}
	
	http::entity &entity() {
		return _entity;
	}

	http::cookie &cookie() {
		return _cookie;
	}

private:
	//response status
	http::status _status;
	//response header
	http::header _header;
	//response entity
	http::entity _entity;

	//response cookie
	http::cookie _cookie;
};
END_CUBE_HTTP_NS
