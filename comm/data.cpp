#include"data.h"


data::data()
{}


data::~data()
{}

int data::str_to_Serialize(std::string& str)
{
	Json::Value root;
	root["name"]=name;
	root["school"]=school;
	root["msg"]=msg;
	root["cmd"]=cmd;
	return Serialize(root,str);
}

int data::Serialize_to_str(std::string& in)
{
	Json::Value root;
	unSerialize(in,root);
	name=root["name"].asString();
	school=root["school"].asString();
	msg=root["msg"].asString();
	cmd=root["cmd"].asString();
}
