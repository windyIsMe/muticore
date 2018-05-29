#include <iostream>
#include "RecursiveMutex.hpp"
#include<pthread.h>
#include<unistd.h>
using namespace std;

pthread_t thd[5];
RecursiveMutex rm;

void *test(void *arg){
	pthread_t tid = pthread_self();
	//cout << tid << endl;
	for (int i = 0; i < 3; i++){
		rm.lock();		
	}
	for (int i = 0; i < 3; i++){
		sleep(1);
		cout << "thread[" << tid << "] is running." << endl;
		rm.unlock();
	}
}

int main(int argc, char const *argv[])
{
	void *status;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for(int i=0; i<5; i++){
		pthread_create(&thd[i], &attr, test, (void *)i);
	}
	pthread_attr_destroy(&attr);
	for(int i=0; i<5; i++)
	{
		pthread_join(thd[i], &status);
	}
	cout << "the end" << endl;
	return 0;
}

