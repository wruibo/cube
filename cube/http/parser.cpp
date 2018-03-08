#include "cube\http\parser.h"
BEGIN_CUBE_HTTP_NS
///////////////////////////////request message parser class////////////////////////////////////////
bool request_message_parser::has_body_done() const {
	return _request.has_entity_done();
}

int request_message_parser::on_head_line(const char *data, int sz) {
	//process start line
	if (_start_line) {
		_start_line = false;
		return _request.put_start_line(data, sz);
	}

	//process header line
	return _request.put_header_line(data, sz);
}

int request_message_parser::on_body_data(const char *data, int sz) {
	return _request.put_entity_data(data, sz);
}

///////////////////////////////request stream parser class////////////////////////////////////////
int request_stream_parser::feed(const char *data, int sz) {
	//check data size
	if (sz < 0)
		return -1;

	//no more stream data to feed
	if (sz == 0) {
		//set body complete flag
		_body_feed_completed = true;
		return 0;
	}

	//head has completed, feed body data
	if (_head_feed_completed)
		return _message_parser.on_body_data(data, sz);

	//head not completed, feed head data first
	int fsz = 0;
	while (fsz < sz) {
		fsz += _line_buffer.put(data+ fsz, sz- fsz);
		if (_line_buffer.full()) {
			//new message line
			std::string strline = _line_buffer.line();
			if (strline.empty()) {
				//set head completed flag
				_head_feed_completed = true;
				
				//send left body data to message parser
				int bsz = _message_parser.on_body_data(data + fsz, sz - fsz);
				if (bsz < 0)
					return -1;

				//add new body feed size
				fsz += bsz;

				break;
			} else {
				//send to message parser
				if (_message_parser.on_head_line(strline.data(), strline.length()) != 0)
					return -1;

				//clear current line buffer for next line
				_line_buffer.clear();
			}
		}
	}

	return fsz;
}

bool request_stream_parser::done() const {
	return _head_feed_completed && (_body_feed_completed || _message_parser.has_body_done());
}
END_CUBE_HTTP_NS
