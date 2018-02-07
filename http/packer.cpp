#include "cube\http\packer.h"
BEGIN_CUBE_HTTP_NS
std::string packer::pack(const header &header) {
	int sz = 0;
	char buf[BUFSZ] = { 0 };

	sz = snprintf(buf + sz, BUFSZ - sz, "\r\n");
	return std::string(buf, sz);
}

std::string packer::pack(const headers &headers) {
	for (int i = 0; i < headers->count(); i++) {
		std::string strheader("");
		pack(&headers->get(i), &strheader, err);
	}
}
END_CUBE_HTTP_NS
