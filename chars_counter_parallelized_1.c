#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

char *buf;
int length;
int ascii[128]={0};

void * worker( void *arg )
{
	int tid, portion_size, portion_remainder, row_start, row_end;  
	tid = *(int *)(arg);
	
	for(int i=0;i<length;i++){
    		if(buf[i]==tid) ascii[tid]++;
    	}
}

int main(){
	struct timeval tstart, tend;
  	double exectime;
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
	for (int i = 0; i < 128; ++i ) {
    		int *tid;
    		tid = (int *) malloc( sizeof(int) );
    		*tid = i;
    		pthread_create( &threads[i], NULL, worker, (void *)tid );
  	}

  	for (int i = 0; i < 128; ++i ) {
    		pthread_join( threads[i], NULL );
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

