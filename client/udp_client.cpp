#include "udp_client.h"

int udp_client::init_client()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0){
		write_log("socket error",FATAL);
		return -1;
	}
}

udp_client::udp_client(const std::string& _ip,const int &_port)
	:ip(_ip)
	,port(_port)
	,sock(-1)
{}

int udp_client::recv_msg(std::string &out)
{
	char buff[1024];
	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);
	int ret = recvfrom(sock,buff,sizeof(buff)-1,0,\
						(struct sockaddr*)&peer,&len);
	if(ret > 0)
	{
		buff[ret] = 0;
		out = buff;
		//add_online_user(peer);
		return 0;
	}
	return -1;
}

int udp_client::send_msg(const std::string &in)
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ip.c_str());
	int ret = sendto(sock,in.c_str(),in.size(),0,(struct sockaddr*)&server,sizeof(server));
	if(ret < 0){
		return -1;
	}
	return 0;
}

//int udp_client::brocast_msg()
//{
//	std::string msg = data_pool.get_data();
//	std::map<int,struct sockaddr_in>::iterator iter = online_user.begin();
//	for(;iter != online_user.end();iter++)
//		send_msg(msg,iter->second,sizeof(iter->second));
//	return 0;	
//}

udp_client::~udp_client()
{
		if(sock>0)
				close(sock);
}
