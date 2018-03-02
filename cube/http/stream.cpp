#include "cube\str\strip.h"
#include "cube\http\stream.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////data stream class/////////////////////////////////
int data_stream::read(char *data, int sz) {
	//no more data for reading
	if (endr())
		return 0;
	
	//current data size
	int len = (int)_data.length();
	//get read size
	int rsz = len - _rpos > sz ? sz : len - _rpos;
	//copy to destination data buffer
	memcpy(data, _data.c_str()+_rpos, rsz);
	//reset current read pos
	_rpos += rsz;
	//return read size
	return rsz;
}

int data_stream::write(const char *data, int sz) {
	if (endw())
		return 0;
	//current stream size
	int size = (int)_data.length();
	//left space for writting
	int left = _maxsz - size;
	//get write size
	int wsz = sz > left ? left : sz;

	if (_wpos == size) {
		//append data
		_data.append(data, wsz);
	} else {
		//replace data
		_data.replace(_wpos, wsz, data, wsz);
	}

	//reset the write position
	_wpos += wsz;

	return wsz;
}

int data_stream::seekr(int pos) {
	if (pos < _data.length()) {
		_rpos = pos;
		return 0;
	}
	return -1;
}

int data_stream::seekw(int pos) {
	if (pos < _maxsz) {
		//add blank data
		if (pos > _data.length()) {
			int blanksz = pos - _data.length();
			_data.append(blanksz, 0);
		}

		//set write position
		_wpos = pos;
		return 0;
	}

	return -1;
}

bool data_stream::endr() const {
	return !(_rpos < (int)_data.length());
}

bool data_stream::endw() const {
	return !(_data.length() < _maxsz);
}

int data_stream::size() {
	return _data.length();
}

std::string data_stream::data() {
	return _data;
}

//////////////////////////////////////////file stream class//////////////////////////////////////
int file_stream::read(char *data, int sz) {
	_file.read(data, sz);
	return (int)_file.gcount();
}

int file_stream::write(const char *data, int sz) {
	_file.write(data, sz);
	return sz;
}

int file_stream::seekr(int pos) {
	_file.seekg(pos);
	return 0;
}

int file_stream::seekw(int pos) {
	_file.seekp(pos);
	return 0;
}

bool file_stream::endw() const {
	return false;
}

bool file_stream::endr() const {
	return _file.eof();
}

int file_stream::size() {
	//save current get position
	std::streampos gpos = _file.tellg();

	//get file size
	_file.seekg(0, std::ios::end);
	std::streampos sz = _file.tellg();

	//restore get position
	_file.seekg(gpos, std::ios::beg);

	return (int)sz;
}

std::string file_stream::data() {
	std::string data("");

	//save current get position
	std::streampos gpos = _file.tellg();

	//set get pos to start
	_file.seekg(0);

	//read file content
	const int BUFSZ = 16 * 1024;
	char buf[BUFSZ] = { 0 };
	while (!_file.eof()) {
		_file.read(buf, BUFSZ);
		data.append(buf, (size_t)_file.gcount());
	}

	//reset get position
	_file.seekg(gpos, std::ios::beg);

	//return content read
	return data;
}
////////////////////////crlf stream class///////////////////////
int crlf_stream::read(char *data, int sz) {
	//no more data for reading
	if (endr())
		return 0;

	//current data size
	int len = (int)_data.length();
	//get read size
	int rsz = len - _rpos > sz ? sz : len - _rpos;
	//copy to destination data buffer
	memcpy(data, _data.c_str() + _rpos, rsz);
	//reset current read pos
	_rpos += rsz;
	//return read size
	return rsz;
}

int crlf_stream::write(const char *data, int sz) {
	if (endw())
		return 0;
	//current stream size
	int size = (int)_data.length();
	//left space for writting
	int left = _maxsz - size;
	//get write size
	int wsz = sz > left ? left : sz;

	if (_wpos == size) {
		//append data
		_data.append(data, wsz);
	} else {
		//replace data
		_data.replace(_wpos, wsz, data, wsz);
	}

	//reset the write position
	_wpos += wsz;

	return wsz;
}

int crlf_stream::seekr(int pos) {
	if (pos < _data.length()) {
		_rpos = pos;
		return 0;
	}
	return -1;
}

int crlf_stream::seekw(int pos) {
	if (pos < _maxsz) {
		//add blank data
		if (pos > _data.length()) {
			int blanksz = pos - _data.length();
			_data.append(blanksz, 0);
		}

		//set write position
		_wpos = pos;
		return 0;
	}

	return -1;
}

bool crlf_stream::endr() const {
	return !(_rpos < (int)_data.length());
}

bool crlf_stream::endw() const {
	return !(_data.length() < _maxsz);
}

int crlf_stream::size() {
	return _data.length();
}

std::string crlf_stream::data() {
	return _data;
}

////////////////////////http stream class///////////////////////
std::streamsize httpstream::read(char *data, std::streamsize sz) {
	return 0;
}

std::streamsize httpstream::write(const char *data, std::streamsize sz) {
	std::streamsize szw = 0;

	//create head stream
	if (_head_stream == nullptr) {
		_head_stream = std::shared_ptr<std::iostream>(new std::stringstream());
	}

	//process head lines
	while (!_message->has_head_transfered() && szw < sz) {
		std::streamsize szl = _crlfbuffer.put(data + szw, sz - szw);
		if (_crlfbuffer.full()) {
			//set new head line
			_message->set_head_line(_crlfbuffer.data());

			//write head stream data
			_head_stream->write(data + szw, szl);

			//clear buffer
			_crlfbuffer.clear();

			//create body entity stream
			if (_message->has_head_transfered()) {
				//get body output stream
				_body_stream = _message->get_body_stream();
			}
		}
		//add new write size
		szw += szl;
	}

	//process body data
	if (_body_stream != nullptr) {
		if (szw < sz) {
			_body_stream->write(data + szw, sz - szw);

			std::streamsize szb = sz - szw;
			_message->set_body_transfered(szb);

			szw += szb;
		} else {
			//body data hash transferd
			_message->set_body_transfered(0);
		}
	}

	return szw;
}

void httpstream::make() {

}

bool httpstream::full() const {
	return _message->has_head_transfered() && _message->has_body_transfered();
}

END_CUBE_HTTP_NS
