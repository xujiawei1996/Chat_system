#ifndef _UDP_CLIENT__
#define _UDP_CLIENT__

#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include"log.h"
#include"pool.h"
#include"data.h"
#include"window.h"

class udp_client{
	public:
		udp_client(const std::string& _ip,const int &_port);
		int  init_client();
 		int recv_msg(std::string &out);
		int add_online_user(struct sockaddr_in *client);
		int send_msg(const std::string &in);
		~udp_client();
	private:
		udp_client(const udp_client &);
	private:
		std::string ip;
		int port;
		int sock;
};

#endif
