#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

static void gluedLLAddNextNode(glued_ll_node_t *curr, glued_ll_node_t *newNode) {
    if (!curr->right) {
        curr->right = newNode;
        newNode->left = curr;
        return;
    }

    glued_ll_node_t *temp = curr->right;
    curr->right = newNode;
    newNode->left = curr;
    newNode->right = temp;
    temp->left = newNode;
}

void gluedLLAddFront(glued_ll_t *list, glued_ll_node_t *node) {
    node->left = NULL;
    node->right = NULL;
    if (!list->head) {
        list->head = node;
        return;
    }
    gluedLLAddNextNode(node, list->head);
    list->head = node;
}

static void gluedLLNodeRemoval(glued_ll_node_t *node) {
    if (!node->left) {
        if (node->right) {
            node->right->left = NULL;
            node->right = 0;
            return;
        }
        return;
    }

    if (!node->right) {
        node->left->right = NULL;
        node->left = NULL;
        return;
    }

    node->left->right = node->right;
    node->right->left = node->left;
    node->left = NULL;
    node->right = NULL;
}

void gluedLLRemoveNode(glued_ll_t *list, glued_ll_node_t *node) {
    if (list->head == node)
        list->head = node->right;
    gluedLLNodeRemoval(node);
}

void initGluedLL(glued_ll_t *linkedList, unsigned int offset) {
    linkedList->head = NULL;
    linkedList->offset = offset;
}