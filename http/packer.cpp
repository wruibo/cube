#include "cube\http\packer.h"
BEGIN_CUBE_HTTP_NS
int packer::pack(const header *header, std::string *str, std::string *err) {
	int sz = 0;
	char buf[BUFSZ] = { 0 };

	sz = snprintf(buf + sz, BUFSZ - sz, "\r\n");

	str->assign(buf, sz);
	return 0;
}

int packer::pack(const headers *headers, std::string *str, std::string *err) {
	for (int i = 0; i < headers->count(); i++) {
		std::string strheader("");
		pack(&headers->get(i), &strheader, err);
	}
}
END_CUBE_HTTP_NS
