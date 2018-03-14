#include "cube\safe.h"
#include "cube\str\part.h"
#include "cube\str\case.h"
#include "cube\str\format.h"
#include "cube\http\request.h"
BEGIN_CUBE_HTTP_NS

bool request::has_entity_done() const {
	return _entity.has_done();
}

int request::set_start_line(const std::string &data) {
	return _query.parse(data);
}

int request::add_header_line(const std::string &data) {
	return _headers.add(data);
}

int request::end_header_data() {
	return _entity.set_meta(_headers);
}

int request::add_entity_data(const char *data, int sz) {
	return _entity.add_data(data, sz);
}

int request::end_entity_data() {
	return _entity.end_data();
}

const http::query &request::query() const {
	return _query;
}

const http::headers &request::headers() const {
	return _headers;
}

const http::entity &request::entity() const {
	return _entity;
}
END_CUBE_HTTP_NS
