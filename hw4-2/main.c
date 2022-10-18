//
//  main.c
//  hw4-4
//
//  Created by 盧家雯 on 2022/6/8.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int N, Q;

void op5(int mach[], int l, int r, int k){
    for(int i=l; i<=r; i++){
        if (mach[i] > k) {
            mach[i] = k;
        }
    }
}

void op6(long long csum[], int l, int r){
    if (l == 0) {
        printf("%lld\n", csum[r]);
    }
    else{
        printf("%lld\n", csum[r]-csum[l-1]);
    }
    
}


int main() {
    scanf("%d%d", &N, &Q);
    
    int mach[N];
    for (int i=0; i<N; i++) {
        scanf("%d",&mach[i]);
    }
    
    int op[Q][5];
    for (int i=0; i<Q; i++) {
        scanf("%d",&op[i][0] );
        int opr = op[i][0] ;
        
        if (opr == 1) {
            scanf("%d",&op[i][1]);
            scanf("%d",&op[i][2]);
            return 0;
        }
        else if (opr == 2){
            scanf("%d",&op[i][1]);
            return 0;
        }
        else if (opr == 3){
            scanf("%d",&op[i][1]);
            scanf("%d",&op[i][2]);
            return 0;
        }
        else if (opr == 4){
            scanf("%d",&op[i][1]);
            scanf("%d",&op[i][2]);
            scanf("%d",&op[i][3]);
            scanf("%d",&op[i][4]);
            return 0;
        }
        else if (opr == 5){
            scanf("%d",&op[i][1]);
            scanf("%d",&op[i][2]);
            scanf("%d",&op[i][3]);
            return 0;
        }
        else if (opr == 6){
            scanf("%d",&op[i][1]);
            scanf("%d",&op[i][2]);
        }
    }
    
    long long csum[N];
    long long sum = 0;
    for (int i=0; i<N; i++) {
        sum += mach[i];
        csum[i] = sum;
    }
    
    for (int i=0; i<Q; i++) {
        int opr = op[i][0];
        
        if (opr == 6) {
            op6(csum, op[i][1]-1, op[i][2]-1);
        }
        else if (opr == 5){
            op5(mach, op[i][1]-1, op[i][2]-1, op[i][3]);
        }
        else if (opr == 1){
            continue;
        }
        else if (opr == 2){
            continue;
        }
        else if (opr == 3){
            continue;
        }
        else if (opr == 4){
            continue;
        }
    }
    return 0;
}

