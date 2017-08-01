#include"log.h"

std::string err_list[]={
	"NOTICE",
	"WARNING",
	"FATAL",
};

void write_log(const std::string &msg,int level)
{
	#ifdef _STDOUT_
		std::cerr<<"["<<msg<<"] ["<<err_list[level]<<"]"<<std::endl;
	#endif
}
