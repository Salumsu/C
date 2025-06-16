#include <stdlib.h>

#ifndef NODE_H
#define NODE_H

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

/**
 * Creates a new node with the given value.
 * The new node's `next` and `prev` pointers are initialized to NULL.
 *
 * @param value The value to store in the node.
 * @return Pointer to the newly created node.
 */
Node* createNode(int value);

/**
 * Appends a new node with the given value to the end of the list.
 * Traverses from the given node to the tail, then appends.
 * 
 * @param head A pointer to any node in the list (ideally the head or tail).
 * @param value The value to insert at the end.
 * @return Pointer to the head of the list (unchanged unless list was empty).
 */
Node* appendNode(Node* head, int value);

/**
 * Prepends a new node with the given value to the start of the list.
 * Traverses from the given node to the head, then prepends.
 *
 * @param head A pointer to any node in the list (ideally the head or tail).
 * @param value The value to insert at the start.
 * @return Pointer to the new head of the list.
 */
Node* prependNode(Node* head, int value);

/**
 * Removes and frees the current head node.
 *
 * @param head Pointer to the current head node.
 * @return Pointer to the new head node, or NULL if list becomes empty.
 *
 * Note: The caller must not free the original head after this call.
 */
Node* popHeadNode(Node* head);

/**
 * Removes and frees the current tail node.
 *
 * @param tail Pointer to the current tail node.
 * @return Pointer to the new tail node, or NULL if list becomes empty.
 *
 * Note: The caller must not free the original tail after this call.
 */
Node* popTailNode(Node* tail);

/**
 * Prints the values of the nodes starting from the head.
 *
 * @param head Pointer to the head of the list.
 */
void printNodes(Node* head);

/**
 * Prints the values of the nodes starting from the tail.
 *
 * @param tail Pointer to the tail of the list.
 */
void printNodesFromTail(Node* tail);

/**
 * Returns the node located `steps` positions after the given node.
 * Follows the `next` pointers.
 *
 * @param node Starting node.
 * @param steps Number of steps to move forward.
 * @return Pointer to the resulting node, or NULL if out of bounds.
 */
Node* getNodeAfter(Node* node, int steps);

/**
 * Returns the node located `steps` positions before the given node.
 * Follows the `prev` pointers.
 *
 * @param node Starting node.
 * @param steps Number of steps to move backward.
 * @return Pointer to the resulting node, or NULL if out of bounds.
 */
Node* getNodeBefore(Node* node, int steps);

/**
 * Inserts `newNode` immediately after `node`.
 * Updates relevant `next` and `prev` pointers.
 *
 * @param node Existing node to insert after.
 * @param newNode The new node to insert.
 * @return Pointer to the inserted node (i.e., newNode).
 */
Node* insertAfter(Node* node, Node* newNode);

/**
 * Inserts `newNode` immediately before `node`.
 * Updates relevant `next` and `prev` pointers.
 *
 * @param node Existing node to insert before.
 * @param newNode The new node to insert.
 * @return Pointer to the inserted node (i.e., newNode).
 */
Node* insertBefore(Node* node, Node* newNode);

/**
 * Traverses forward from the given node to the last node,
 * and inserts `newNode` at the end.
 *
 * @param node Starting node for traversal (usually head or tail).
 * @param newNode The node to append.
 * @return Pointer to the head of the list (unchanged).
 *
 * Tip: The closer `node` is to the tail, the faster this completes.
 */
Node* appendToEnd(Node* node, Node* newNode);

/**
 * Traverses backward from the given node to the first node,
 * and inserts `newNode` at the start.
 *
 * @param node Starting node for traversal (usually head or tail).
 * @param newNode The node to prepend.
 * @return Pointer to the new head of the list.
 *
 * Tip: The closer `node` is to the head, the faster this completes.
 */
Node* prependToStart(Node* node, Node* newNode);

/**
 * Removes and frees the node immediately after the given node.
 *
 * If the removed node was the tail, the reference node becomes the new tail.
 * The caller may check if `node->next == NULL` to confirm this.
 *
 * @param node The reference node whose next node will be removed.
 * @return Pointer to the reference node (unchanged).
 */
Node* removeNext(Node* node);

/**
 * Removes and frees the node immediately before the given node.
 *
 * If the removed node was the head, the reference node becomes the new head.
 * The caller may check if `node->prev == NULL` to confirm this.
 *
 * @param node The reference node whose previous node will be removed.
 * @return Pointer to the reference node (unchanged).
 */
Node* removePrev(Node* node);


// NOTE: If a pointer seems to be invalid or points to garbage memory,
// it's possible the head or tail became NULL after removal.
// In such cases, the reference node (first parameter) should now be the new head or tail,
// because the original head/tail was among the removed nodes.
// Always check if head/tail needs to be updated after calling remove* functions.
/**
 * Removes and frees up to `count` nodes immediately after the given node.
 *
 * If fewer than `count` nodes exist after the given node, all available nodes will be removed.
 * 
 * If the last removed node was the tail, the reference node becomes the new tail.
 * The caller may check if `node->next == NULL` to confirm this.
 *
 * @param node The reference node from which to begin removing next nodes.
 * @param count The number of nodes to attempt to remove.
 * @return Number of nodes that where successfully removed.
 */
int removeNextNodes(Node* node, int count);

/**
 * Removes and frees up to `count` nodes immediately before the given node.
 *
 * If fewer than `count` nodes exist before the given node, all available nodes will be removed.
 *
 * If the last removed node was the head, the reference node becomes the new head.
 * The caller may check if `node->prev == NULL` to confirm this.
 *
 * @param node The reference node from which to begin removing previous nodes.
 * @param count The number of nodes to attempt to remove.
 * @return Number of nodes that where successfully removed.
 */
int removePrevNodes(Node* node, int count);

/**
 * Frees all nodes in a linked list starting from the given head.
 *
 * This function assumes that the passed-in pointer is the head of the list.
 * It will recursively or iteratively traverse the list and free each node.
 *
 * After calling this function, the entire list will be deallocated and
 * any pointer to the original head or its nodes will become invalid.
 *
 * @param head A pointer to the head node of the linked list.
 */
void free_list(Node* head);
#endif