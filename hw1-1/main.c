//
//  main.c
//  hw1-4
//
//  Created by 盧家雯 on 2022/3/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DATA {
    long long int value; //for operand
    int type; //1: operand, 0: operator
    char op; //for operator
};

int prior(char op) {
    int p;

    switch(op) {
       case '+': case '-':
            p = 1;
            break;
        case '*': case '/': case '%':
            p = 2;
            break;
        default:
            p = 0;
            break;
    }

    return p;
}

int toPostfix(struct DATA *infix, struct DATA *postfix, int len) {
    struct DATA *stack = NULL;
    stack = (struct DATA*)malloc(sizeof(struct DATA)*len);
    
    int i, j, top;
    
    for(i = 0, j = 0, top = 0; i<len; i++) {
        switch(infix[i].op) {
            case '(':
                stack[++top] = infix[i];
                break;
                
            case '+': case '-': case '*': case '/': case '%':
                while(prior(stack[top].op) >= prior(infix[i].op)) {
                    postfix[j++] = stack[top--];
                }
                stack[++top] = infix[i];
                break;
                
            case ')':
                while(stack[top].op != '(') {
                    postfix[j++] = stack[top--];
                }
                top--;
                break;
                
            default:
                postfix[j++] = infix[i];
        }
    }
    while(top > 0) {
        postfix[j++] = stack[top--];
    }
    free(stack);
    return 0;
}
 

long long int operation (long long int a, long long int b, char op){ // top-1:a, top:b
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (a<0 && b>0 && a%b != 0)
                return a/b-1;
            else if (a>0 && b<0 && a%b != 0)
                return a/b-1;
            else
                return a / b;
        case '%': return a % b;
    }
    return 0;
}

long long int caculate(struct DATA *postfix, int len, long long int ans, int first){
    long long int *stack;
    stack = (long long int*)calloc(len,sizeof(long long int));
    
    int top = 0;
    
    if (first != 1) {
        stack[++top] = ans;
    }
    
    for (int i=0; i<len; i++) {
        if (postfix[i].op == '\0') {
            break;
        }
        char op = postfix[i].op;
        
        switch(op) {
            case '+': case '-': case '*': case '/': case '%':
                stack[top-1] = operation(stack[top-1], stack[top], op);
                top--;
                break;
                
            default:
                stack[++top] = postfix[i].value;
                break;
        }
        //printf("\n%lld", stack[top]);
    }
    long long int s_top = stack[top];
    free(stack);
    return s_top;
}


int main(int argc, const char * argv[]) {
    
    char str[1000001] = {'\0'};
    
    scanf("%s",str);
    //int inlen = strlen(str); // get length of input line
    
    const char s[2] = "=";
    char *substr;
    substr = strtok(str, s);
    
    long long int ans = 0;
    int first = 1;
    
    while( substr != NULL ){
        //printf("\n%s, ", substr);
        
        struct DATA *infix=NULL;
        infix = (struct DATA*)malloc(sizeof(struct DATA)*strlen(substr));
        for (int j=0; j<strlen(substr); j++) { //initialization
            infix[j].type = -1;
            infix[j].value = 0;
            infix[j].op = '\0';
        }
         
        
        
        int N = 0; //index of infix(array);
        long long int tmp = 0;
        
        for (int i=0; i<strlen(substr); i++) {
            if (substr[i] < 48) {
                infix[N].type = 0;
                infix[N].value = 0;
                infix[N].op = substr[i];
                N++;
            }
            else {
                tmp += substr[i]-48;
                if (substr[i+1] >= 48 && i+1 < strlen(substr)) {
                    tmp *= 10;
                }
                if (substr[i+1] < 48 && i+1 < strlen(substr) && tmp != 0) {
                    infix[N].type = 1;
                    infix[N].value = tmp;
                    infix[N].op = 'n';
                    N++;
                    tmp = 0;
                }
                if (i == strlen(substr)-1 && tmp != 0) {
                    infix[N].type = 1;
                    infix[N].value = tmp;
                    infix[N].op = 'n';
                    N++;
                }
            }
        }
         //check infix
        /*
        for (int k = 0; k<N; k++) {
            if (infix[k].type == 1) {
                printf("%lld ", infix[k].value);
            }
            else{
                printf("%c ", infix[k].op);
            }
        }
         */
         
        struct DATA *postfix= NULL; // store the postfix notation
        postfix = (struct DATA*)malloc(sizeof(struct DATA)*N);
        for (int j=0; j<N; j++) { //initialization
            postfix[j].type = -1;
            postfix[j].value = 0;
            postfix[j].op = '\0';
        }
        
        toPostfix(infix, postfix, N);
        
        //check postfix
        /*
        for (int i=0; i<N; i++) {
            if (postfix[i].type == 1) {
                printf("%lld ", postfix[i].value);
            }
            else{
                printf("%c ", postfix[i].op);
            }
        }
         */
         
         
        
        //printf("\nLen: %d\n", N);
        
        ans = caculate(postfix, N, ans, first);
        printf("Print: %lld\n", ans);
        first = 0;
        
        substr = strtok(NULL, s);
        free(infix);
        free(postfix);
    }
    
    return 0;
}
