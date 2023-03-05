#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

char message[] = "hello world";
int thread_finished = 0;

void * thread_function(void *arg)
{
	printf("thread_function is running. Argument is %s\n", message);
	sleep(4);
	printf("second thread set finished flag, and exit now\n");
	thread_finished =1;
	pthread_exit(NULL);
}

int main()
{
	int res;
	pthread_t a_thread;

	pthread_attr_t thread_attr;

	//设置属性
	res = pthread_attr_init(&thread_attr);
	if(res!=0) {
		perror("attribute create failed\n");
		exit(EXIT_FAILURE);
	}
	res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
	if(res!=0) {
		perror("setting detached failed\n");
		exit(EXIT_FAILURE);
	}

	//按照设定的属性创建线程
	res = pthread_create(&a_thread, &thread_attr, thread_function, (void*)message);
	if(res!=0) {
		perror("thread create failed\n");
		exit(EXIT_FAILURE);
	}

	pthread_attr_destroy(&thread_attr); //线程创建完，属性变量就可以销毁了
	while (!thread_finished) {
		printf("waiting for thread to say it finished\n");
		sleep(1);
	}
	printf("other thread finished\n");
	exit(EXIT_SUCCESS);
}


