#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define SIZE 4

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE], AR[SIZE][SIZE], CR[SIZE][SIZE], n=0;

void read_matrix(int matrix[SIZE][SIZE]){
	
	int i = 0, j = 0;
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
			scanf("%d",&matrix[i][j]);	
}

void print_matrix(int matrix[SIZE][SIZE]){

	int i = 0, j = 0;
	for(i=0;i<SIZE;i++){
		printf("\n");
		for(j=0;j<SIZE;j++)
			printf(" %d",matrix[i][j]);
	}
}

int main(int argc, char* argv[]){
	
	int p, myrank;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	int i,j,k,from,to;
	from = myrank * SIZE/p;
	to = (myrank+1)* SIZE/p;
	//printf("\n n value: %d\n p value %d",n,p);
	if(n%p!=0){
		printf("Process cannot proceed");
		return 0;
	}
	if(myrank == 0){
		printf("\nEnter matrix A\n");
		read_matrix(A);
		printf("\nEnter matrix B\n");
		read_matrix(B);
	}
	
	int count = SIZE*SIZE/p;
	
	MPI_Bcast(B, count, MPI_INT, 0 , MPI_COMM_WORLD);
	MPI_Scatter(A, count, MPI_INT, AR[from], count, MPI_INT, 0, MPI_COMM_WORLD);
	
	for(i=from;i<to;i++){
		for(j=0;j<SIZE;j++){
		C[i][j] = 0;
			for(k=0;k<SIZE;k++){
				C[i][j] += AR[i][k] * B[k][j]; 	
			}
		}
	}
	MPI_Gather(C[from],count,MPI_INT, CR, count, MPI_INT,0 ,MPI_COMM_WORLD);
	if(myrank==0){
		print_matrix(A);
		printf("\n*\n");
		print_matrix(B);
		printf("\n=\n");
		print_matrix(CR);
	}
	
	MPI_Finalize();
	return 0;
	
}
