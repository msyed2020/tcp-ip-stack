#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

// THIS FILE ONLY EXISTS TO TEST THE GLUED LL. HAS NO PURPOSE W TCP/IP STACK

typedef struct my_node {
    int data;
    glued_ll_node_t glued_node;
} my_node_t;

int main() {
    glued_ll_t list;
    initGluedLL(&list, offsetof(my_node_t, glued_node));

    for (int i = 0; i < 5; i++) {
        my_node_t *new_node = (my_node_t *)malloc(sizeof(my_node_t));
        new_node->data = i;
        gluedLLNodeInit(&new_node->glued_node);
        gluedLLAddFront(&list, &new_node->glued_node);
        printf("Added node with data: %d\n", i);
    }

    printf("\nList contents:\n");
    my_node_t *node_ptr;
    ITERATE_GLUED_LL_BEGIN(&list, my_node_t, node_ptr)
        printf("Node data: %d\n", node_ptr->data);
    ITERATE_GLUED_LL_END

    if (list.head) {
        node_ptr = (my_node_t *)((char *)list.head - list.offset);
        printf("\nRemoving node with data: %d\n", node_ptr->data);
        gluedLLRemoveNode(&list, &node_ptr->glued_node);
        free(node_ptr);
    }

    printf("\nList contents after removal:\n");
    ITERATE_GLUED_LL_BEGIN(&list, my_node_t, node_ptr)
        printf("Node data: %d\n", node_ptr->data);
    ITERATE_GLUED_LL_END

    ITERATE_GLUED_LL_BEGIN(&list, my_node_t, node_ptr)
        glued_ll_node_t *temp = &node_ptr->glued_node;
        gluedLLRemoveNode(&list, temp);
        free(node_ptr);
    ITERATE_GLUED_LL_END

    return 0;
}
