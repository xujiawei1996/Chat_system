#ifndef __WINDOW_H__
#define __WINDOW_H__

#include<iostream>
#include<string>
#include<ncurses.h>
//#include"comm.h"
#include<string.h>

class chat_window{

public:
	chat_window();
	~chat_window();
	WINDOW* create_win(int _h,int _w,int _y,int _x);
	void create_header();
	void create_output();
	void create_friends();
	void create_input();
	void put_str(WINDOW* win,int _y,int _x,std::string&str);
	void get_str(WINDOW *win,std::string &out);
	void clr_win_lines(WINDOW* _w,int begin,int lines);

public:
	WINDOW* header;
	WINDOW* output;
	WINDOW* friends;
	WINDOW* input;
};


#endif
