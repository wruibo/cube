#include "cube\http\response.h"
BEGIN_CUBE_HTTP_NS
////////////////////////////////////////response class///////////////////////////////////////////
void response::info(int code) {

}

void response::succ(int code) {

}

void response::cerr(int code) {
	//set status line
	_head.status().set(code);

	//set general header
	_head.header().set(http::header::response::default());
}

void response::serr(int code) {
	//set status line
	_head.status().set(code);

	//set general header
	_head.header().set(http::header::response::default());
}

void response::jump(const char *url, bool permanent) {
	//set status line
	if (permanent)
		_head.status().set(301);
	else
		_head.status().set(302);

	//set general header
	_head.set_header(http::header::response::default());

	//set redirect location
	_head.set_header("Location", url);
}

void response::file(const char *path, const char* charset) {
	//set status line
	_head.status().set(200);

	//set general header
	_head.header.(http::header::response::default());

	//set entity data
	_body.file(path, charset);
}

void response::json(const char *data, int sz, const char* charset) {
	//set status line
	_head.status().set(200);

	//set general header
	_head.set_header(http::header::response::default());

	//set entity data
	_body.data("json", data, sz, charset);
}

void response::data(const char *data, int sz, const char* charset) {
	//set status line
	_head.status().set(200);

	//set general header
	_head.set_header(http::header::response::default());

	//set entity data
	_body.data("octet", data, sz, charset);
}

int response::read(char *data, int sz) {
	//taked size
	int tsz = 0;

	//take head data
	if (tsz < sz) {
		tsz += _head.take(data + tsz, sz - tsz);
	}

	//take body data
	if (tsz < sz) {
		tsz += _body.take(data + tsz, sz - tsz);
	}

	//size taked
	return tsz;
}

int response::write(const char *data, int sz) {
	//feed size
	int fsz = 0;

	//feed head
	if (!_head.done()) {
		fsz += _head.feed(data + fsz, sz - fsz);
	}

	//feed body
	fsz += _body.feed(data + fsz, sz - fsz);

	//size feed
	return fsz;
}
END_CUBE_HTTP_NS
