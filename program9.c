#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int product = 0;
pthread_mutex_t lock;
int main(){
	pthread_t prod,com;
	void* producer();
	void* consumer();
	pthread_create(&prod,NULL,producer,NULL);
	pthread_create(&com,NULL,consumer,NULL);
	pthread_exit(0);
}
void add_buffer(int i ){
	product = i;
}
int get_buffer(){
	return product;
}
void* producer(){
	printf("\n:::Producer Active::: ");
	int i = 0;
	for(i=0;i<10;i++){
		pthread_mutex_lock(&lock);
		add_buffer(i);
		printf("\nSend : %d",i);
		pthread_mutex_unlock(&lock);	
	}	
}

void* consumer(){
	printf("\n:::Consumer Active::: ");
	int i = 0;
	for(i=0;i<10;i++){
		pthread_mutex_lock(&lock);
		int rec = get_buffer();
		printf("\nRecieved : %d",i);
		pthread_mutex_unlock(&lock);
	}
}
