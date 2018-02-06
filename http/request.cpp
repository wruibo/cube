#include "cube\http\request.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////request head class/////////////////////////////////////////
int rqhead::read(char *data, int sz, std::string *err) {
	//make stream
	if (_feed == nullptr) {
		_feed = std::unique_ptr<crlfeed>(new crlfeed(_query.pack() + _header.pack() + "\r\n"));
	}

	//take data from stream
	return _feed->read(data, sz);
}

int rqhead::write(const char *data, int sz, std::string *err) {
	//create stream
	if (_feed == nullptr) {
		_feed = std::unique_ptr<crlfeed>(new crlfeed());
	}

	//full stream
	if (_feed->done())
		return 0;

	//check data
	if (sz == 0 || data == 0) {
		//incompleted request
		safe_assign<std::string>(err, "incompleted request.");
		return -1;
	}

	//feed stream
	int fsz = _feed->write(data, sz);

	//parse head
	if (_feed->done()) {
		//parse query line
		if (!_feed->endr()) {
			if (_query.parse(_feed->next().c_str(), err) != 0)
				return -1;
		} else {
			//invalid request
			safe_assign<std::string>(err, "empty request.");
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

bool rqhead::done() const {
	if (_feed == nullptr)
		return false;
	return _feed->done();
}

///////////////////////////////////////////////request body class//////////////////////////////////////
int rqbody::read(char *data, int sz, std::string *err) {
	if (_entity == nullptr)
		return 0;

	return _entity->read(data, sz);
}

int rqbody::write(const char *data, int sz, std::string *err) {
	if (_entity == nullptr)
		return 0;

	return _entity->write(data, sz);
}

bool rqbody::done() const {
	if (_entity == nullptr)
		return true;
	return _entity->done();
}

///////////////////////////////////////////////request class//////////////////////////////////////
int request::read(char *data, int sz) {
	//taked size
	int tsz = 0;

	//take head data
	if (tsz < sz) {
		tsz += _head.read(data + tsz, sz - tsz);
	}

	//take body data
	if (tsz < sz) {
		tsz += _body.read(data + tsz, sz - tsz);
	}

	//size taked
	return tsz;
}

int request::write(const char *data, int sz) {
	//feed size
	int fsz = 0;

	//feed head
	if (!_head.done()) {
		fsz += _head.write(data + fsz, sz - fsz);
		if (_head.done()) {
			_body.
		}
	}

	//feed body
	fsz += _body.write(data + fsz, sz - fsz);

	//size feed
	return fsz;
}


END_CUBE_HTTP_NS
