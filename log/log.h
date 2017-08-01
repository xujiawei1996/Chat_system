#ifndef _LOG_H_
#define _LOG_H_

#include<iostream>

#define NOCTICE 1
#define WARNING 2
#define FATAL 3


extern std::string err_list[];

void write_log(const std::string &msg,int level);


#endif
