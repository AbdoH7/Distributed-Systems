#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

int size=1000;
double **x;
double **m;
double **res;
int num_threads=12;

void init(){
	x = malloc(size * sizeof(double *));
   	m = malloc(size * sizeof(double *));
   	res = malloc(size * sizeof(double *));
   	for(int i=0;i<size; i++){
   		x[i] = malloc(size * sizeof(double));
   		m[i] = malloc(size * sizeof(double));
   		res[i] = malloc(size * sizeof(double));
   	}
}

void randd(){
	time_t t;
	srand((unsigned) time(&t));
	
	//randomly assign values to the 2 matrices
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			x[i][j]=rand() % 5;
			m[i][j]=rand() % 5;
		}
	}
}

void * worker( void *arg )
{
	int tid, portion_size, portion_remainder, row_start, row_end;  
	tid = *(int *)(arg);
	portion_size = size / num_threads;
	portion_remainder = size % num_threads;
	if(tid>=portion_remainder){
		row_start = tid * portion_size + portion_remainder;
		row_end = (tid+1) * portion_size + portion_remainder;
	}
	else{
		row_start = tid * portion_size + tid;
		row_end = (tid+1) * portion_size + portion_remainder;
	}
	  

	for (int i = row_start; i < row_end; ++i) {
		for (int j = 0; j < size; ++j) {
			res[i][j]=0;
			for (int k = 0; k < size; ++k) { 
				res[i][j] += x[ i ][ k ] * m[ k ][ j ];
			}
		}
	}
}

void print(double **matrix){
	for(int i=0;i<size;i++){
		printf("\nRow No.%d\n",i+1);
		for(int j=0;j<size;j++){
			printf("%f\t",matrix[i][j]);
		}
	}
	printf("\n");
}

int main(){
	struct timeval tstart, tend;
  	double exectime;
	init();
	randd();
	pthread_t * threads;
	threads = (pthread_t *) malloc( num_threads * sizeof(pthread_t) );
	
	gettimeofday( &tstart, NULL );
	for (int i = 0; i < num_threads; ++i ) {
    	int *tid;
    	tid = (int *) malloc( sizeof(int) );
    	*tid = i;
    	pthread_create( &threads[i], NULL, worker, (void *)tid );
  	}

  	for (int i = 0; i < num_threads; ++i ) {
    	pthread_join( threads[i], NULL );
  	}
  	gettimeofday( &tend, NULL );
  	
  	/*
  	print(x);
  	print(m);
  	print(res);
  	*/
  
  	exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
  	exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms   

  	printf( "matrix size: %dx%d ,Number of threads: %d\tExecution time:%.3lf sec\n",size,size,num_threads, exectime/1000.0);
  	
	
	return 0;
}

