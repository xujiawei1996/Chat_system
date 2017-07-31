#include"base_json.h"

int Serialize(Json::Value & _v,std::string& str)
{
	//序列化数据_v,这里是统一将数据先转为Json::value，再转为所要用的数据类型.
	Json::FastWriter _w;
	str = _w.write(_v);
	return 0;
}

Json::Value unSerialize(std::string &str,Json::Value &_v)
{
	Json::Reader _r;
	if(_r.parse(str,_v,false) < 0)
			return 0;
	return -1;
}
