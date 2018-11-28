#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){
	int A[4][4],B[4],gather[4],buf[4], size, rank,i=0,j=0,sum=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank == 0){
		printf("\nEnter the Matrix A: [16 elements]\n");
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)	
				scanf("%d",&A[i][j]);
		printf("\nEnter the Matrix B: [4 elements]\n");
		for(i=0;i<4;i++)
				scanf("%d",&B[i]);
	}
	MPI_Scatter(A,4,MPI_INT,buf,4,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(B,4,MPI_INT,0,MPI_COMM_WORLD);
	for(i=0;i<4;i++)
		sum += buf[i]*B[i];
	MPI_Gather(&sum,1,MPI_INT,gather,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0){
		printf("\nThe output is : \n");
		for(i=0;i<4;i++)
			printf("%d\t",gather[i]);
	}
	MPI_Finalize();
	return 0 ;
}
