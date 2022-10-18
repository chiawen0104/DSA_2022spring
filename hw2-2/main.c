//
//  main.c
//  hw2-5
//
//  Created by 盧家雯 on 2022/4/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "price.h"
int A, Q, N;

typedef struct stock {
    int stock;
    int index;
    int day;
    unsigned long long price;
}Stock;

//delete root
void heapify_top_bottom(Stock *arr, int n, int i)
{
    int smallest = i;
    int leftChild = 2*i+1; // left child = 2*i + 1
    int rightChild = 2*i+2; // right child = 2*i + 2

    if (leftChild < n && arr[leftChild].price < arr[smallest].price){
        smallest = leftChild;
    }
        
    if (rightChild < n && arr[rightChild].price < arr[smallest].price){
        smallest = rightChild;
    }
        
    // If smallest is not the root
    if (smallest != i)
    {
        Stock tmp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = tmp;
        heapify_top_bottom(arr, n, smallest);
    }
}

//insert node
void heapify_bottom_top(Stock *arr, int n, int i)
{
    int parent = (i-1)/2;
 
    if (arr[i].price < arr[parent].price) {
        Stock tmp = arr[i];
        arr[i] = arr[parent];
        arr[parent] = tmp;
        heapify_bottom_top(arr, n, parent);
    }
}


void minHeap (Stock *arr, int size) {
    // Index of last non-leaf node
    int lastNLNode = (size/2)-1;
    
    for (int i=lastNLNode; i>=0; i--)
    {
        heapify_top_bottom(arr, size, i);
    }
}

int main() {
    
    scanf("%d%d%d", &A, &Q, &N);
    
    int tmp_stock[A];
    
    for (int i=0; i<A; i++) {
        int v;
        scanf("%d", &v);
        tmp_stock[i] = v;
    }
    
    unsigned long long Ktable[1000001];//record order of each k
    memset(Ktable, 0, sizeof(Ktable)); //initialize the empty stack
    int K[Q]; //record every k
    
    int maxk = -1;
    for (int i=0; i<Q; i++) {
        int s,k; //1 <= k <= 10^6
        scanf("%d%d", &s, &k);
        if (k > maxk)
            maxk = k;
        K[i] = k;
        Ktable[k] = 1;
    }
    
    if (N == 1) {
        Stock *arr;
        arr = (Stock*)malloc(sizeof(Stock)*A);
        for (int i=0; i<A; i++) { //day 1 of all stocks
            arr[i].stock = tmp_stock[i];
            arr[i].day = 1;
            arr[i].price = price(arr[i].stock, arr[i].day);
        }
            
        minHeap(arr, A);
        
        int k=1;
        for (k=1; k<=maxk; k++) {
            if (Ktable[k] != 0) {
                Ktable[k] = arr[0].price;
            }
            //pop minimum and remove last one
            Stock tmp = arr[0];
            arr[0] = arr[A-1];
            arr[A-1].stock = 0;
            arr[A-1].day = 0;
            arr[A-1].price = 0;
            heapify_top_bottom(arr, A-1, 0);
            
            //insert new node
            arr[A-1].stock = tmp.stock;
            arr[A-1].day = tmp.day+1;
            arr[A-1].price = price(arr[A-1].stock, arr[A-1].day);
            heapify_bottom_top(arr, A, A-1);
        }
    }
    else { // N > 1
        Stock *arr;
        arr = (Stock*)malloc(sizeof(Stock)*(A*(N+1)));
        int size = 0; //size of arr
        int stockk[A];
        
        for (int i=0; i<A; i++) {
            for (int j=1; j<=N+1; j++){ //day 1~1+N of all stocks
                arr[size].stock = tmp_stock[i];
                arr[size].day = j;
                arr[size].price = price(tmp_stock[i], j);
                arr[size].index = i;
                size++;
            }
            stockk[i] = 1;
        }
        
        /*
        printf("before heap:\n");
        for (int i=0; i<size; i++) {
            printf("%llu(%d,%d) ", arr[i].price, arr[i].stock,arr[i].day);
        }
         */
        minHeap(arr, size);
        
        for (int k=1; k<=maxk; k++) {
            if (Ktable[k] != 0) {
                Ktable[k] = arr[0].price;
            }
            
             //printf("k=%d: stock: %d, day: %d, price: %llu\n",k,arr[0].stock, arr[0].day, arr[0].price);
            
            //pop minimum
            Stock minstock = arr[0];
            //printf("size: %d\n",size);
            arr[0] = arr[size-1];
            arr[size-1].stock = 0;
            arr[size-1].index = -1;
            arr[size-1].day = 0;
            arr[size-1].price = 0;
            size--;
            heapify_top_bottom(arr, size, 0);
            
            /*
            printf("after pop:\n");
            for (int i=0; i<7; i++) {
                printf("%llu ", arr[i].price);
            }
            printf("\n");
             */
            
            //insert day k+N+1
            size++;
            arr[size-1].stock = minstock.stock;
            arr[size-1].day = stockk[minstock.index]+N+1;
            arr[size-1].index = minstock.index;
            arr[size-1].price = price(arr[size-1].stock, arr[size-1].day);
            stockk[minstock.index] += 1;
            heapify_bottom_top(arr, size, size-1);
            
        }
        free(arr);
    }
    //printf("-----------\n");
    for (int i=0; i<Q; i++) {
        int ki = K[i];
        printf("%llu\n",Ktable[ki]);
    }
    return 0;
}

