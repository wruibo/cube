#include "cube\http\feed.h"
BEGIN_CUBE_HTTP_NS
const std::string crlfeed::_tag("\r\n\r\n");

int crlfeed::read(char *data, int sz) {
	if (!endr()) {
		_stream->read(data, sz);
		return (int)_stream->gcount();
	}
	return 0;
}

int crlfeed::write(const char *data, int sz) {
	//stream not completed, need more data
	if (!_done) {
		//restore last tag match result
		int sztag = _tag.length();
		const char *tag = _tag.c_str(), *ptag = tag + _pos;

		//continue check the end tag
		const char *pdata = data, *sdata = data;
		while (pdata - data < sz && ptag - tag < sztag) {
			if (*ptag != *pdata) {
				//move data pos to next position
				sdata = ++pdata;
				//reset tag pos
				ptag = tag;
			} else {
				pdata++;
				ptag++;
			}
		}

		//tag found in stream
		if (ptag - tag == sztag) {
			//set completed flag
			_done = true;
			//write data
			int wsz = pdata - data;
			write(data, wsz);
			//return write size
			return wsz;
		}

		//tag not found, save current matched pos
		_pos = ptag - tag;
		//write all data
		write(data, sz);
		//all data feeded
		return sz;
	}

	//stream has completed
	return 0;
}

int crlfeed::size() const {
	//save current get pos
	std::streampos gpos = _stream->tellg();

	//get file size
	_stream->seekg(0, std::ios::end);
	std::streampos sz = _stream->tellg();

	//restore get pos
	_stream->seekg(gpos, std::ios::beg);

	return (int)sz;
}

bool crlfeed::endr() const {
	return _stream->eof();
}

bool crlfeed::endw() const {
	return done();
}

bool crlfeed::done() const {
	return _done;
}

bool crlfeed::empty() const {
	return size() == 0;
}

std::string crlfeed::next() {
	char buf[BUFSZ] = { 0 };
	if(!_stream->eof())
		_stream->getline(buf, BUFSZ);
	return std::string(buf);
}

END_CUBE_HTTP_NS
