#include "cube\log\log.h"
#include "cube\str\stype.h"
#include "cube\http\config.h"
#include "cube\http\entity.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////entity class/////////////////////////////////////////
int entity::set_meta(const headers &headers) {
	//set content type
	_type = headers.get("content-type");

	//set content length
	std::string strlen = headers.get("content-length");
	if (!strlen.empty()) {
		if (!str::isdigit(strlen.c_str())) {
			log::error("invalid content length: %s", strlen.c_str());
			return -1;
		}
		_length = atoi(strlen.c_str());
		if (_length < 0 || _length > config::max_entity_length) {
			log::error("too large content length: %d", _length);
			return -1;
		}
	}

	//set content language
	_language = headers.get("content-language");

	//set content encoding
	_encoding = headers.get("content-encoding");

	//set content range
	_range = headers.get("content-range");

	//set content expires
	_expires = headers.get("expires");

	return 0;
}

int entity::add_data(const char *data, int sz) {
	if (_stream.size() > config::max_entity_length)
		return -1;

	return (int)_stream.write(data, sz);
}

int entity::end_data() {
	if (_stream.size() < _length)
		return -1; //data not completed
	
	_length = (int)_stream.size();
	return 0;
}

bool entity::has_done() const {
	return _length == (int)_stream.size();
}

END_CUBE_HTTP_NS
