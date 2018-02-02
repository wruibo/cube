#pragma once
#include "cube\log\def.h"
BEGIN_CUBE_LOG_NS
/*
*	get current time by specified unit
*@param u: in, time unit, year|month|day|hour|min|sec
*@return:
*	current time unit value
*/
int today();

/*
*	get current time string by specified format
*@param format: in, time string format
*@return:
*	time string
*/
std::string now(const char* format);

/*
*	format string
*@param format: in, format string
*@...: in, arguments meet the format
*@return:
*	formated string
*/
std::string format(const char *format, ...);

/*
*	test if specified file or directory is exist
*@param path: file path
*@return:
*	true if file exist, otherwise false
*/
bool fexist(const std::string &path);

/*
*	get specified file size
*@param path: in, file path
*@return:
*	size of file
*/
int fsize(const std::string &path, size_t &sz);

/*
*	test if specified path represents a directory
*@param path: file path
*@return:
*	true if is directory, otherwise false
*/
bool isdir(const std::string &path);

/*
*	make directory by specified directory path
*@param path: directory path
*@return:
*	0 for success, otherwise <0
*/
int mkdir(const std::string &path);

/*
*	make directory by specified directory path, create parent directory if not exist
*@param path: directory path
*@return:
*	0 for success, otherwise <0
*/
int mkdirs(const std::string &path);

/*
*	make full path by parent and its child path
*@param parent: in, parent path
*@param child: in, child name/path
*@return:
*	full path combined by parent and child
*/
std::string mkpath(const std::string &parent, const std::string &child);
END_CUBE_LOG_NS

