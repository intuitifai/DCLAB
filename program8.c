#include<stdio.h>
#include<omp.h>
int main(int argc, char* argv[]){
	char words[100],filename[10] = "words.txt";
	int count = 0;
	int tid = 0;
	FILE* f;
	#pragma omp parallel num_threads(2) firstprivate(count) private(f,tid,words) shared(filename)
	{
		tid = omp_get_thread_num();
		#pragma omp sections
		{
			#pragma omp section
			{
				f = fopen(filename,"r");
				if(f){
					while(!feof(f)){
						
						fscanf(f,"%s",words);
						if(feof(f))
							break;
						if(strcmp(words,"Elizabeth")==0)
							count= count+1;
						
						//printf("\n%s\n",words);
					}
					printf("\nElizbeth Count : %d ", count);
				}
				fclose(f);
			}
			#pragma omp section
			{
				f = fopen(filename,"r");
				while(!feof(f))
				{
					fscanf(f, "%s", words);
					if(feof(f))
						break;
					if(strcmp("Jane", words) == 0)
						count++;
					
				}
				printf("\nJane Count : %d ", count);
				fclose(f);
			}
		}
	}
}
