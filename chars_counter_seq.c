#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


int main(){

	struct timeval tstart, tend;
  	double exectime;
	char *buf;
	int len;
	int length;
    	FILE *f = fopen("./lorem.txt", "r");
    	
    	int ascii[128]={0};

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
    	for(int i=0;i<length;i++){
    		ascii[(int)buf[i]]++;
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

