#include "udp_client.h"
#include"data.h"
#include"window.h"
#include<signal.h>

typedef struct{
	udp_client *cp;
	chat_window* wp;
}net_window_t,*net_window_p;

std::string name;
std::string school;
std::string msg;
std::string cmd;
std::vector<std::string> flist;//friendslist
udp_client *sig_client = NULL;

void *show_header(void *arg){
	net_window_p objs = (net_window_p)arg;
	udp_client *client = objs->cp;
	chat_window *win = objs->wp;

	win->create_header();
	wrefresh(win->header);

	int i = 1,j = 1;
	std::string runing = "Welcome to chat system";

	while(1){
		int _y,_x;
		getmaxyx(win->header,_y,_x);
		win->clr_win_lines(win->header,_y/2,1);
		win->create_header();
		win->put_str(win->header,_y/2,j++,runing);
		if(j >= _x - runing.size() - 1)
			j = 1;
		wrefresh(win->header);
		usleep(200000);
	}
}

void add_user(std::string user)
{
	std::vector<std::string>::iterator iter = flist.begin();
	for(;iter != flist.end();++iter)
	{
		if(user == *iter)
			return;
	}
	flist.push_back(user);
}

void del_user(std::string user)
{
	std::vector<std::string>::iterator iter = flist.begin();
	for(;iter != flist.end();++iter)
	{
		if(user == *iter)
		{
			iter = flist.erase(iter);
			return;
		}
		else
			return;			
	}
}

void *show_output_fl(void *arg){
	net_window_p objs = (net_window_p)arg;
	udp_client *client = objs->cp;
	chat_window *win = objs->wp;
	win->create_output();
	wrefresh(win->output);
	win->create_friends();
	wrefresh(win->friends);

	int _w,_h;
	int i = 1;
	std::string recv_str;
	std::string friends;

	//data d;
	//std::string show_str = d.name;
	//show_str += "-";
	//show_str += d.school;
	//friends = show_str;

	while(1){
		client->recv_msg(recv_str);

	    data d;
		d.Serialize_to_str(recv_str);

		std::string show_str = d.name;
		show_str += "-";
		show_str += d.school;
		friends = show_str;

		if(d.cmd == "QUIT"){
			del_user(friends);
	      	wrefresh(win->friends);
		}else{

	      	show_str += ":#";
	      	show_str += d.msg;
	      	
	      	win->put_str(win->output,i++,2,show_str);
	      	
	      	getmaxyx(win->output,_h,_w);
	      	if(i >= _h-1)
	      	{
	      		sleep(1);
	      		i = 1;
	      		win->clr_win_lines(win->output,1,_h-1);
	      		win->create_output();
	      	}
	      	wrefresh(win->output);

	      	add_user(friends);
	      	int j = 0;
	      	for(;j<flist.size();++j){
	      		win->put_str(win->friends,j+1,2,flist[j]);
	      	}
	      	wrefresh(win->friends);

	      	usleep(300000);
		}
	}
}

void *show_input(void *arg){
	net_window_p objs = (net_window_p)arg;
	udp_client *client = objs->cp;
	chat_window *win = objs->wp;

	std::string win_in;
	std::string send_str;
	
	std::string tips = "Please Enter#:";
	while(1){
		win->create_input();
		win->put_str(win->input,1,2,tips);
		win->get_str(win->input,win_in);
	
		
		data d;
		d.name = name;
		d.school = school;
		d.msg = win_in;
		d.cmd = cmd;
		d.str_to_Serialize(send_str);
		client->send_msg(send_str);

		win->clr_win_lines(win->input,1,1);
	
		win->create_input();
		win->put_str(win->input,1,2,tips);
		wrefresh(win->input);
		usleep(300000);
	}
}

void quit(int sig)
{
	data d;
	d.name = name;
	d.school = school;
	d.msg = "";
	d.cmd = "QUIT";
	std::string send_str;
	d.str_to_Serialize(send_str);
	sig_client->send_msg(send_str);
	
	endwin();
	exit(1);
}

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		std::cout<<"usage: [ip] [port]"<<argv[0]<<std::endl;
	}
	
	std::cout<<"Please input your name:#";
	std::cin>>name;
	std::cout<<"Please input your school:#";
	std::cin>>school;

	udp_client client(argv[1],atoi(argv[2]));
	client.init_client();
	chat_window win;

	sig_client = &client;
	signal(2,quit);

	//这里怎么拿到win和client的方法
	net_window_t nw = {&client,&win};
	
	//创建三个线程，一个控制头，一个控制中间输出的线程，一个控制输入的线程
	pthread_t theader,toutput_fl,tinput;
	pthread_create(&theader,NULL,show_header,&nw);
	pthread_create(&toutput_fl,NULL,show_output_fl,&nw);
	pthread_create(&tinput,NULL,show_input,&nw);
	
	pthread_join(theader,NULL);
	pthread_join(toutput_fl,NULL);
	pthread_join(tinput,NULL);
//	data write;
//	std::cout<<"your name#";
//	std::string name;
//	std::cin>>write.name;
//
//	std::cout<<"your school#";
//	std::string school;
//	std::cin>>write.school;

//	std::cout<<"your msg#";
//	std::string msg;
//	std::cin>>write.msg;

//	std::cout<<"your cmd#";
//	std::string cmd;
//	std::cin>>write.cmd;

//	while(1){
//
//		std::cout<<"please enter#";
//		fflush(stdout);
//
// 		std::cout<<"your msg#";
// 		std::string msg;
// 		std::cin>>write.msg;
//		std::string out;
//		write.str_to_Serialize(out);
//		client.send_msg(out);
//	//	char buf[1024];
//	//	ssize_t s = read(0,buf,sizeof(buf)-1);
//	//	if(s > 0){
//	//		buf[s] = 0;
//	//		write.str_to_Serialize(write);
//	//		client.send_msg(data1);
//	//	}
//
//		std::string in;
//		client.recv_msg(in);
//		std::cout<<"server echo# "<<in<<std::endl;
//		//win.get_str(win.input,msg);
//	
//		//输出序列化转为str的信息
//		data r;
//		r.Serialize_to_str(in);
//		std::cout<<name<<"-"<<school<<"#"<<in<<std::endl;
//	}
	return 0;
}
