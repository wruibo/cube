#pragma once
#include "cube\fd\def.h"
#include "cube\fd\exp.h"
#include <string>
#include <vector>
BEGIN_CUBE_FD_NS
//exceptions
typedef cexception error;

/*
*	test if specified file or directory is exist
*@param path: file path
*@return:
*	true if file exist, otherwise false
*/
bool exist(const std::string &path);

/*
*	test if specified path represents a directory
*@param path: file path
*@return:
*	true if is directory, otherwise false
*/
bool isdir(const std::string &path);

/*
*	test if specified path represents a normal file
*@param path: file path
*@return:
*	true if is normal file, otherwise false
*/
bool isfile(const std::string &path);


/*
*	get file stat
*@param fd: in, file descriptor
*@param path: in, file path
*@param stat: out, file stat
*@return:
*	0 for success, otherwise <0
*/
int stat(int fd, filestat &stat);
int stat(const std::string &path, filestat &stat);

/*
*	get specified file size
*@param path: in, file path
*@return:
*	size of file
*/
int size(int fd, size_t &sz);
size_t size(const std::string &path);
int size(const std::string &path, size_t &sz);

/*
*	get file extension name
*@param path: in, file name
*@return:
*	file extension name
*/
std::string ext(const std::string &name);

/*
*	get file name from file path
*@param path: in, file path
*@return:
*	file name
*/
std::string name(const std::string &path);

/*
*	get the file's directory path from file path
*@param path: in, file path
*@return:
*	file's directory path
*/
std::string path(const std::string &path);

/*
*	find file/directory in the specified path
*@param path: in, directory path
*@param attrib: in, filter of file/directory attribute
*@param onlyname: in, want only file/dir name in return results
*@return:
*	find results
*/
std::vector<findres> find(const std::string &path, const char* spec = "*", int attrib = attrib::ALL, bool onlyvisible = true, bool onlyname = true);
std::vector<std::string> finds(const std::string &path, const char* spec = "*", int attrib = attrib::ALL, bool onlyvisible = true, bool onlyname = true);

/*
*	get the sub directories or files in the specified directory
*@param path: in, directory path
*@param onlyname: in, want only file/dir name in return results
*@return:
*	file or directory path vector
*/
std::vector<std::string> dirs(const std::string &path, bool onlyvisible = true, bool onlyname = true);
std::vector<std::string> files(const std::string &path, bool onlyvisible = true, bool onlyname = true);
END_CUBE_FD_NS
