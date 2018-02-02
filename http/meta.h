#pragma once
#include "cube\http\def.h"
BEGIN_CUBE_HTTP_NS
//http body meta information
class meta {
public:
	meta() : _type(""), _lang(""), _encoding(""), _length(0), _range(""), _expires("") {}
	~meta() {}

	const std::string &type()  const { return _type; }
	void type(const std::string &type) { _type = type; }
	const std::string &lang()  const { return _lang; }
	void lang(const std::string &lang) { _lang = lang; }
	const std::string &encoding()  const { return _encoding; }
	void encoding(const std::string &encoding) { _encoding = encoding; }
	int length() const { return _length; }
	void length(int len) { _length = len; }
	const std::string &range()  const { return _range; }
	void range(const std::string &range) { _range = range; }
	const std::string &expires() const { return _expires; }
	void expires(const std::string &expires) { _expires = expires; }
private:
	int _length;
	std::string _type;
	std::string _lang;
	std::string _encoding;
	std::string _range;
	std::string _expires;
};
END_CUBE_HTTP_NS
