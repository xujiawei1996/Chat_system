#ifndef _POOL_H_
#define _POOL_H_

#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<semaphore.h>

class pool{
	
	public:
		pool(int size);
		int get_data(std::string &out);
		int put_data(const std::string &in);
		~pool();
	private:
		pool(const pool &);	
	private:
		int c_step;
		int p_step;
		sem_t c_sem;
		sem_t p_sem;
		std::vector<std::string> data_pool;
		int cap;
};


#endif
