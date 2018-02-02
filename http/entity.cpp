#include "cube\http\entity.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////entity class/////////////////////////////////////////
void body::init(const http::meta &meta) {
	//

	//create output stream
	int len = meta.length();
}

void body::file(const std::string &path, const char* charset) {
	//set stream data
	_stream = std::unique_ptr<stream>(new fstream(path, std::ios::in | std::ios::binary));

	//get file extension
	std::string ext = fd::ext(path);

	//set content type
	_meta.type(mime::get(ext, charset));

	//set content length
	_meta.length(_stream->size());
}

void body::form(const char *data, int sz, const char* charset) {
	//set content type
	_meta.type(mime::get("form", charset));

	//set content length
	_meta.length(sz);

	//set stream data
	_stream = std::unique_ptr<stream>(new sstream(std::string(data, sz)));
}

void body::data(const std::string &type, const char *data, int sz, const char* charset) {
	//set content type
	_meta.type(mime::get(type, charset));

	//set content length
	_meta.length(sz);

	//set stream data
	_stream = std::unique_ptr<stream>(new sstream(std::string(data, sz)));
}

int body::take(char *data, int sz) {
	if (_stream == nullptr) {
		return 0;
	}

	return _stream->take(data, sz);
}

int body::feed(const char *data, int sz) {
	if (_stream == nullptr) {
		return 0;
	}
	return _stream->feed(data, sz);
}

bool body::done() const {
	if (_stream == nullptr) {
		return true;
	}
	return _stream->full();
}
END_CUBE_HTTP_NS
