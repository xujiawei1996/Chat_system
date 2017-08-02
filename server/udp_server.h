#ifndef _UDP_SERVER_
#define _UDP_SERVER_

#include<pthread.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<fcntl.h>
#include<map>
#include"log.h"
#include"pool.h"

class udp_server{
	public:
		udp_server(const std::string& _ip,int _port);
		int init_server();
		int recv_msg(std::string &out);
		int add_online_user(struct sockaddr_in *client);
		int send_msg(const std::string &in,struct sockaddr_in &peer,const socklen_t &len);
		int brocast_msg();
		~udp_server();
	private:
		udp_server(const udp_server&);
	private:
		std::string ip;
		int port;
		int sock;
		std::map<int,struct sockaddr_in> online_user;
		pool data_pool;
};


#endif
