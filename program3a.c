#include<stdio.h>
#include<mpi.h>

int main(int argc, char* argv[]){
	int rank,size,tag= 1;
	int dest,src;
	int rc;
	char inmsg, outmsg= 'X';
	MPI_Init(&argc,&argv);
	MPI_Status stat;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank==0 && size>2){
		printf("\nOnly 2 task needed... removing extra..");
		src = 1;
		dest = 1;
		rc = MPI_Send(&outmsg,1,MPI_CHAR,dest,0,MPI_COMM_WORLD);
		rc = MPI_Recv(&inmsg,1,MPI_CHAR,src,0,MPI_COMM_WORLD,&stat);	
		printf("\nTask %d is communicated containing %c from %d to %d", rank,inmsg,stat.MPI_SOURCE,stat.MPI_TAG);
	}
	if(rank==1){
		src = 0;
		dest = 0;
		rc = MPI_Recv(&inmsg,1,MPI_CHAR,src,0,MPI_COMM_WORLD,&stat);
		rc = MPI_Send(&outmsg,1,MPI_CHAR,dest,0,MPI_COMM_WORLD);
		printf("\nTask %d is communicated containing %c from %d to %d", rank,inmsg,stat.MPI_SOURCE,stat.MPI_TAG);
	}
	if(rank>=2){
		printf("\nTask %d is communicated containing %c from %d to %d", rank,inmsg,stat.MPI_SOURCE,stat.MPI_TAG);
	}
	MPI_Finalize();
	return  0;
}
