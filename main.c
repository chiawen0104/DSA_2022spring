//
//  main.c
//  hw0
//
//  Created by 盧家雯 on 2022/3/2.
//

#include <stdio.h>
#include <stdlib.h>

int comparator(short *a, short *b, int lena, int lenb){
    //if a>b return 1, a<b return -1, a=b will return 0
    
    if(lena > lenb)
        return 1;
    else if (lena == lenb) {
        for (int j=lena-1; j>=0; j--) {
            if (a[j] > b[j])
                return 1;
            else if (a[j] < b[j])
                return -1;
        }
        return 0;
    }
    
    return -1;
}

void two_multip(short *a){
    
    for (int i=0; i<256; i++) {
        a[i] = 2*a[i];
        if (a[i-1] >= 10 && i-1 >= 0) {
            a[i] ++;
            a[i-1] -= 10;
        }
    }
}

void printans(short *ans){
    int i=255;
    while (ans[i] == 0) {
        i--;
    }
    for (int j=i; j>=0; j--) {
        printf("%d",ans[j]);
    }
}

int equalzero(short *a){ // equal 0 return 1, else return 0
    for (int i = 255; i>=0; i--) {
        if (a[i] != 0) {
            return 0;
        }
    }
    if (a[0] == 0) {
        return 1;
    }
    return 0;
}

void two_division(short a[]){
    
    short tmp[256] = {0};
    
    for (int i=255; i>=0; i--) {
        tmp[i] = a[i];
    }
    
    int d = 0;
    for (int i=255; i>=0; i--) {
        if (i == 255) {
            a[i] = tmp[i]/2;
        }
        else if (i+1 >= 0 && i+1 < 256) {
            d = 10*(tmp[i+1]%2)+tmp[i];
            a[i] = d/2;
        }
    }
}
 

void subtraction(short *a, short *b){
    
    for (int i=0; i<256; i++) {
        a[i] = a[i] - b[i];
        if (a[i] < 0 && i+1 < 256) {
            a[i] += 10;
            a[i+1] --;
        }
    }
    
}
 

int main() {
    char stra[257] = {'\0'};
    char strb[257] = {'\0'};
    int lena = 0;
    int lenb = 0;
    
    scanf("%s%s",stra,strb);
    
    //caculate length of string a and string b
    int i = 0;
    while (stra[i] != '\0'){
        lena++;
        i++;
    }
    
    i=0;
    while (strb[i] != '\0'){
        lenb++;
        i++;
    }
    
    //store Bigint in array
    short arra[256] = {0};
    short arrb[256] = {0};
    short ans[256] = {0};
    ans[0] = 1;
    
    for (int j=0; j<lena; j++){
        arra[j] = stra[lena-1-j]-48;
    }
    for (int j=0; j<lenb; j++){
        arrb[j] = strb[lenb-1-j]-48;
    }
    
    //point to array
    short *a = arra;
    short *b = arrb;
    
    // if a<b, swap(a,b)
    if (comparator(a, b, lena, lenb) == -1) {
        short *tmp = a;
        a = b;
        b = tmp;
    }
    

    //check multip
    //two_multip(a);
    
    
    //check subtraction
    //subtraction(a, b);
    
    //check division
    //two_division(a);
    
    int k=0; //2^k
    
    while (equalzero(a) != 1 && equalzero(b) != 1) {
        if (a[0] % 2 == 0 && b[0] % 2 == 0){
            //two_multip(ans);
            k++;
            two_division(a);
            two_division(b);
        }
        else if(b[0] % 2 == 0){
            two_division(b);
        }
        else if(a[0] % 2 == 0){
            two_division(a);
        }
        
        if(comparator(a, b, 256, 256) == -1){ //swap
            short *tmp2 = a;
            a = b;
            b = tmp2;
        }
        subtraction(a, b);
    }
    
    //printans(b);
    //printf("*");
    //printans(ans); //ans = 2^k
    //printf("\n%d",k);
    
    for (int i=0; i<k; i++) {
        two_multip(b);
    }
    printans(b);
    return 0;
}
