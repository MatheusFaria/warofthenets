#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
using namespace std;

class Log{
public:
	static void warn(string);
	static void error(string);
	static void info(string);
};

#endif
