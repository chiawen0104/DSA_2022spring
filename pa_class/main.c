//
//  main.c
//  in class
//
//  Created by 盧家雯 on 2022/5/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    // TODO: Determine fields to use by your method
    int *rank;
    int *parent;
} DisjointSet;


DisjointSet ds[1 << 24];
bool set[1 << 24] = {};
//char *name[1 << 24];

int c2i(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}

int hash(const char* s) {
    int ret = 0;
    int mask = (1<<24)-1;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        ret = mask & (ret << 4) | c2i(s[i]);
    return ret;
}

void makeset(const char* s){
    // TODO: Initialize a set with hash value
    int i = hash(s);
    ds->parent[i] = i;
}

inline void static init(const char* s) {
    int i = hash(s);
    if (!set[i]) {
        makeset(s);
        set[i] = 1;
    }
}

int find_set(const char *s) {
    init(s);
    int i = hash(s);
    // TODO: Implement your find algorithm here
    
    while (ds->parent[i] != i) {
        ds->parent[i] = ds->parent[ds->parent[i]];
        i = ds->parent[i];
    }
     
    return ds->parent[i];
}

void group(const char *ra, const char *rb) { //union
    int a = find_set(ra), b = find_set(rb);
    // TODO: Implement your union algorithm here
    if (a == b)
        return;

    
    if (ds->rank[a] < ds->rank[b]) {
        ds->parent[a] = b;
    }
    else if (ds->rank[a] > ds->rank[b]) {
        ds->parent[b] = a;
    }
    else {
        ds->parent[b] = a;
        ds->rank[a] = ds->rank[a] + 1;
    }
}

bool same_set(const char*a, const char* b) {
    // TODO: Implement your algorithm here
    if (find_set(a) == find_set(b)) {
        return true;
    }
    return false;
}
 
int main() {
    // TODO: Implement your algorithm here
    int N;
    scanf("%d",&N);
    
    ds->parent = (int*)calloc((1<<24),sizeof(int));
    ds->rank = (int*)calloc((1<<24),sizeof(int));
    
    ///*
    for (int i=0; i<N; i++) {
        char op[6];
        char a[13];
        char b[13];
        
        scanf("%s%s%s", op, a, b);
        //name[hash(a)] = a;
        //name[hash(b)] = b;
        //printf("%c %s %s\n", op[0], a, b);
        //printf("hash: %d %d\n", hash(a), hash(b));
        //printf("%d\n", hash(b));
        
        if (op[0] == 't') { // test query
            //printf("%d & %d\n", find_set(a), find_set(b));
            if (same_set(a, b) == true) {
                printf("Positive\n");
            }
            else{
                printf("Negative\n");
            }
        }
        else { //group opearation
            group(a, b);
        }
        
    }
     //*/
    free(ds->parent);
    free(ds->rank);
    return 0;
}

