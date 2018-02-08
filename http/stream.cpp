#include "cube\str\strip.h"
#include "cube\http\stream.h"
BEGIN_CUBE_HTTP_NS
////////////////////////CRLF buffer class///////////////////////
std::streamsize crlfbuffer::put(const char *data, std::streamsize sz) {
	std::streamsize szput = 0;

	while (_buffer.back() != '\n' && szput < sz) {
		_buffer.append(1, *(data + szput));
		szput++;
	}

	return szput;
}

std::string crlfbuffer::data() const {
	return cube::str::strip(_buffer);
}

const std::string &crlfbuffer::buffer() const {
	return _buffer;
}

bool crlfbuffer::full() const {
	return _buffer.back() == '\n';
}

void crlfbuffer::clear() {
	_buffer.clear();
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
