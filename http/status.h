#pragma once
#include "cube\http\version.h"
#include <map>
BEGIN_CUBE_HTTP_NS
//response status line class
class status {
public:
	//status setter
	class setter {
	public:
		setter(int code, const std::string &reason);
		~setter() {}
	};

	//default status, <int-code, <string-code, reason>>
	static std::map<int, std::pair<std::string, std::string>> _status;

public:
	status() : _code(""), _reason("") {}
	virtual ~status() {}

	//pack/parse status line with string
	std::string pack() const;
	int parse(const char *str, std::string *err = 0);

	//set status with specified code
	int set(int code, std::string *err = 0);

	//get/set status properties
	const std::string &code() { return _code; }
	void code(const std::string &code) { _code = code; }
	const std::string &version() { return _version.name(); }
	const std::string &reason() { return _reason; }
	void reason(const std::string &reason) { _reason = reason; }

private:
	//http version
	http::version _version;
	//response code
	std::string _code;
	//response description
	std::string _reason;
};
END_CUBE_HTTP_NS
