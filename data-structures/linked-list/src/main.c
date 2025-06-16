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

void setFirstNode(LinkedList* linkedList, Node* node) {
    linkedList->head = linkedList->tail = node;
}

Node* append(LinkedList* linkedList, int value) {
    if (linkedList == NULL) return NULL;
    Node* node = createNode(value);
    if (node == NULL) return NULL;
    
    if (linkedList->size == 0) {
        setFirstNode(linkedList, node);
    } else {
        linkedList->tail = insertAfter(linkedList->tail, node);
    }
    
    linkedList->size++;
    return node;
}

Node* prepend(LinkedList* linkedList, int value) {
    if (linkedList == NULL) return NULL;
    Node* node = createNode(value);
    if (node == NULL) return NULL;

    if (linkedList->size == 0) {
        setFirstNode(linkedList, node);
    } else {
        linkedList->head = insertBefore(linkedList->head, node);
    }

    linkedList->size++;
    return node;
}

Node* insertAt(LinkedList* linkedList, int value, int index) {
    if (linkedList == NULL) return NULL;
    Node* node = createNode(value);
    if (node == NULL) return NULL;

    IndexPath* indexPath = getPathInfo(linkedList->size, index);
    if (indexPath == NULL) return NULL;
    if (indexPath->fromHead) {
        if (indexPath->steps == 0) {
            if (linkedList->size == 0) {
                setFirstNode(linkedList, node); 
            } else {
                linkedList->head = insertBefore(linkedList->head, node);
            }
        } else {
            Node* next = getNodeAfter(linkedList->head, indexPath->steps);
            insertBefore(next, node);
        }
    } else {
        if (indexPath->steps == 0) {
            if (linkedList->size == 0) {
                setFirstNode(linkedList, node);
            } else {
                linkedList->tail = insertAfter(linkedList->tail, node);
            }
        } else {
            Node* prev = getNodeBefore(linkedList->tail, indexPath->steps);  
            insertAfter(prev, node);
        }
    }
    free(indexPath);
    linkedList->size++;
    return node;
}

void popHead (LinkedList* linkedList) {
    if (linkedList == NULL || linkedList->size == 0) return;

    linkedList->head = popHeadNode(linkedList->head);
    linkedList->size--;

    if (linkedList->size == 0) {
        linkedList->tail = NULL;
    }

}   

void popTail (LinkedList* linkedList) {
    if (linkedList == NULL || linkedList->size == 0) return;

    linkedList->tail = popTailNode(linkedList->tail);
    linkedList->size--;

    if (linkedList->size == 0) {
        linkedList->head = NULL;
    }

}

void removeAt (LinkedList* linkedList, int index) {
    if (linkedList == NULL || linkedList->size == 0) return;
    if (index >= linkedList->size) return; // Special case because prepareIndex allows this
    IndexPath* indexPath = getPathInfo(linkedList->size, index);
    if (indexPath == NULL) return;
    if (indexPath->fromHead) {
        DEBUG_PRINT("FROM HEAD: %d\n", indexPath->steps);
        if (indexPath->steps == 0) {
            linkedList->head = popHeadNode(linkedList->head); 
            if (linkedList->head == NULL) {
                linkedList->tail = NULL;
            }
        } else {
            Node* prev = getNodeAfter(linkedList->head, indexPath->steps - 1);
            removeNext(prev);
        }
    } else {
        DEBUG_PRINT("FROM TAIL: %d\n", indexPath->steps);
        if (indexPath->steps == 1) {
            linkedList->tail = popTailNode(linkedList->tail);
            if (linkedList->tail == NULL) {
                linkedList->head = NULL;
            }
        } else {
            Node* next = getNodeBefore(linkedList->tail, indexPath->steps - 1);
            removePrev(next);
        }
    } 
    free(indexPath);
    linkedList->size--;
}

void printLinkedList(LinkedList* linkedList) {
    printNodes(linkedList->head);
    DEBUG_PRINT("REVERSE\n");
    printNodesFromTail(linkedList->tail);
}

int* to_array(LinkedList* linkedList) {
    int* array = malloc(sizeof(int) * linkedList->size);
    if (array == NULL) return NULL;
    Node* curr = linkedList->head;
    for (int i = 0; i < linkedList->size && curr != NULL; i++) {
        array[i] = curr->value;
        curr = curr->next;
    }

    return array;
}

void free_linked_list(LinkedList* linkedList) {
    free_list(linkedList->head);
    free(linkedList);
}

int main() {
    // IndexPath* indexPath = getPathInfo(5, 4);
    // printf("fromHead: %d\nsteps: %d\n", indexPath->fromHead, indexPath->steps); 
    LinkedList* linkedList = createLinkedList();
    
    append(linkedList, 5);                         // [5]
    append(linkedList, 2);                         // [5, 2]
    prepend(linkedList, 6);                        // [6, 5, 2]

    insertAt(linkedList, 4, 2);                    // [6, 5, 4, 2]
    insertAt(linkedList, 7, 0);                    // [7, 6, 5, 4, 2]
    insertAt(linkedList, 8, -linkedList->size);    // [8, 7, 6, 5, 4, 2]
    insertAt(linkedList, 3, -1);                   // [8, 7, 6, 5, 4, 3, 2]
    insertAt(linkedList, 1, linkedList->size);     // [8, 7, 6, 5, 4, 3, 2, 1]

    // // ✅ Insert into exact middle (even-sized list: index = size / 2 = 4)
    // insertAt(linkedList, 9, linkedList->size / 2); // [8, 7, 6, 5, 9, 4, 3, 2, 1]

    // // ✅ Insert multiple times at same index
    // insertAt(linkedList, 10, 2);                   // [8, 7, 10, 6, 5, 9, 4, 3, 2, 1]
    // insertAt(linkedList, 11, 2);                   // [8, 7, 11, 10, 6, 5, 9, 4, 3, 2, 1]
    // insertAt(linkedList, 99, 999);
    // insertAt(linkedList, 100, -999);

    // for (int i = 0; i < 10; i++) {
    //     insertAt(linkedList, 100 + i, 0);
    // }

    printLinkedList(linkedList);

    free(linkedList);

    return 0;
}