#pragma once
#include "cube\http\def.h"
#include <map>
#include <vector>
BEGIN_CUBE_HTTP_NS
//header class
class header {
	typedef std::pair<std::string, std::string> keyval;
	typedef std::vector<keyval> keyvals;
	typedef std::map<std::string, keyvals> items;
public:
	//default request header class
	class request {
	public:
		class setter {
		public:
			setter(const std::string &key, const std::string &value) { http::header::request::set(key, value); }
			~setter() {}
		};

		static const std::map<std::string, std::string> &get() { return _header; }
		static void set(const std::string &key, const std::string &value) { _header[key] = value; }

	private:
		//default request header
		static std::map<std::string, std::string> _header;
	};

	//default response header class
	class response {
	public:
		class setter {
		public:
			setter(const std::string &key, const std::string &value) { http::header::response::set(key, value); }
			~setter() {}
		};

		static const std::map<std::string, std::string> &get() { return _header; }
		static void set(const std::string &key, const std::string &value) { _header[key] = value; }
	private:
		//default request header
		static std::map<std::string, std::string> _header;
	};
public:
	header() {}
	virtual ~header() {}

	/*
	*	pack header data
	*@return:
	*	header crlf feed
	*/
	std::string pack() const;

	/*
	*	parse header data
	*@return:
	*	0 for success, otherwise <0
	*/
	int parse(const char *str, std::string *err = 0);

	/*
	*	set string value of specified item
	*@param item: in, item key
	*@param replace: in, replace item value if exist
	*@param format: in, format string
	*@return:
	*	self
	*/
	header &set(const std::string &key, const char *format, ...);
	header &set(const std::string &key, bool replace, const char *format, ...);
	header &set(const std::map<std::string, std::string> &items, bool replace = false);

	/*
	*	get string value of specified item
	*@param item: in, item key
	*@param default: in, default value if item not exist
	*@return:
	*	item string value or default value
	*/
	std::vector<std::string> get(const std::string &key) const;
	std::string get(const std::string &key, const char *default) const;

private:
	//header items, map<lower key, vector<<original key, value>>>
	header::items _items;
};
END_CUBE_HTTP_NS
