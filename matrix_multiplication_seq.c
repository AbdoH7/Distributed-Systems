#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int size=10000;
double **x;
double **m;
double **res;

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
	
	gettimeofday( &tstart, NULL );
	for (int i = 0; i < size; i++) {
        	for (int j = 0; j < size; j++) {
            	res[i][j] = 0;
            		for (int k = 0; k < size; k++) {
                		res[i][j] += x[i][k] * m[k][j];
            			}
        		}
    	}
    	gettimeofday( &tend, NULL );
    	exectime = (tend.tv_sec - tstart.tv_sec) * 1000.0; // sec to ms
  	exectime += (tend.tv_usec - tstart.tv_usec) / 1000.0; // us to ms   
  	printf( "Matrix size: %dx%d, Execution time:%.3lf sec\n",size, size, exectime/1000.0);
  	
  	return 0
}

