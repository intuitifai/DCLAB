#include<stdio.h>
#include<mpi.h>
int main(int argc, char *argv[]){
	int rank,size;
	int input;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank==0){
		printf("Enter the number here: ");
		scanf("%d",&input);
	}
	MPI_Bcast(&input,1,MPI_INT,0,MPI_COMM_WORLD);
	int i = 0, product = 1;
	int first = (input*rank)/size+1;
	int last = ((rank+1)*input)/size;
	for(i=first;i<=last;i++){
		product *= i;
	}
	int result = 1;
	MPI_Reduce(&product,&result,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);
	if(rank==0)
		printf("The factorial of the input %d is : %d",input,result);
	MPI_Finalize();
	return 0;
}
