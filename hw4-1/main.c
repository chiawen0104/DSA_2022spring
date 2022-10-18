#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int N, M;

typedef struct disjointSet{
    int *rank;
    int *parent;
} DisjointSet;

typedef struct node {
    int day;
    struct node* next;
}Node;

typedef struct event {
    int shop;
    int type;
    int day;
    int a;
    int b;
}Event;

DisjointSet ds[1000001];
int set[1000001] = {};

Node* newNode(int d)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->day = d;
    node->next = NULL;
    return node;
}

void createAdjlist (Node *head[], Node *curr[], Event *dayptr[], Event event[])
{
    
    for (int i=0; i<=M; i++) { //set head
        head[i] = newNode(i);
        head[i]->next = NULL;
        curr[i] = head[i];
    }
    
    for (int i=1; i<=M; i++){ //set each node
        if (event[i].type == 1) { //only merge type
            int from = dayptr[i-1]->day;//from yesterday
            Node *node = newNode(i);
            curr[from]->next = node;
            node->next = NULL;
            curr[from] = node;
        }
    }
}

void init(int i) {
    if (set[i] == 0) {
        ds->parent[i] = i; //makeset of itself
        set[i] = 1;
    }
}

int find_set(int i) {
   
    init(i);//initialization check
    int par = ds->parent[i];
    
    while (par != i) {
        par = ds->parent[par];
        i = ds->parent[i];
    }
     
    
    //No path compression
    /*
    if (ds->parent[i] != i) {
        return find_set(ds->parent[i]);
        //ds->parent[i] = find_set(ds->parent[i]);
    }
     */
     
    return par;
}

void merge(int x, int y) { //union
    int a = find_set(x);
    int b = find_set(y);
    
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

bool same_set(int x, int y) {
    if (find_set(x) == find_set(y)) {
        return true;
    }
    return false;
}

/*
void printPar (int d) {
    printf("d%d: ", d);
    for (int i=1; i<=N; i++) {
        printf("%d ", ds->parent[i]);
    }
    printf("\n\n");
}
 */

void DFS (Node *head[], bool *visited, Event event[], int d) {
    
    if (visited[d] == true) {
        return;
    }
    
    static int shop = 0;//record times of merge success and let N-shop equal to number of sets
    
    visited[d] = true; //mark node of day i is visited
    bool flag = false; //merge success is true or false otherwise
    
    int a = event[d].a;
    int b = event[d].b;
    int as = find_set(a);
    int bs = find_set(b);
    
    //copy number before merge
    int apar = ds->parent[as];
    int bpar = ds->parent[bs];
    int arank = ds->rank[as];
    int brank = ds->rank[bs];
    int aset = set[a];
    int bset = set[b];
     
    //printf("Before day%d, (a)%d par= %d, rank= %d, set= %d, fst=%d\n", d, a,apar, arank, aset, find_set(a));
    //printf("Before day%d, (b)%d par= %d, rank= %d, set= %d, fst=%d\n", d, b,bpar, brank, bset, find_set(b));
    
    if (d != 0) {
        if (!same_set(a, b)) {
            merge(a, b);
            shop++;
            flag = true;
        }
    }
    
    event[d].shop = N-shop;
    
    
    //printf("After day%d, (a)%d par= %d, rank= %d, set= %d, fst=%d\n", d, a, ds->parent[a], ds->rank[a], set[a], find_set(a));
    //printf("After day%d, (b)%d par= %d, rank= %d, set= %d, fst=%d\n", d, b, ds->parent[b], ds->rank[b], set[b], find_set(b));
    
    //DFS recursion
    Node *ptr = head[d]->next;
    while (ptr != NULL) {
        int x = ptr->day;
        if (visited[x] == false) {
            DFS(head, visited, event, x);
        }
        ptr = ptr->next;
    }
    

    //printf("day%d: shop=%d\n",d, event[d].shop);
    if (d != 0 && flag == true) {
        shop--;
    }
    ds->parent[as] = apar;
    ds->rank[as] = arank;
    ds->parent[bs] = bpar;
    ds->rank[bs] = brank;
    set[a] = aset;
    set[b] = bset;
    
    //printf("Revise day%d, (a)%d par= %d, rank= %d, set= %d, fst=%d\n", d, a, ds->parent[a], ds->rank[a], set[a], find_set(a));
    //printf("Revise day%d, (b)%d par= %d, rank= %d, set= %d, fst=%d\n", d, b, ds->parent[b], ds->rank[b], set[b], find_set(b));
    //return;
}

int main() {
    int Q = 0;//query count
    scanf("%d%d",&N,&M);
    
    ds->parent = (int*)calloc(1000001,sizeof(int));
    ds->rank = (int*)calloc(1000001,sizeof(int));
    
    //input record
    Event event[M+1];//event[0] is day 0 (intial state)
    event[0].type = 1;
    event[0].day = 0;
    event[0].shop = N;
    event[0].a = 0;
    event[0].b = 0;
    bool bm = false;
    
    for (int i=1; i<=M; i++) { //input of commands
        char op[6];
        scanf("%s", op);
        
        if (op[0] == 'm') { //merge = type 1
            int x,y;
            scanf("%d%d", &x,&y);
            event[i].type = 1;
            event[i].day = i;
            event[i].a = x;
            event[i].b = y;
        }
        else if (op[0] == 'b'){ //boom = type 2
            int k;
            scanf("%d", &k);
            bm = true;
            event[i].type = 2;
            event[i].day = i;
            event[i].a = k;
            event[i].b = 0;
        }
        else { //query = type 3
            event[i].type = 3;
            event[i].day = i;
            event[i].a = 0;
            event[i].b = 0;
            Q++; //query count
        }
    }
    
    int *query = (int*)calloc(Q,sizeof(int));//record day of each query
    int qid=0; //index of query

    Event *dayptr[M+1];
    
    for (int i=0; i<=M; i++) {
        if (event[i].type == 1){
            dayptr[i] = &event[i];
        }
        else if (event[i].type == 2){
            dayptr[i] = dayptr[event[i].a];
        }
        else {
            dayptr[i] = dayptr[i-1];
            query[qid] = i;
            qid++;
        }
    }
    
    Node *head[M+1];
    Node *curr[M+1];
    createAdjlist(head, curr, dayptr, event);
    
    //check adj list
    /*
    printf("\n");
    Node *tmp = head[0];
    printf("%d: ", tmp->day);
    while (tmp->next != NULL) {
        printf("%d ", tmp->next->day);
        tmp = tmp->next;
    }
    printf("\n");
    
    for (int i=1; i<=M; i++) {
        tmp = head[i];
        printf("%d: ", tmp->day);
        while (tmp->next != NULL) {
            printf("%d ", tmp->next->day);
            tmp = tmp->next;
        }
        printf("\n");
    }
     */
    
    //visited array of dfs
    bool *visited = (bool*)calloc(M+1,sizeof(bool));
    
    for (int i=0; i<=M; i++) {
        if (event[i].type != 1) {
            visited[i] = true; //do not visit non merge day
        }
        else{
            visited[i] = false;//visit merge day
        }
    }
    
    //start from day 0 (initial status)
    DFS(head, visited, event, 0);
    
    
    /*
    for (int i=0; i<=M; i++) {
        printf("day %d: %d\n", i, dayptr[i]->shop);
    }
     */
     
    //print answer
    for (int j=0; j<Q; j++) {
        int d = query[j];
        printf("%d\n", dayptr[d]->shop);
    }
     
    free(ds->parent);
    free(ds->rank);
    free(query);
    free(visited);
    
    return 0;
}




