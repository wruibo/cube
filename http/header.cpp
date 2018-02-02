#include "cube\http\header.h"
#include "cube\str\case.h"
#include "cube\str\part.h"
#include "cube\str\format.h"
#include <stdarg.h>
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////header class/////////////////////////////////////////
std::map<std::string, std::string> http::header::request::_header;
std::map<std::string, std::string> http::header::response::_header;

http::header::request::setter request_accept("Accept", "*/*");
http::header::request::setter request_set_user_agent("User-Agent", "cube");
http::header::request::setter request_accept_encoding("Accept-Encoding", "gzip, deflate");
http::header::response::setter response_server("Server", "Cube/1.0");

std::string header::pack() const {
	//header data
	int sz = 0;
	char data[BUFSZ] = { 0 };

	//process each item
	header::items::const_iterator iter = _items.begin(), iterend = _items.end();
	while (iter != iterend) {
		for (size_t i = 0; i < iter->second.size(); i++) {
			sz += snprintf(data + sz, BUFSZ - sz, "%s: %s\r\n", iter->second[i].first.c_str(), iter->second[i].second.c_str());
		}
		iter++;
	}

	//add last "\r\n"
	sz += snprintf(data + sz, BUFSZ - sz, "\r\n");
	return std::string(data, sz);
}

int header::parse(const char *str, std::string *err) {
	//check data
	std::vector<std::string> item;
	str::part(str, ":", item, 2);
	if (item.size() != 2) {
		safe_assign<std::string>(err, str::format("header: %s invalid header", str));
		return -1;
	}

	//parse header
	std::string key = str::lower(item[0]);
	header::items::iterator iter = _items.find(key);
	if (iter == _items.end()) {
		_items.insert(std::pair<std::string, header::keyvals>(key, header::keyvals()));
	}
	_items[key].push_back(header::keyval(item[0], item[1]));

	return 0;
}

header &header::set(const std::string &key, const char *format, ...) {
	//format value string
	char buf[BUFSZ] = { 0 };
	va_list va;
	va_start(va, format);
	vsnprintf(buf, BUFSZ, format, va);
	va_end(va);

	//formatted value
	std::string val(buf);

	//set header value
	_items[key] = header::keyvals();
	_items[key].push_back(header::keyval(key, val));

	return *this;
}

header& header::set(const std::string &key, bool replace, const char *format, ...) {
	//format value string
	char buf[BUFSZ] = { 0 };
	va_list va;
	va_start(va, format);
	vsnprintf(buf, BUFSZ, format, va);
	va_end(va);

	//formatted value
	std::string val(buf);

	//set header value
	header::items::iterator iter = _items.find(key);
	if (iter != _items.end()) {
		if (replace) {
			iter->second.clear();
		}
		iter->second.push_back(header::keyval(key, val));
	} else {
		_items[key] = header::keyvals();
		_items[key].push_back(header::keyval(key, val));
	}

	return *this;
}

header &header::set(const std::map<std::string, std::string> &items, bool replace) {
	std::map<std::string, std::string>::const_iterator citer = items.begin(), citerend = items.end();
	while (citer != citerend) {
		std::string key = cube::str::lower(citer->first);
		header::items::iterator iter = _items.find(key);
		if (iter != _items.end()) {
			if (replace) {
				iter->second.clear();
			}
			iter->second.push_back(header::keyval(citer->first, citer->second));
		} else {
			header::keyvals kvs;
			kvs.push_back(header::keyval(citer->first, citer->second));
			_items.insert(std::pair<std::string, header::keyvals>(citer->first, kvs));
		}

		citer++;
	}

	return *this;
}

std::vector<std::string> header::get(const std::string &item) const {
	std::vector<std::string> result;
	header::items::const_iterator iter = _items.find(cube::str::lower(item));
	if (iter != _items.end()) {
		for (size_t i = 0; i < iter->second.size(); i++) {
			result.push_back(iter->second[i].second);
		}
	}

	return result;
}

std::string header::get(const std::string &item, const char *default) const {
	header::items::const_iterator iter = _items.find(cube::str::lower(item));
	if (iter != _items.end() && iter->second.size() > 0) {
		return iter->second[0].second;
	} else {
		return default;
	}
}
END_CUBE_HTTP_NS
