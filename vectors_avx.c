#include"immintrin.h"
#include<stdio.h>

#define size 1024

int main() {
    double *v1 = aligned_alloc(32, sizeof(double) * size);
    double *v2 = aligned_alloc(32, sizeof(double) * size);
    double *v_res = aligned_alloc(32, sizeof(double) * size);
    
    __m256d x, y, z;

    for(int i = 0; i < MAX; i++) {
        *(v1+i) = i+1;
        *(v2+i) = i+1;
    }

    for(int i = 0; i < size; i+=4) {
        x = _mm256_load_pd(&v1[i]);
        y = _mm256_load_pd(&v2[i]);
        z = _mm256_add_pd(x,y);

        _mm256_store_pd(&v_res[i],z);
    }

    for(int i =0; i < size; i++) {
        printf("Result[%d] = %f\n",i,v_res[i]);
    }

    return 0;
}
