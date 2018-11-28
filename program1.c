#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<mpi.h>

void sorting(int* sorted, int count, int value){
	int i = 0;
	sorted[count]=value;
	for(i=0;i<count;i++){
		if(sorted[i]>sorted[i+1]){
			int temp = sorted[i];
			sorted[i] = sorted[i+1];
			sorted[i+1] = temp;
		}
	}
}

int main(int argc, char* argv[]){
	int size,rank,i;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	FILE* infile;
	infile = NULL;
	int sorted[100],value,count=0,tot;
	int gath_buf[10], temp[10];
	infile = fopen("loans.txt","r");
	if(infile == NULL){
		printf("Error! File Doesn't exits : loans.txt");
		return 0;
	}
	MPI_Scatter(&infile,1,MPI_INT,&tot,1,MPI_INT,0,MPI_COMM_WORLD);
	while(!feof(infile)){
		fscanf(infile,"%d\n",&value);
		sorting(sorted,count,value);
		++count;
	}
	int rev = count;
	for(i=0;i<count;i++){
		temp[--rev] = sorted[i];
	}
	MPI_Gather(&temp,1,MPI_INT,&gath_buf,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0){
	printf("\nSorted order: \n");
	for(i=0;i<count;i++)
	printf("%d\t",temp[i]);
	fclose(infile);
	}
	MPI_Finalize();
	return 0;
}
