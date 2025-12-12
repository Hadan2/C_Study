#include <stdio.h>
#include <stdlib.h>


int main () {
    int N,M,i,j;
    scanf("%d %d", &N, &M);

    int* arr = (int*)malloc(sizeof(int)*N);
    int* pre_sum = (int*)malloc(sizeof(int)*N);

    for(int k=0; k<N; k++){
        int t=0;
        scanf("%d", &t);
        arr[k] = t;
        if(k==0) {
            pre_sum[0] = t;
        }
        else {
            pre_sum[k] = pre_sum[k-1] + t;
        }
         
    }


    for(int k=0; k<M; k++){ 
        scanf("%d %d", &i, &j);
        int sum = pre_sum[j-1]; 
        if(i!=1) {
            sum-=pre_sum[i-2];
        }
        printf("%d\n", sum);
    }


   
    return 0;
}