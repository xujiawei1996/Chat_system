#ifndef __BASE_JSON_H__
#define __BASE_JSON_H__

#include<iostream>
#include<json/json.h>

int Serialize(Json::Value &_v,std::string& str);
Json::Value unSerialize(std::string &str,Json::Value &_v);



#endif
