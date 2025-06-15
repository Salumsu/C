#include <stdlib.h>

#ifndef NODE_H
#define NODE_H

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int value); 
Node* appendNode(Node* head, int value);
Node* prependNode(Node* head, int value);

// popHeadNode frees the original head and returns the new head.
// The caller must not free the original head again.
Node* popHeadNode(Node* head);

// popTailNode frees the original tail and returns the new tail.
// The caller must not free the original tail again.
Node* popTailNode(Node* tail);

void printNodes(Node* head);
void printNodesFromTail(Node* tail);

#endif