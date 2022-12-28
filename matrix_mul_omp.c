#include <stdio.h>

#define size 1024
double a[size][size], b[size][size], c[size][size];

void init(double m[size][size])
{
    int i, j;
    #pragma omp parallel for private(j)
    for(i = 0; i < size; ++i)
        for(j = 0; j < size; ++j)
            m[i][j] = i + 2*j;
}


void mult(double a[size][size], double b[size][size], double c[size][size])
{
    int i, j, k;
    #pragma omp parallel for private(i,k)
    // remove the prior line for the function to be sequential
    for(j = 0; j < size; ++j)
        for(i = 0; i < size; ++i){
       	    c[i][j]=0;
            for(k = 0; k < size; ++k)
                c[i][j] += a[i][k]*b[k][j];
                }
}

int main()
{
    init(a);
    init(b);

    mult(a, b, c);
    return 0;
}
