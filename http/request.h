#pragma once
#include "cube\http\uri.h"
#include "cube\http\message.h"
#include <mutex>
#include <memory>
BEGIN_CUBE_HTTP_NS
class request_line {

};

//http request class
class request : public message{
public:
	request() {}
	virtual ~request() {}

protected:
	virtual int on_head_transfered(std::string *err);

private:
	//http request method
	std::string _method;
	//http request uri
	http::uri _uri;
};
END_CUBE_HTTP_NS
