#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1);
typedef struct
{
    unsigned char op_code;
    int value_a;
    int value_b;
    unsigned char checksum;
    
} Packet;
#pragma pack(pop);

typedef int (*CalcFunc)(int, int);

int my_ntohl(int n) {
    return ((n & 0xFF000000) >> 24) |
           ((n & 0x00FF0000) >> 8)  |
           ((n & 0x0000FF00) << 8)  |
           ((n & 0x000000FF) << 24);
    
}

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int _div(int a, int b) { return b == 0 ? 0 : a / b; }

int main () {
    unsigned char raw_data[10] = { 
    0x02,                         // OpCode: SUB (뺄셈)
    0x00, 0x00, 0x03, 0xE8,       // Value A: 1000 (Big Endian)
    0x00, 0x00, 0x01, 0xF4,       // Value B: 500  (Big Endian)
    0xFF                          // Checksum (무시)
    };

    Packet *pkt = (Packet*)raw_data;


    // printf("%p\n",pkt); // pkt 포인터가 가리키는 주소 = raw_data의 주소
    // printf("%p\n", *pkt); // 이건 아예 쓰레기 값. *pkt 는 구조체 자체가 나오므로 출력 형태 오류.
    // printf("%p\n", &pkt); // pkt 포인터의 주소
    // printf("%p\n", raw_data); // raw_data 의 주소
    


    int real_a = my_ntohl(pkt->value_a);
    int real_b = my_ntohl(pkt->value_b);

    printf("[Packet Info]\n");
    printf("OpCode : %d\n", pkt->op_code);
    printf("Value A (Dec): %d\n", real_a);
    printf("Value B (Dec): %d\n", real_b);

    CalcFunc funclist[4] = {add, sub, mul, _div};

    printf("Result: %d\n", funclist[pkt->op_code](real_a,real_b));

    for(int i=0; i<4; i++) {
        printf("Result: %d\n", funclist[i](real_a,real_b));
    }

    return 0;
}