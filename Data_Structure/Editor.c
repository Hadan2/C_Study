#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char left_stack[600005];
char right_stack[600005];
int l_top=0;
int r_top=0;


int main () {
    char str[1000001];
    scanf("%s", str);
    int len= strlen(str);
    for(int i=0; i<len; i++) {
        left_stack[l_top++] = str[i];
    }

    int M;
    scanf("%d", &M);
    
    char cmd;
    char add_char;
    

    for(int i=0; i<M; i++) {
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'L':
            if(l_top>0) {
                right_stack[r_top++] = left_stack[--l_top];
            }
            break;
        case 'D':
            if(r_top>0) {
                left_stack[l_top++] = right_stack[--r_top];
            }
            break;
        
        case 'B':
            if(l_top>0) {
                l_top--;
            }
            
            break;
        case 'P':
            scanf(" %c", &add_char);
            left_stack[l_top] = add_char;
            l_top++;
            break;
        }
    }

    for(int i=0; i<l_top; i++) {
        printf("%c", left_stack[i]);
    }
    for(int i=r_top-1; i>=0; i--) {
        printf("%c", right_stack[i]);
    }

}