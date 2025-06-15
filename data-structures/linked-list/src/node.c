#include <stdio.h>
#include "node.h"
#include "lib.h"

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    
    return node;
}

Node* popHeadNode(Node* head) {
    if (head == NULL) return NULL;
    Node* temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }

    free(temp);

    return head; 
}

Node* popTailNode(Node* tail) {
    if (tail == NULL) return NULL;
    Node* temp = tail;
    tail = tail->prev;
    if (tail != NULL) {
        tail->next = NULL;
    }

    free(temp);

    return tail; 
}

void printNodes(Node* head) {
    int index = 0;
    while (head != NULL) {
        DEBUG_PRINT("%d: %d\n", index, head->value);
        head = head->next;
        index++;
    }
}

void printNodesFromTail(Node* tail) {
    int index = 0;
    while (tail != NULL) {
        DEBUG_PRINT("%d: %d\n", index, tail->value);
        tail = tail->prev;
        index++;
    }
}