#include "cube\http\entity.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////entity class/////////////////////////////////////////
entity *entity::create(const headers *headers) {
	std::string type =	headers->get("content-type").value();
	if(type)
}

bool entity::has_transfered() const {
	return _size == _transfered;
}

void entity::set_transfered(std::streamsize sz) {
	if (sz == 0) {
		//transfer completed
		_size = _transfered;
	} else {
		//add new transfered size
		_transfered += sz;
	}	
}

std::streamsize entity::get_size() const {
	return _size;
}

END_CUBE_HTTP_NS
