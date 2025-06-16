#include <stdio.h>
#include "node.h"
#include "lib.h"

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    
    return node;
}

Node* appendNode(Node* head, int value) {
    if (head == NULL) return NULL;
    Node* node = createNode(value);
    if (node == NULL) return NULL;

    return appendToEnd(head, node);
}

Node* prependNode(Node* head, int value) {
    if (head == NULL) return NULL;
    Node* node = createNode(value);
    if (node == NULL) return NULL;
    return insertBefore(head, node);
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

Node* getNodeAfter(Node* head, int steps) {
    int currentStep = 0;
    while (head != NULL && currentStep < steps) {
        head = head->next;
        currentStep++;
    }
    return head;
}

Node* getNodeBefore(Node* tail, int steps) {
    int currentStep = 0;
    while (tail != NULL && currentStep < steps) {
        tail = tail->prev;
        currentStep++;
    }
    return tail;
}

Node* insertAfter(Node* node, Node* newNode) {
    if (node == NULL || newNode == NULL) return NULL;
    Node* next = node->next;
    node->next = newNode;
    newNode->prev = node;
    newNode->next = next;
    if (next != NULL) {
        next->prev = newNode;
    }

    return newNode; 
}

Node* insertBefore(Node* node, Node* newNode) {
    if (node == NULL || newNode == NULL) return NULL;
    Node* prev = node->prev;
    node->prev = newNode;
    newNode->next = node;
    newNode->prev = prev;
    if (prev != NULL) {
        prev->next = newNode;
    }

    return newNode;
}

Node* appendToEnd(Node* node, Node* newNode) {
    if (node == NULL || newNode == NULL) return NULL;
    while (node->next != NULL) {
        node = node->next;
    }
    return insertAfter(node, newNode); 
}

Node* prependToStart(Node* node, Node* newNode) {
    if (node == NULL || newNode == NULL) return NULL;
    while (node->prev != NULL) {
        node = node->prev;
    }
    return insertBefore(node, newNode);
}

Node* removePrev(Node* node) {
    if (node == NULL) return NULL;
    Node* prev = node->prev;
    Node* newPrev = NULL;
    if (prev != NULL) {
        newPrev = prev->prev;
        free(prev);
        newPrev->next = node;
    }
    node->prev = newPrev;

    return node;
}

Node* removeNext(Node* node) {
    if (node == NULL) return NULL;
    Node* next = node->next;
    Node* newNext = NULL;
    if (next != NULL) {
        newNext = next->next;
        free(next);
        newNext->prev = node;
    }
    node->next = newNext;

    return node;
}

int removePrevNodes(Node* node, int count) {
    if (node == NULL) return 0;
    if (count < 1) return 0;

    Node* curr = node;
    int currentCount = 0;
    Node* temp = NULL;
    while (curr != NULL && currentCount < count) {
        curr = curr->prev;
        if (temp != NULL) {
            free(temp);
        }
        temp = curr;
        currentCount++;
    }

    if (curr == NULL) {
        node->prev = NULL;
    } else {
        temp = curr->prev;
        if (temp != NULL) {
            temp->next = node;
        }
        free(curr);
        node->prev = temp;
    }

    return currentCount;
}

int removeNextNodes(Node* node, int count) {
    if (node == NULL) return 0;
    if (count < 1) return 0;

    Node* curr = node;
    int currentCount = 0;
    Node* temp = NULL;
    while (curr != NULL && currentCount < count) {
        curr = curr->next;
        if (temp != NULL) {
            free(temp);
        }
        temp = curr;
        currentCount++;
    }

    if (curr == NULL) {
        node->next = NULL;
    } else {
        temp = curr->next;
        if (temp != NULL) {
            temp->prev = node;
        }
        free(curr);
        node->next = temp;
    }

    return currentCount;
}

void free_list(Node* head) {
    Node* temp = head;
    while (head != NULL) {
        head = head->next;
        free(temp);
        temp = head;
    }
}
