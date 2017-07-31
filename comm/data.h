#ifndef __DATA_H__
#define __DATA_H__

#include<iostream>
#include<string>
#include"base_json.h"

class data{
		
public:
	std::string name;
	std::string school;
	std::string msg;
	std::string cmd;//这里封装命令
public:
	data();
	~data();
	int str_to_Serialize(std::string& str);
	int Serialize_to_str(std::string& in);

	
			
};



#endif
