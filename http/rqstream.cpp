#include "cube\http\rqstream.h"
BEGIN_CUBE_HTTP_NS
int rqstream::read(char *data, int sz) { 
	return _request.read(data, sz); 
}
int rqstream::write(const char *data, int sz) { 
	return _request.write(data, sz); 
}

bool rqstream::done() const { 
	return _request.done(); 
}
END_CUBE_HTTP_NS
