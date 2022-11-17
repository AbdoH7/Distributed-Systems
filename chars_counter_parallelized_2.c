#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

char *buf;
int length;
int ascii[128]={0};
int num_threads=12;

int **arr;
void init(){
	arr = malloc(num_threads * sizeof(int *));
   	for(int i=0;i<num_threads; i++){
   		arr[i] = malloc(128 * sizeof(int));
   	}
}

void * worker( void *arg )
{
	int tid, portion_size, portion_remainder, start, end;  
	tid = *(int *)(arg);
	portion_size = length / num_threads;
	portion_remainder = length % num_threads;
	if(tid>=portion_remainder){
		start = tid * portion_size + portion_remainder;
		end = (tid+1) * portion_size + portion_remainder;
	}
	else{
		start = tid * portion_size + tid;
		end = (tid+1) * portion_size + (tid+1);
	}
	
	for(int i=start;i<end;i++){
    		arr[tid][(int)buf[i]]++;
    	}
}

int main(){
	int i,j;
	struct timeval tstart, tend;
  	double exectime;
	init();
	pthread_t * threads;
	threads = (pthread_t *) malloc( 128 * sizeof(pthread_t) );
	
	
    	FILE *f = fopen("./lorem.txt", "r");
    	if (f)
    	{
        	fseek(f, 0, SEEK_END);
        	length = ftell(f);
        	fseek(f, 0, SEEK_SET);
        	buf = malloc(length);
        	if (buf)
        	{
            		fread(buf, 1, length, f);
        	}
        	fclose(f);
    	}
    	
    	
    	gettimeofday( &tstart, NULL );
	for (i = 0; i < num_threads; ++i ) {
    		int *tid;
    		tid = (int *) malloc( sizeof(int) );
    		*tid = i;
    		pthread_create( &threads[i], NULL, worker, (void *)tid );
  	}

  	for (i = 0; i < num_threads; ++i ) {
    		pthread_join( threads[i], NULL );
  	}
  	
  	for(i=0;i<128;i++){
  		for(j=0;j<num_threads;j++){
  			ascii[i]+=arr[j][i];
  		}
  	}
  	
  	gettimeofday( &tend, NULL );
  	
  	for(int i=0;i<128;i++){
    		printf("Occurrences of Ascii %d = %d\n",i,ascii[i]);
    	}
    	
    	
  	exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
  	exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms   
  	printf("File Length: %d\n",length);
  	printf( "Execution time:%.3lf sec\n", exectime/1000.0);

	return 0;
}

