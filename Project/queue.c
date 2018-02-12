#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

//Inizializza una coda
void initQueue(Queue *q){
    q->head = q->tail = NULL;
}

//Aggiungi un elemento in coda
void addToQueue(Queue *q, Value elem){
    
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = elem;
    node->next = NULL;
    
    if(q->head == NULL && q->tail == NULL){
        //Primo elemento della coda
        q->head = node;
        q->tail = node;
    }    
    else{
        q->tail->next = node;
        q->tail = node;
    }
        
  
}

//Rimuovi un elemento dalla coda, e memorizzalo in output_node
int removeFromQueue(Queue *q, Value *output_value){
    if(q->tail == NULL && q->head == NULL) return FALSE;
    
    if(output_value != NULL){
        *output_value = q->head->value;
    }
    if(q->head == q->tail){
        free(q->head);
        
        q->head = NULL;
        q->tail = NULL;
        
        return TRUE;
    }
    
    Node *tmp = q->head;
    q->head = q->head->next;
    
    
    free(tmp);
    
    return TRUE;
}


void debugQueue(Queue q){

    Node *currentNode = q.head;
    int nElems = 0;
    while(currentNode){
        nElems++;
        currentNode = currentNode->next;
    }
    
    if(nElems>0)
    printf("%d elementi nella coda..\n", nElems);
    
}
