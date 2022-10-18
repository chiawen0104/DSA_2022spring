//
//  main.c
//  hw1-5
//
//  Created by 盧家雯 on 2022/3/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int M,N,K; //bathrooms, situations, groups

typedef struct node{
    int id;
    int group;
    struct node *next;
    struct node *prev;
}Node;

//Create a new Node
Node* GetNewNode(int i, int j) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->group = i;
    newNode->id = j;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

Node* SearchGroup(Node* last, int i){
    Node* node = last;
    
    while(node != NULL){
        if (node->group == i){
            return node;
        }
        node=node->prev;
    }
    return last;
}

int enter(int i, int j, int m, Node* head[], Node* line[]){
    
    if (head[m]->id == -1 && head[m]->group == -1) { //create first node
        head[m]->group = i;
        head[m]->id = j;
        head[m]->next = NULL;
        head[m]->prev = NULL;
        line[m] = head[m];
    }
    else {
        Node* in_node = SearchGroup(line[m], i); //node position of same group
        if (in_node->next == NULL) { //add a node in tail
            Node* newNode = GetNewNode(i,j);
            line[m]->next = newNode;
            newNode->prev = line[m];
            line[m] = newNode;
        }
        else{ //insert a node in middle
            Node* newNode = GetNewNode(i, j);
            Node* tmp = in_node->next;
            
            tmp->prev = newNode;
            in_node->next = newNode;
            newNode->prev = in_node;
            newNode->next = tmp;
        }
    }
    return 0;
}

//delete last node
int leave(Node* last, Node* line[], int m){
    if (last->prev == NULL) { //only one node: initialize it
        last->group = -1;
        last->id = -1;
        last->next = NULL;
        return 0;
    }
    else{
        Node* tmp = last;
        last = last->prev;
        last->next = NULL;
        line[m] = last;
        free(tmp);
    }
    return 0;
}

//find the nearest bathroom using for loop to find index of bathroom
int FindBathroom (int m, Node* head[]){
    for (int i=m-1; i>=0; i--) {
        if (head[i]->group != -2 && head[i]->id != -2) {
            return i;
        }
    }
    for (int i=M-1; i>m; i--) {
        if (head[i]->group != -2 && head[i]->id != -2) {
            return i;
        }
    }
    
    return -1;
}

void To_nonempty (Node* head[], Node* line[], int m, int target) {
    //printf("From %d:%d-%d\n", m, head[m]->group, head[m]->id);
    
    while (line[m]->prev != NULL) { //move non-head nodes
        //printf("*now:%d-%d\n", line[m]->group, line[m]->id);
        Node* des_node = SearchGroup(line[target], line[m]->group); //node position of target
        Node* copy = line[m];
        
        line[m] = line[m]->prev;
        line[m]->next = NULL;
        
        if (des_node->next == NULL) { //insert at tail of line[target]
            des_node->next = copy;
            copy->prev = des_node;
            copy->next = NULL;
            line[target] = copy;
        }
        else{ //cut into middle of line[target]
            Node* tmp = des_node->next;
            tmp->prev = copy;
            des_node->next = copy;
            copy->prev = des_node;
            copy->next = tmp;
        }
    }
    //move head node
    Node* newNode = GetNewNode(head[m]->group, head[m]->id);
    Node* des_node = SearchGroup(line[target], line[m]->group); //node position of target
    
    if (des_node->next == NULL) { //insert at tail of line[target]
        des_node->next = newNode;
        newNode->prev = des_node;
        newNode->next = NULL;
        line[target] = newNode;
    }
    else{ //cut into middle of line[target]
        Node* tmp = des_node->next;
        tmp->prev = newNode;
        des_node->next = newNode;
        newNode->prev = des_node;
        newNode->next = tmp;
    }
    //printf("Tar%d:%d-%d\n", target, line[target]->group, line[target]->id);
}

void To_empty (Node* head[], Node* line[], int m, int target){
    //line[m] tail＆line[target] head
    head[target]->group = line[m]->group;
    head[target]->id = line[m]->id;
    line[m]=line[m]->prev;
    head[target]->next = NULL;
    head[target]->prev = NULL;
    line[target] = head[target];
    
    if (line[m] == NULL) return;
    
    while (line[m]->prev != NULL) {
        Node* copy = line[m];
        line[m]=line[m]->prev;
        
        line[target]->next = copy;
        copy->prev = line[target];
        copy->next = NULL;
        line[target] = copy;
    }
        
    //line[m] head＆line[target] tail
    Node* last = GetNewNode(line[m]->group, line[m]->id);
    line[target]->next = last;
    last->prev = line[target];
    last->next = NULL;
    line[target] = last;
    //printf("line tar: %d-%d\n", line[target]->group, line[target]->id);
}


void CLOSE (Node* head[], Node* line[], int m, int target){
    //Move line[m] to line[target]
    if (head[m]->group >= 0 && head[m]->id >= 0) {
        if (head[target]->group == -1 && head[target]->id == -1){ //empty target
            To_empty(head, line, m, target);
        }
        else { //nonempty target
            To_nonempty(head, line, m, target);
        }
    }
    //close bathroom m, label head[m] -2
    head[m]->group = -2;
    head[m]->id = -2;
    head[m]->next = NULL;
    head[m]->prev = NULL;
}

//print each line
void PrintLine (Node* head[]) {
    Node* curr;
    for (int k=0; k<M; k++) {
        //printf("line %d: ",k);
        curr = head[k]; //point to head
        if (curr->group >= 0 && curr->id >= 0) {
            while(1){
                printf("%d ", curr->id);
                //printf("%d-%d ", curr->group, curr->id);
                curr = curr->next;
                if (curr == NULL){
                  break;
                }
            }
        }
        printf("\n");
    }
}

void FreeNode (Node* head[], Node* line[]){
    
    for (int k=0; k<M; k++) { //free all node
        line[k] = head[k];
        while (line[k] != NULL) {
            Node* next = line[k]->next;
            free(line[k]);
            line[k] = next;
        }
    }
}

int main() {
    char situ[6];//input of situation
    int i,j,m;//input of group, id and line
    
    scanf("%d%d%d", &M, &N, &K);
    
    Node* head[M];//head pointer to node of each bathroom
    Node* line[M]; //current pointer to node of each bathroom
    
    for (int k=0; k<M; k++) { //initialize head
        head[k] = (Node*)malloc(sizeof(Node));
        head[k]->id = -1;
        head[k]->group = -1;
        head[k]->next = NULL;
        head[k]->prev = NULL;
        line[k] = head[k];
    }
    
    for (int n=0; n<N; ++n) {
        scanf("%s", situ);
        
        switch(situ[0]){
            case 'e': //USB enter
                scanf("%d%d%d", &i, &j, &m);
                enter(i, j, m, head, line);
                break;
                
            case 'l': //leave: last USB leave bathroom
                scanf("%d", &m);
                leave(line[m], line, m);
                break;
                
            case 'g': //go: first USB go to bathroom
                scanf("%d", &m);
                
                //delete first node
                if (head[m]->next == NULL) { //only one node: initialize it
                    head[m]->group = -1;
                    head[m]->id = -1;
                    head[m]->prev = NULL;
                    head[m]->next = NULL;
                }
                else{
                    Node* tmp = head[m]; //2 or more nodes
                    head[m] = head[m]->next;
                    head[m]->prev = NULL;
                    free(tmp);
                }
                break;
                
            case 'c': //close the bathroom
                scanf("%d", &m);
                int target = FindBathroom(m, head);
                //printf("target index:%d\n", target);
                CLOSE(head, line, m, target);
                //PrintLine(head);
                break;
        }
    }
    
    PrintLine(head);
    FreeNode(head, line);
    
    return 0;
}

