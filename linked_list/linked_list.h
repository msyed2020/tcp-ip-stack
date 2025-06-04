#ifndef __GLUELL__
#define __GLUELL__

#include <stddef.h>

typedef struct glued_ll_node {
    struct glued_ll_node *left;
    struct glued_ll_node *right;
} glued_ll_node_t;

typedef struct glued_ll {
    glued_ll_node_t *head;
    unsigned int offset;
} glued_ll_t;

void gluedLLAddFront(glued_ll_t *list, glued_ll_node_t *node);

void gluedLLRemoveNode(glued_ll_t *list, glued_ll_node_t *node);

#define ITERATE_GLUED_LL_BEGIN(lstptr, struct_type, ptr)    \
{                                                           \
    glued_ll_node_t *gluedNode = NULL;                      \
    glued_ll_node_t *next = NULL;                           \
    for (gluedNode = (lstptr)->head; gluedNode; gluedNode = next) {   \
        next = gluedNode->right;                            \
        ptr = (struct_type *)((char *) gluedNode - (lstptr)->offset);
      
#define ITERATE_GLUED_LL_END }}

#define gluedLLNodeInit(gluedNode)  \
    do {                            \
        (gluedNode)->left = NULL;   \
        (gluedNode)->right = NULL;  \
    } while(0)

void initGluedLL(glued_ll_t *linkedList, unsigned int offset);

#endif