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
}