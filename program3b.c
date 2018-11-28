#include<stdio.h>
#include<mpi.h>
int main(int argc, char* argv[]){
	int tag1=1,tag2=2,buf_send[2],buf_recv[2];
	int size,rank;
	MPI_Request req[20];
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int prev = rank-1;
	int next = rank+1;
	if(rank == 0)
		prev = size-1;
	if(rank == (size-1))
		next = 0;
	buf_send[0] = 10;
	buf_send[1] = 10;
	MPI_Irecv(&buf_recv[0],1,MPI_INT,prev,tag1,MPI_COMM_WORLD,&req[0]);
	MPI_Irecv(&buf_recv[1],1,MPI_INT,next,tag2,MPI_COMM_WORLD,&req[1]);
	MPI_Isend(&buf_send[0],1,MPI_INT,prev,tag2,MPI_COMM_WORLD,&req[2]);
	MPI_Isend(&buf_send[1],1,MPI_INT,next,tag1,MPI_COMM_WORLD,&req[3]);
	
	printf("\nTask %d communicated from %d to %d", rank,prev,next);
	MPI_Finalize();
	return 0;
}
