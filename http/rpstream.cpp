#include "cube\http\rpstream.h"
BEGIN_CUBE_HTTP_NS
int rpstream::read(char *data, int sz) {
	return _response.read(data, sz);
}
int rpstream::write(const char *data, int sz) {
	return _response.write(data, sz);
}

bool rpstream::done() const {
	return _response.done();
}
END_CUBE_HTTP_NS
