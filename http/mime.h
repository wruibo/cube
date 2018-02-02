#pragma once
#include "cube\http\def.h"
#include <map>
BEGIN_CUBE_HTTP_NS
//mime class
class mime {
public:
	/*
	*	general mime types
	*/
	class form {
	public:
		static std::string utf8;
		static std::string gb2312;
		static std::string default;
	};
	class json {
	public:
		static std::string utf8;
		static std::string gb2312;
		static std::string default;
	};
	class octet {
	public:
		static std::string utf8;
		static std::string gb2312;
		static std::string default;
	};
	static std::string unknown;

	/*
	*	mime setter
	*/
	class setter {
	public:
		setter(const std::string &ext, const std::string &ctype) { set(ext, ctype); }
		~setter() {}
	};
public:
	/*
	*	get content type by extension name
	*/
	static std::string get(const std::string &ext, const std::string &charset);

	/*
	*	set content type by extension name & type
	*/
	static void set(const std::string &ext, const std::string &ctype);

private:
	//mime types, <extension, http content-type>
	static std::map<std::string, std::string> _types;
};
END_CUBE_HTTP_NS
