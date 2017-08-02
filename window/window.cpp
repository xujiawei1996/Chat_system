#include"window.h"

chat_window::chat_window()
{
	initscr();
}

//给窗体画线
WINDOW* chat_window::create_win(int _h,int _w,int _y,int _x)
{
	WINDOW *win = newwin(_h,_w,_y,_x);
	box(win,0,0);
	return win;
}

void chat_window::create_header()
{
	int _h = LINES/5;
	int _w = COLS;
	int _y = 0;
	int _x = 0;
	header = create_win(_h,_w,_y,_x);
	wrefresh(header);
}

void chat_window::create_output()
{
	int _h = (3*LINES)/5;
	int _w = (4*COLS)/5;
	int _y = LINES/5;
	int _x = 0;
	output = create_win(_h,_w,_y,_x);
	wrefresh(output);
}

void chat_window::create_friends()
{
	int _h = (3*LINES)/5;
	int _w = COLS/5;
	int _y = LINES/5;
	int _x = (4*COLS)/5;
	friends = create_win(_h,_w,_y,_x);
	wrefresh(friends);
}

void chat_window::create_input()
{
	int _h = LINES/5;
	int _w = COLS;
	int _y = (4*LINES)/5;
	int _x = 0;
	input = create_win(_h,_w,_y,_x);
	wrefresh(input);
}

chat_window::~chat_window()
{
	delwin(header);
	delwin(output);
	delwin(friends);
	delwin(input);
	endwin();
}

void chat_window::get_str(WINDOW *win,std::string &out)
{
	char msg[1024];
	msg[0] = 0;
	wgetnstr(win,msg,1024);
	out = msg;
	wrefresh(win);
}

void chat_window::put_str(WINDOW* win,int _y,int _x,std::string&str)
{
	mvwaddstr(win,_y,_x,str.c_str());
	wrefresh(win);
}

void chat_window::clr_win_lines(WINDOW* _w,int begin,int lines)
{
	while(lines-- > 0)
	{
		wmove(_w,begin++,0);
		wclrtoeol(_w);
	}
}

//int main()
//{
//	chat_window win;
//	win.create_header();
//	wrefresh(win.header);
//	win.create_output();
//	wrefresh(win.output);
//	win.create_friends();
//	wrefresh(win.friends);
//	win.create_input();
//	wrefresh(win.input);
//	
//	std::string tips = "Please Enter#";
//	win.put_str(win.input,1,2,tips);
//	wrefresh(win.input);
//	
//	std::string runing = "Welcome to chat system";
//
//	int i = 1,j = 1;
//	int _h,_w;
//	while(1){
//		
//		int _y,_x;
//		getmaxyx(win.header,_y,_x);
//		win.clr_win_lines(win.header,_y/2,1);
//		win.create_header();
//		win.put_str(win.header,_y/2,j++,runing);
//		if(j >= _x)
//			j = 1;
//		wrefresh(win.header);
//
//		win.put_str(win.output,i,2,tips);
//		wrefresh(win.output);
//		usleep(20000);
//		i++;
//		getmaxyx(win.output,_h,_w);
//		i %= (_h-1);
//		if(i == 0){
//			win.clr_win_lines(win.output,1,_h-1);
//			i = 1;
//			win.create_output();
//			wrefresh(win.output);
//		}
//	}
//
//
//
//}
