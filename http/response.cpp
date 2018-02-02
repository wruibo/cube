#include "cube\http\response.h"
BEGIN_CUBE_HTTP_NS
////////////////////////////////////////response class///////////////////////////////////////////

int rphead::read(char *data, int sz, std::string *err) {
	//make stream
	if (_feed == nullptr) {
		_feed = std::unique_ptr<crlfeed>(new crlfeed(_status.pack() + _header.pack() + "\r\n"));
	}

	//take data from stream
	return _feed->read(data, sz);
}

int rphead::write(const char *data, int sz, std::string *err) {
	//create stream
	if (_feed == nullptr) {
		_feed = std::unique_ptr<crlfeed>(new crlfeed());
	}

	//full stream
	if (_feed->done())
		return 0;

	//check data
	if (sz == 0 || data == 0) {
		//incompleted response
		safe_assign<std::string>(err, "incompleted response.");
		return -1;
	}

	//feed stream
	int fsz = _feed->write(data, sz);

	//parse head
	if (_feed->done()) {
		//parse query line
		if (!_feed->endr()) {
			if (_status.parse(_feed->next().c_str(), err) != 0)
				return -1;
		} else {
			//invalid request
			safe_assign<std::string>(err, "empty response.");
			return -1;
		}

		//parse headers
		while (!_feed->endr()) {
			if (_header.parse(_feed->next().c_str(), err) != 0)
				return -1;
		}
	}

	//return feed size
	return fsz;
}

bool rphead::done() const {
	if (_feed == nullptr) {
		return true;
	}
	return _feed->done();
}

///////////////////////////////////////////////response body class//////////////////////////////////////
int rpbody::read(char *data, int sz, std::string *err) {
	return 0;
}

int rpbody::write(const char *data, int sz, std::string *err) {
	return 0;
}

bool rpbody::done() const {
	if (_entity == nullptr)
		return true;
	return _entity->done();
}

///////////////////////////////////////////////response class//////////////////////////////////////
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
