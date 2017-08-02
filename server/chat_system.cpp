#include "udp_server.h"

void *brocast(void *arg)
{
	udp_server* serverp=(udp_server*)arg;
	while(1){
		serverp->brocast_msg();
	}
}

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		std::cout<<"usage: [ip] [port]"<<argv[0]<<std::endl;
	}

	udp_server server(argv[1],atoi(argv[2]));
	server.init_server();
	pthread_t id;
	pthread_create(&id,NULL,brocast,(void*)&server);
	std::string msg;
	while(1)
	{
		server.recv_msg(msg);
		std::cout<<"client echo#: "<<msg<<std::endl;
	}
	return 0;
}
