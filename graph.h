#include "linked_list/linked_list.h"

#define NODE_NAME_SIZE  16
#define INTERF_NAME_SIZE  16
#define MAX_INTF_PER_NODE  10

typedef struct node node_t;
typedef struct link link_t;

typedef struct interface {
    char ifName[INTERF_NAME_SIZE];
    struct node *attNode;
    struct link *link;
} interface_t;

struct link {
    interface_t interface1;
    interface_t interface2;
    unsigned int cost;
};

struct node {
    char nodeName[NODE_NAME_SIZE];
    interface_t *interfaces[MAX_INTF_PER_NODE];
    glued_ll_t graphGlue;
};

typedef struct graph {
    char topologyName[32];
    glued_ll_t nodeList;
} graph_t;

static inline node_t* getNBRNode(interface_t *interface);
static inline int getNodeINTFAvailableSlot(node_t *node);

#define ITERATE_GLUED_LL_BEGIN(lstptr, struct_type, ptr)        \
{                                                               \
    glued_ll_node_t *gluedNode = NULL;                          \
    glued_ll_node_t *next = NULL;                               \
    for (gluedNode = (lstptr)->head; gluedNode; gluedNode = next) { \
        next = gluedNode->right;                                \
        ptr = (struct_type *)((char *) gluedNode - (lstptr)->offset);

#define ITERATE_GLUED_LL_END }}
