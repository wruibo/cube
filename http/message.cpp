#include "cube\http\message.h"
BEGIN_CUBE_HTTP_NS
////////////////////////////////////http message class/////////////////////////////
bool message::has_head_transfered() const {
	return !_header_lines.empty() && _header_lines.back().empty();
}

int message::set_head_line(const std::string &line, std::string *err) {
	if (_start_line.empty()) {
		//set start line
		if (!line.empty()) {
			_start_line = line;
		}
	} else {
		//parse header line


		//set header line
		_header_lines.push_back(line);

		//head transfer completed
		if (line.empty())
			return on_head_transfered(err);
	}

	return 0;
}

bool message::has_body_entity() const {
	return _entity != nullptr;
}

bool message::has_body_transfered() const {
	if (_entity != nullptr)
		return _entity->has_transfered();
	return true;
}

void message::set_body_transfered(std::streamsize sz) {
	if (_entity != nullptr) {
		_entity->set_transfered(sz);
	}
}

std::shared_ptr<std::iostream> message::get_head_stream() const {
	//set entity headers
	if (_entity != nullptr)
		_entity->set_headers(&_headers);

	//set general headers

	//set message headers
}

std::shared_ptr<std::iostream> message::get_body_stream() const {
	if (_entity != nullptr)
		return _entity->get_stream();
	return nullptr;
}

std::streamsize message::get_content_length() const {
	if (_entity != nullptr)
		return _entity->get_size();
	return 0;
}
END_CUBE_HTTP_NS
