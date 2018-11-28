#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>	
int main(int argc, char* argv[]){
	int r1,c1,r2,c2,i,j,tid=0,k;
	clock_t tic,toc;
	printf("\nEnter the rows and columns of matrix A: ");
	scanf("%d%d",&r1,&c1);
	printf("\nEnter the rows and columns of matric B: ");
	scanf("%d%d",&r2,&c2);
	if(c1!=r2){
		printf("\nUsage: Please Enter the correct dimensions both matrix");
		return 0;
	}
	int A[r1][c1], B[r2][c2], result[r1][c2];
	printf("\nEnter the Elements of the matrix A: \n");
	for(i=0;i<r1;i++)
		for(j=0;j<c1;j++)
			scanf("%d",&A[i][j]);
	printf("\nEnter the Elements of the matrix B: \n");
	for(i=0;i<r2;i++)
		for(j=0;j<c2;j++)
			scanf("%d",&B[i][j]);
	//resultant matrix;
	for(i=0;i<r1;i++)
		for(j=0;j<c2;j++)
			result[i][j] = 0;
	tic = clock();
	#pragma omp parallel num_threads(3) shared(r1,c1,r2,c2,result) private(i,j,k,tid)
	{
		tid = omp_get_thread_num();
		#pragma omp for
		for(i=0;i<r1;i++){
			printf("\nThread : %d and Value : %d \n",tid,i);
			for(j=0;j<c2;j++){
				for(k=0;k<c1;k++){
					result[i][j] += A[i][k] * B[k][j];
				}
			}
		}
	}
	toc = clock();
	double timeTaken = (toc-tic)/CLOCKS_PER_SEC;
	printf("\nOutput matrix: \n");
	for(i=0;i<r1;i++){
		printf("\n");
		for(j=0;j<c2;j++){
			printf("%d\t",result[i][j]);
		}
	}
	printf("Time taken : %f", timeTaken);
	return 0;
}
