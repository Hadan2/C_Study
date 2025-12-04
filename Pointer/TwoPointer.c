#include <stdlib.h>
#include <stdio.h>
#define MAX(a,b) ((a)>(b) ? (a) : (b))

int main() {
    int N,K;
    scanf("%d %d", &N, &K);

    int *arr = (int*)malloc(sizeof(int)*N);

    for(int i=0; i<N; i++) {
        scanf("%d", &arr[i]);
    }

    int* start = arr;
    int* end = arr+K-1;
    int sum=0, result;
    
    for(int i=0; i<K; i++) {
        sum += arr[i];
    }
    result = sum;
   

    for(int i=0; i<N-K; i++) {
        sum -= *start;
        end++;
        sum += *end;
        start++;
        result = MAX(result, sum);
    }

    printf("%d\n", result);
    free(arr);
    //system("pause");

}