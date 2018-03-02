#include <string.h>
#include "cube\http\buffer.h"
BEGIN_CUBE_HTTP_NS
int line_buffer::get(char *data, int sz) {
	int getsz = sz > (int)_data.length() ? (int)_data.length() : sz;
	memcpy(data, _data.c_str(), getsz);
	return getsz;
}

int line_buffer::put(const char *data, int sz) {
	int putsz = 0;
	while (_data.back() != '\n' && putsz < sz) {
		_data.append(1, *(data + putsz));
		putsz++;
	}

	return putsz;
}

bool line_buffer::full() const {
	return _data.back() == '\n';
}

int line_buffer::size() const {
	return _data.length();
}

const char * line_buffer::data() const {
	return _data.c_str();
}

void line_buffer::clear() {
	_data.clear();
}
END_CUBE_HTTP_NS
