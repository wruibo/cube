#include "cube\http\mime.h"
BEGIN_CUBE_HTTP_NS
//////////////////////////////////////////mime class/////////////////////////////////////////
std::string mime::json::default("application/json");
std::string mime::octet::default("application/octet-stream");
std::string mime::form::default("application/x-www-form-urlencoded");

std::string mime::json::utf8("application/json;charset=utf-8");
std::string mime::octet::utf8("application/octet-stream;charset=utf-8");
std::string mime::form::utf8("application/x-www-form-urlencoded;charset=utf-8");

std::string mime::json::gb2312("application/json;charset=gb2312");
std::string mime::octet::gb2312("application/octet-stream;charset=gb2312");
std::string mime::form::gb2312("application/x-www-form-urlencoded;charset=gb2312");

std::string mime::unknown("");

std::map<std::string, std::string> mime::_types;

mime::setter mime_json("json", "application/json");
mime::setter mime_octet("octet", "application/octet-stream");
mime::setter mime_form("form", "application/x-www-form-urlencoded");

std::string mime::get(const std::string &ext, const std::string &charset) {
	std::string res("");

	//get relate mime type
	std::map<std::string, std::string>::const_iterator citer = _types.find(ext);
	if (citer != _types.end()) {
		res.append(citer->second);
	}

	//append content charset
	if (!charset.empty()) {
		if (!res.empty())
			res.append(";charset=" + charset);
		else
			res.append("charset=" + charset);
	}

	return res;
}

void mime::set(const std::string &ext, const std::string &ctype) {
	_types[ext] = ctype;
}
END_CUBE_HTTP_NS
