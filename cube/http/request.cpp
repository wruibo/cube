#include "cube\safe.h"
#include "cube\str\part.h"
#include "cube\str\case.h"
#include "cube\str\format.h"
#include "cube\http\request.h"
BEGIN_CUBE_HTTP_NS

bool request::has_entity_done() const {
	return false;
}

int request::put_start_line(const char *data, int sz) {
	return 0;
}

int request::put_header_line(const char *data, int sz) {
	return 0;
}

int request::put_entity_data(const char *data, int sz) {
	return 0;
}

const http::query &request::query() const {
	return _query;
}

const http::header &request::header() const {
	return _header;
}

const http::entity &request::entity() const {
	return _entity;
}
END_CUBE_HTTP_NS
