#include "event.h"
#include "types.h"

typedef Event Value;

struct SElement{
    Value value;
    struct SElement *next;
};
typedef struct SElement Node;

struct SCoda{
    Node *head, *tail;
};
typedef struct SCoda Queue;

//Inizializza una coda
void initQueue(Queue *q);

//Aggiungi un elemento in coda
void addToQueue(Queue *q, Value value);

//Rimuovi un elemento dalla coda, e memorizzalo in output_node
int removeFromQueue(Queue *q, Value *output_node);

void debugQueue(Queue q);
