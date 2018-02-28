#include "cube\fd\file.h"
#include <io.h>
#include <fstream>
BEGIN_CUBE_FILE_NS
////////////////////////////////////////////////file class//////////////////////////////////////////////////
int read(const std::string &path, std::string &data) {
	//clear out data first
	data.clear();

	//read content from file
	std::ifstream ifs(path, std::ifstream::in | std::ifstream::binary);
	if (!ifs.is_open())
		return -1;

	//read buffer
	const std::streamsize BUFSZ = 32 * 1024;
	char buf[BUFSZ] = { 0 };

	//process each file line
	ifs.read(buf, BUFSZ);
	while (ifs.gcount() > 0) {
		//append data
		data.append(buf, (size_t)ifs.gcount());

		//check file
		if (!ifs.good())
			break;

		//next line
		ifs.read(buf, BUFSZ);
	}

	return 0;
}


char* read(const std::string &path, int &sz) {
	// open file
	FILE * pf = fopen(path.c_str(), "rb");
	if (pf == NULL) {
		return NULL;
	}

	// get file size
	int file_size = (int)_filelength(_fileno(pf));
	if (file_size < 0) {
		fclose(pf);
		return NULL;
	}

	//read data
	char *content = new char[file_size];
	size_t rdsz = fread(content, sizeof(char), file_size, pf);
	if (rdsz != (size_t)file_size) {
		delete[]content;
		fclose(pf);
		return NULL;
	}

	//close file
	fclose(pf);

	//set data size read
	sz = file_size;

	return content;

}

int write(const std::string &path, const char* content, int sz) {
	//open file
	FILE * pf = fopen(path.c_str(), "wb");
	if (pf == NULL) {
		return -1;
	}

	//write to file
	size_t wsz = fwrite(content, sizeof(char), sz, pf);
	if (wsz != sz) {
		fclose(pf);
		return -1;
	}

	//close file
	fclose(pf);

	return 0;
}
END_CUBE_FILE_NS