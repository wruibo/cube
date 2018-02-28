#pragma once
#include "cube\fd\def.h"
BEGIN_CUBE_FILE_NS

/*
*	read all content of file by specified file path
*@param path: in, file path
*@param data: out, data in the file read
*@return:
*	0 for succcess, otherwise <0
*/
int read(const std::string &path, std::string &data);

/*
*	read all content of file by specified file path.
*NOTES:
*	do not forget free the return content memory
*@param path: in, file path
*@param sz: out, data read in bytes
*@return:
*	content of file or 0 if read file failed.
*/
char* read(const std::string &path, int &sz);

/*
*	write content to specified file, replace file if exists
*@param path: in, file path
*@param content: in, content want to write
*@param sz: in, size of content in byte
*@return:
*	0 for success, otherwise <0
*/
int write(const std::string &path, const char* content, int sz);

END_CUBE_FILE_NS
