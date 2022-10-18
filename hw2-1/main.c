//
//  main.c
//  hw2-4
//
//  Created by 盧家雯 on 2022/4/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int N, Q, S, R;//cities, quries, capital, resort
int top = -1;

typedef struct node {
    int city;
    struct node *next; //pointer to node
}Node;

void DFS(Node* head[N+1], int visited[N+1], int x, int dfs[N], int inSR[N+1], int ans[N+1])
{
    static int i=0; //index of dfs[]
    visited[x] = 1;
    dfs[i] = x;
    i++;
    
    Node* ptr = head[x]->next;
    while (ptr != NULL) {
        int y = ptr->city;
        if(visited[y] == 0) {// to city y
            if (inSR[y] == 0)
                ans[y] = ans[x];
            DFS(head, visited, y, dfs, inSR, ans);
        }
        ptr = ptr->next;
    }
    free(ptr);
}

void printPath(int stack[], int inSR[N+1]){

    for (int i = 0; i <= top; i++) {
        //printf("%d->", stack[i]);
        inSR[stack[i]] = 1;
    }
    //printf("\n");
}

// from x to y
void SR_DFS(Node* head[N+1], int vis[N+1], int stack[N], int x, int y, int inSR[N+1])
{
    stack[++top] = x;// stack push
    
    if (x == y) {
        printPath(stack, inSR);
        return;
    }
    vis[x] = 1;
 
    Node* ptr = head[x]->next;
    while (ptr != NULL) {
        int j = ptr->city;
        if (vis[j] == 0)
            SR_DFS(head, vis, stack, j, y, inSR);
        ptr = ptr->next;
    }

    stack[top] = 0; //stack pop
    top--;
    free(ptr);
}

void CreateAdjList (Node* head[N+1], Node* curr[N+1], int a, int b) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (head[a]->next == NULL)
        head[a]->next = newNode;
    else
        curr[a]->next = newNode;
    
    newNode->city = b;
    newNode->next = NULL;
    curr[a] = newNode;
    
    
    Node* newNode2 = (Node*)malloc(sizeof(Node));
    if (head[b]->next == NULL)
        head[b]->next = newNode2;
    else
        curr[b]->next = newNode2;
    
    newNode2->city = a;
    newNode2->next = NULL;
    curr[b] = newNode2;
     
}

int main() {
    scanf("%d%d%d%d", &N, &Q, &S, &R);
    
    // adjacency linked list
    Node* head[N+1];
    Node* curr[N+1];
    
    for (int k=1; k<N+1; k++) { //initialize head
        head[k] = (Node*)malloc(sizeof(Node));
        head[k]->city = k;
        head[k]->next = NULL;
        curr[k] = head[k];
    }
    
    int visted[N+1]; // for DFS
    int dfs[N]; // store dfs path
    int inSR[N+1]; // 1(if in SR path), 0(not in SR path)
    int vis[N+1]; // for SR_DFS
    int stack[N]; // for SR_DFS

    memset(vis, 0, sizeof vis); //initialize the vis array
    memset(visted, 0, sizeof visted); //initialize the vistied array
    memset(stack, 0, sizeof stack); //initialize the empty stack
    memset(inSR, 0, sizeof inSR);
    
    for (int i=0; i<N-1; i++) {
        int a,b;
        scanf("%d%d", &a, &b);
        CreateAdjList(head, curr, a, b);
    }
    
    int ans[N+1]; // answer of each city(index)
    int query[Q];
    memset(ans, 0, sizeof ans);
    
    for (int i=0; i<Q; i++) { //query input
        int c;
        scanf("%d", &c);
        query[i] = c;
    }
    
    SR_DFS(head, vis, stack, S, R, inSR); //find the path from S to R
    
    for (int i=1; i<N+1; i++) { //answer set
        if (inSR[i] == 1) {
            ans[i] = i;
        }
    }
    
    DFS(head, visted, S, dfs, inSR, ans);// traverse every city
    
    /*
    for (int i=0; i<N; i++) { //check dfs order
        printf("%d->", dfs[i]);
    }
    printf("\n");
    
    for (int i=1; i<N+1; i++) { //check ans array
        printf("%d:%d ", i, ans[i]);
    }
    printf("\n");
     
    for (int i=1; i<N+1; i++) { //check adjlist
        Node* ptr = head[i];
        while (ptr != NULL) {
            printf("%d->", ptr->city);
            ptr = ptr->next;
        }
        printf("\n");
    }
     */
    
    for (int i=0; i<Q; i++) { //answer output
        printf("%d\n", ans[query[i]]);
    }
    
    return 0;
}

