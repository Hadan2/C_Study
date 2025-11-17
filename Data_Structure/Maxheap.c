#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
} MaxHeap;

void initHeap(MaxHeap *h, int capacity) {
    h->capacity = capacity;
    // (*h).capacity 는 h->capacity 와 동일하다.
    h->size = 0;
    h->arr = (int *)malloc(sizeof(int) * capacity);
}

void freeHeap(MaxHeap *h) {
    free(h->arr);
    h->arr = NULL;
    h->size = 0;
    h->capacity = 0;
}

int pop(MaxHeap *h) {
    if(h->size==0) {
        return 0;
    }
    else {
        int result;
        result = h->arr[0];
        h->arr[0] = h->arr[h->size-1];
        h->size--;
        int current = 0;

        while(current*2+1 < h->size) {
            int child;
            if(current*2+2 < h->size) {
                child = h->arr[current*2+1] > h->arr[current*2+2] 
                ? current*2+1 :current*2+2;    
            }
            else {child = current*2+1;}

            if(h->arr[child] > h->arr[current]) {
                int temp;
                temp = h->arr[child];
                h->arr[child] = h->arr[current];
                h->arr[current] = temp;
                current = child;
            }
            else { break; }

        }
        return result;
    }
}

void push(MaxHeap *h, int value) {
    h->arr[h->size] = value;
    int current = h->size;
    h->size++;
    while(current!=0 && h->arr[current] > h->arr[(current-1)/2]) {
        h->arr[current] = h->arr[(current-1)/2];
        h->arr[(current-1)/2] = value;
        current = (current-1)/2;
    }

}

// 재귀적으로 트리를 출력하는 내부 함수 (Right -> Root -> Left 순서)
void printHeapHelper(MaxHeap *h, int index, int space) {
    // 기저 조건: 인덱스가 범위를 벗어나면 종료
    if (index >= h->size)
        return;

    // 1. 오른쪽 자식부터 먼저 들어감 (화면상 위쪽)
    // space는 들여쓰기 깊이 (10칸씩 띄움)
    printHeapHelper(h, index * 2 + 2, space + 10);

    // 2. 현재 노드 출력
    printf("\n");
    for (int i = 10; i < space + 10; i++)
        printf(" "); // 공백 찍기
    
    printf("%d\n", h->arr[index]); // 값 출력

    // 3. 왼쪽 자식으로 들어감 (화면상 아래쪽)
    printHeapHelper(h, index * 2 + 1, space + 10);
}

// 사용자가 호출할 함수 wrapper
void printHeap(MaxHeap *h) {
    printf("=== Heap Tree Structure (Turn your head left!) ===\n");
    if (h->size == 0) {
        printf("(Empty Heap)\n");
    } else {
        printHeapHelper(h, 0, 0);
    }
    printf("==================================================\n");
}

int main(void) {
	int N;
    scanf("%d", &N);
    MaxHeap myHeap;
    initHeap(&myHeap, N+2);

    int input;
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &input);
        if(input == 0 ) {
            if(myHeap.size==0) {
                printf("%d\n", 0);
            }
            else {
                int node = pop(&myHeap);
                printf("%d\n", node);
            }
            
        }
        else {
            push(&myHeap, input);
        }
    }

   

	return 0;
}