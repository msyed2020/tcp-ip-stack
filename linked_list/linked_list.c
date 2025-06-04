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
    glued_ll_node_t *head = list->head;
    gluedLLAddNextNode(node, head);
    list->head = node;
}

static void gluedLLNodeRemoval(glued_ll_node_t *node) {
    if (!node->left) {
        if (node->right) {
            node->left->right = NULL;
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

}