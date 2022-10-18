//
//  main.c
//  hw3-5
//
//  Created by 盧家雯 on 2022/5/7.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int k, l, flag;

typedef struct rbk{
    long long value; //right-left
    long long left;
    long long right;
    long long value2;
    int strid;
}Rbk;

int compareV(const void *a, const void *b)
{
    Rbk c = *(Rbk*)a;
    Rbk d = *(Rbk*)b;
    
    if(c.left < d.left) return -1;
    else if(c.left > d.left) return 1;
      
    if(c.right < d.right) return -1;
    else if(c.right > d.right) return 1;
    else return 0;
}

int compareV2(const void *a, const void *b)
{
    Rbk c = *(Rbk*)a;
    Rbk d = *(Rbk*)b;
    if(c.value2 < d.value2) {return -1;}     //-1: a < b
    else if (c.value2 == d.value2) {return 0;} //0: a = b
    else return 1;               //1: a>b        //1: a>b
}


int binary_search0(Rbk *arr, int sid) { //id1 is index of sorted array
    int left = 0;
    int right = k - 1;
    int leftbound = -1; //smallest index of same left rbk
    
    while (left <= right) {
        int mid = (right+left) / 2;
        if (arr[mid].left > arr[sid].left) {
            right = mid - 1;
        }
        else if (arr[mid].left < arr[sid].left) {
            left = mid + 1;
        }
        else {
            leftbound = mid;
            right = mid - 1;
        }
    }
    
    int rightbound = -1;
    left = 0;
    right = k - 1;
    while (left <= right) {
        int mid = (right+left) / 2;
        if (arr[mid].left > arr[sid].left) {
            right = mid - 1;
        }
        else if (arr[mid].left < arr[sid].left) {
            left = mid + 1;
        }
        else {
            rightbound = mid;
            left = mid+1;
        }
    }
    
    //right rbk value
    left = leftbound;
    right = rightbound;
    int leftbound2 = -1; //smallest index of same left rbk
    
    while (left <= right) {
        int mid = (right+left) / 2;
        if (arr[mid].right > arr[sid].right) {
            right = mid - 1;
        }
        else if (arr[mid].right < arr[sid].right) {
            left = mid + 1;
        }
        else {
            leftbound2 = mid;
            right = mid - 1;
        }
    }
    
    int rightbound2 = -1;
    left = leftbound;
    right = rightbound;
    while (left <= right) {
        int mid = (right+left) / 2;
        if (arr[mid].right > arr[sid].right) {
            right = mid - 1;
        }
        else if (arr[mid].right < arr[sid].right) {
            left = mid + 1;
        }
        else {
            rightbound2 = mid;
            left = mid+1;
        }
    }
    
    if (leftbound2 != -1 && rightbound2 != -1) {
        for (int i=leftbound2; i<=rightbound2; i++) {
            if (i != sid) {
                if (arr[i].left == arr[sid].left && arr[i].right == arr[sid].right) {
                    return i;
                }
            }
        }
    }
    
    return -1;
}

long long binary_search_11(Rbk *arr, int sid) { //id1 is index of sorted array
    /*
    for (int j = 0; j < k; j++){
        printf("left=%lld right=%lld v1=%lld\n", arr[j].left, arr[j].right, arr[j].value);
    }
    printf("----------\n");
     */
    
    //left rbk value
    int left = 0;
    int right = k - 1;
    int leftbound = -1; //smallest index of same left rbk
    
    while (left <= right) {
        int mid = (right+left) / 2;
        if (arr[mid].left > arr[sid].left) {
            right = mid - 1;
        }
        else if (arr[mid].left < arr[sid].left) {
            left = mid + 1;
        }
        else {
            leftbound = mid;
            right = mid - 1;
        }
    }
    
    int rightbound = -1;
    left = 0;
    right = k - 1;
    while (left <= right) {
        int mid = (right+left) / 2;
        if (arr[mid].left > arr[sid].left) {
            right = mid - 1;
        }
        else if (arr[mid].left < arr[sid].left) {
            left = mid + 1;
        }
        else {
            rightbound = mid;
            left = mid+1;
        }
    }
    
    //right rbk value
    left = leftbound;
    right = rightbound;
    int leftbound2 = -1; //smallest index of same left rbk
    
    while (left <= right) {
        int mid = (right+left) / 2;
        if (arr[mid].right > arr[sid].right) {
            right = mid - 1;
        }
        else if (arr[mid].right < arr[sid].right) {
            left = mid + 1;
        }
        else {
            leftbound2 = mid;
            right = mid - 1;
        }
    }
    
    int rightbound2 = -1;
    left = leftbound;
    right = rightbound;
    while (left <= right) {
        int mid = (right+left) / 2;
        if (arr[mid].right > arr[sid].right) {
            right = mid - 1;
        }
        else if (arr[mid].right < arr[sid].right) {
            left = mid + 1;
        }
        else {
            rightbound2 = mid;
            left = mid+1;
        }
    }
    
    //number of similar pair(1 different char)
    if (rightbound2-leftbound2 > 0) {
        return rightbound2-leftbound2;
    }
    else{
        return 0;
    }
}

long long binary_search_10(Rbk *arr, int sid) { //id1 is index of sorted array
    int left = 0;
    int right = k - 1;
    int leftbound = -1; //smallest index of same left rbk
    
    while (left <= right) {
        int mid = (right+left) / 2;
        if (arr[mid].value2 > arr[sid].value2) {
            right = mid - 1;
        }
        else if (arr[mid].value2 < arr[sid].value2) {
            left = mid + 1;
        }
        else {
            leftbound = mid;
            right = mid - 1;
        }
    }
    
    int rightbound = -1;
    left = 0;
    right = k - 1;
    while (left <= right) {
        int mid = (right+left) / 2;
        if (arr[mid].value2 > arr[sid].value2) {
            right = mid - 1;
        }
        else if (arr[mid].value2 < arr[sid].value2) {
            left = mid + 1;
        }
        else {
            rightbound = mid;
            left = mid+1;
        }
    }
    
    return rightbound-leftbound;//number of same pair
}

int main() {
    
    scanf("%d%d%d", &k, &l, &flag);
    
    // string input
    char **arr = (char**)malloc(k * sizeof(char*));
    for (int i = 0; i < k; i++)
        arr[i] = (char*)malloc((l+1) * sizeof(char));
    
    for (int i=0; i<k; i++) {
        scanf("%s", arr[i]);
    }
    
    if (l == 1 && k > 1 && flag==0) {
        printf("Yes\n");
        printf("%d %d\n", 0, 1);
        return 0;
    }
    
    long long q = (LLONG_MAX/94)+1; // d=126-33+1=94
    //printf("%lld\n",q);
    
    // table of RBK value
    Rbk **table = (Rbk**)malloc(l * sizeof(Rbk*));
    for (int i = 0; i < l; i++)
            table[i] = (Rbk*)malloc(k * sizeof(Rbk));
    
    for (int j=0; j<k; j++){
        long long lhash = 0;
        for (int i = 0; i < l; i++){
            table[i][j].strid = j;
            table[i][j].left = lhash;
            lhash = ((94*lhash)+(long long)arr[j][i]-33)%q;
        }
        long long ll = lhash;
        
        long long rhash = 0;
        for (int i=l-1; i>=0; i--) {
            table[i][j].right = rhash;
            rhash = ((94*rhash)+(long long)arr[j][i]-33)%q;
        }
        
        long long d = 1;
        for (int i = l-1; i >= 0; i--){
            table[i][j].value2 = ll;
            table[i][j].value = (table[i][j].left%(2147483647)*d)+table[i][j].right;
            d = (94*d)%(2124638078);
        }
    }
    
    /*
    for (int j = 0; j < k; j++){
        for (int i = 0; i < l; i++){
            printf("left=%lld right=%lld v1=%lld\n", table[i][j].left, table[i][j].right, table[i][j].value);
        }
        printf("v2=%lld\n\n", table[0][j].value2);
    }
     */
    
    
    if (flag == 0) {
        for (int i = 0; i < l; i++){
            Rbk *sortl = table[i];
            qsort((void *)sortl, k, sizeof(sortl[0]), compareV);
            
            for (int j = 0; j < k; j++){
                int target = binary_search0(sortl, j);
                //printf("%d & %d\n", j, target);
                
                if (target != -1) {
                    int id1 = sortl[j].strid; //convert to original index
                    int id2 = sortl[target].strid;
                    printf("Yes\n");
                    printf("%d %d\n", id1, id2);
                    free(sortl);
                    return 0;
                }
            }
            free(sortl);
        }
        printf("No\n");
    }
    else { // flag=1
        Rbk *sort1 = table[0];
        qsort((void *)sort1, k, sizeof(sort1[0]), compareV2);
        long long same_total = 0;
        
        for (int j = 0; j < k; j++){
            long long same_c = binary_search_10(sort1, j);
            same_total += same_c;
        }
        
        
        long long similar_total=0;
        
        for (int i = 0; i < l; i++){ //for l=0,1,....
            Rbk *sort2 = table[i];
            qsort((void *)sort2, k, sizeof(sort2[0]), compareV);
            
            for (int j = 0; j < k; j++){ //for each string
                long long similar_c = binary_search_11(sort2, j);
                similar_total += similar_c;
                //printf("%d\n",similar_c);
            }
        }
        //printf("same: %lld\n",same_total);
        //printf("similar: %lld\n",similar_total);
        long long ans = (same_total/2) + (similar_total-l*same_total)/2;
        if (ans <= 0) {
            printf("No\n");
        }
        else {
            printf("Yes\n");
            printf("%lld\n", ans);
        }
    }
    return 0;
}



