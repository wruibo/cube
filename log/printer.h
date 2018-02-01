#pragma once
#include "cube\log\def.h"
#include <string>
#include <fstream>
BEGIN_CUBE_LOG_NS
//printer class
class printer {
public:
	virtual void print(const char *msg) = 0;
};

//console printer class
class console_printer : public printer {
public:
	void print(const char *msg);
};

//file printer class
class file_printer : public printer {
public:
	file_printer(const std::string &dir, const std::string &name, log::cut ct = log::cut::none, uint fszlimit = -1);
	virtual ~file_printer();

	void print(const char *msg);

private:
	/*
	*	check and cut file when need
	*/
	void check_and_cut(int msgsz);

	/*
	*	get next print file
	*/
	std::string next_normal_file();
	std::string next_daily_file();
	std::string next_sized_file(int msgsz);

private:
	//output file
	std::ofstream _file;

	//file directory
	std::string _dir;
	//file name prefix
	std::string _name;
	//cut option
	log::cut _cutopt;

	//current day for daily cutting file
	int _currday;

	//file number for sized cutting file
	int _currnum;
	//current file size for sized cutting file
	uint _currfsz;
	//file size limit for sized cutting file
	uint _fszlimit;

};
END_CUBE_LOG_NS