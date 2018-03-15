#include "cube\http\config.h"
#include "cube\http\response.h"
BEGIN_CUBE_HTTP_NS
////////////////////////////////////////response class///////////////////////////////////////////
std::string response::pack() const {
	std::string res("");

	//pack status line
	res.append(_status.pack());
	//pack headers
	res.append(_headers.pack());

	//pack empty line
	res.append("\r\n");

	//pack entity data
	res.append(_entity.get_data());

	return res;
}

void response::status(http::status s) {
	//set status line
	_status = s;

	//set default headers
	_headers.add("Server", http::config::server);
}

void response::redirect(const char *url, bool permanent) {
	//set status line
	if (permanent)
		_status = http::status_301_moved_permanently;
	else
		_status = http::status_302_found;

	//set general header
	_headers.add("Server", http::config::server);

	//set redirect location
	_headers.add("Location", url);
}

void response::content(const char *data, int sz, const char *type, const char *charset) {
	//set status line
	_status = http::status_200_ok;

	//set general header
	_headers.add("Server", http::config::server);

	//set entity data
	_entity.set_data(data, sz);

	//set entity type/charset
	_entity.set_type(type, charset);
}

void response::cookie(const std::string &name, const std::string &value, int maxage, const char *domain = config::domain, const char *path = "/") {
	_cookies.set(name, value, domain, path, maxage);
}
END_CUBE_HTTP_NS
