#pragma once
#include <string>
#include "cube\ns.h"
BEGIN_CUBE_HTTP_NS
class status {
public:
	status() : _version("1.1"), _code(""), _reason("") {}
	status(const std::string &version, const std::string &code, const std::string &reason) : _version(version), _code(code), _reason(reason) {}
	virtual ~status() {}

	std::string pack() const;
	int parse(const std::string &str);

public:
	const std::string &code() const { return _code; }
	void code(const std::string &code) { _code = code; }

	const std::string& version() const { return _version; }
	void version(const std::string &version) { _version = version; }

	const std::string& reason() const { return _reason; }
	void reason(const std::string &reason) {_reason = reason;}
	
private:
	//response code
	std::string _code;
	//response description
	std::string _reason;
	//http version
	std::string _version;
};
END_CUBE_HTTP_NS
