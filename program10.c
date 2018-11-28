#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX 10
int number = 0;
pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sc = PTHREAD_COND_INITIALIZER;
pthread_cond_t sp = PTHREAD_COND_INITIALIZER;

void* consumer(){
	printf("\n\t\t::Hello Consumer::\n");
	while(1){
		pthread_mutex_lock(&mu);
		pthread_cond_signal(&sp);
		pthread_cond_wait(&sc,&mu);
		printf("\t\t::Consumer : %d\n",number);
		pthread_mutex_unlock(&mu);
		if(number == MAX){
			printf("\n\t\t::Consumer Finished::\n");
			break;
		}
	}
}

void* producer(){
	printf("\n\t\t::Hello Producer::\n");
	while(1){
		pthread_mutex_lock(&mu);
		number++;
		pthread_cond_signal(&sc);
			pthread_cond_wait(&sp,&mu);
		printf("\t\t::Producer: %d\n",number);
		pthread_mutex_unlock(&mu);
		if(number == MAX){
			printf("\t\t::Producer Done\n");
			break;
		}
	}
}

int main(){
	pthread_t prod,cons;
	pthread_create(&prod,NULL,producer,NULL);
	pthread_create(&cons,NULL,consumer,NULL);
	pthread_join(prod,NULL);
	pthread_join(cons,NULL);
	return 0;
}
