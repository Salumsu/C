#include <stdlib.h>
#include <stdio.h>
#include "node.h" 
#include "lib.h"

typedef struct LinkedList {
    int size;
    Node* head;
    Node* tail;
} LinkedList;

LinkedList* createLinkedList() {
    LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
    linkedList->size = 0;
    linkedList->head = NULL;
    linkedList->tail = NULL;

    return linkedList;
}

Node* append (LinkedList* linkedList, int value) {
    if (linkedList == NULL) return NULL;
    Node* node = createNode(value);
    if (node == NULL) return NULL;
    
    if (linkedList->head == NULL) {
        linkedList->head = node;
    } 

    if (linkedList->tail != NULL) {
        linkedList->tail->next = node;
    }

    node->prev = linkedList->tail;
    linkedList->tail = node;
    linkedList->size++;
    return node;
}

Node* prepend (LinkedList* linkedList, int value) {
    if (linkedList == NULL) return NULL;
    Node* node = createNode(value);
    if (node == NULL) return NULL;

    node->next = linkedList->head;
    if (linkedList->head != NULL) {
        linkedList->head->prev = node;
    } 
    linkedList->head = node;
    if (linkedList->tail == NULL) {
        linkedList->tail = node;
    }
    linkedList->size++;

    return node;
}

Node* insertAt (LinkedList* linkedList, int value, int index) {
    if (linkedList == NULL) return NULL;
    index = prepareIndex(linkedList->size, index);
    if (index < 0) return NULL;

    if (index == 0) return prepend(linkedList, value); 
    if (index == linkedList->size) return append(linkedList, value);
    
    Node* node = createNode(value);
    if (node == NULL) return NULL;

    int currentIndex = 1;
    Node* prev = linkedList->head;
    Node* curr = prev->next;

    while (curr != NULL && currentIndex < index) {
        prev = curr;
        curr = curr->next;
        currentIndex++;
    }
    node->prev = prev;
    prev->next = node;
    node->next = curr;
    curr->prev = node;
    linkedList->size++;
    return node;
}

void popHead (LinkedList* linkedList) {
    if (linkedList == NULL || linkedList->size == 0) return;

    Node* newHead = popHeadNode(linkedList->head);
    linkedList->head = newHead;

    if (linkedList->size == 1) {
        linkedList->tail = NULL;
    }

    linkedList->size--;
}   

void popTail (LinkedList* linkedList) {
    if (linkedList == NULL || linkedList->size == 0) return;

    Node* newTail = popTailNode(linkedList->tail);
    linkedList->tail = newTail;

    if (linkedList->size == 1) {
        linkedList->head = NULL;
    }

    linkedList->size--;
}

void removeAt (LinkedList* linkedList, int index) {
    if (linkedList == NULL || linkedList->size == 0) return;
    index = prepareIndex(linkedList->size, index);
    if (index < 0) return;
    if (index == 0) return popHead(linkedList);
    if (index == linkedList->size) return popTail(linkedList);

    int currentIndex = 2;
    Node* prev = linkedList->head;
    Node* curr = prev->next;

    while (curr != NULL && currentIndex < index) {
        prev = curr;
        curr = curr->next;
        currentIndex++;
    }

    Node* temp = curr;
    curr = curr->next;
    prev->next = curr;
    if (curr != NULL) {
        curr->prev = prev;
    }
    free(temp);
    linkedList->size--;
}

void printLinkedList(LinkedList* linkedList) {
    printNodes(linkedList->head);
    DEBUG_PRINT("REVERSE\n");
    printNodesFromTail(linkedList->tail);
}

int main() {
    LinkedList* linkedList = createLinkedList();
    
    removeAt(linkedList, 0);

    append(linkedList, 5);
    append(linkedList, 2);
    prepend(linkedList, 6); 
    insertAt(linkedList, 4, 2); 
    insertAt(linkedList, 7, 0); 
    insertAt(linkedList, 8, linkedList->size * -1); 
    insertAt(linkedList, 3, -1); 
    insertAt(linkedList, 1, linkedList->size); 

    removeAt(linkedList, -9);

    printLinkedList(linkedList);

    return 0;
}