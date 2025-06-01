#include "linked_list/linked_list.h"

#define NODE_NAME_SIZE  16
#define INTERF_NAME_SIZE  16
#define MAX_INTF_PER_NODE  10

typedef struct node node_t;
typedef struct link link_t;

typedef struct interface {
    char if_name[INTERF_NAME_SIZE];
    struct node *attNode;
    struct link *link;
} interface_t;

struct link {
    interface_t interface1;
    interface_t interface2;
    unsigned int cost;
}

struct node {
    char nodeName[NODE_NAME_SIZE];
    interface_t *intf[MAX_INTF_PER_NODE];
    glued_ll_t graphGlue;
}

typedef struct graph {
    char topologyName[32];
    glued_ll_t nodeList;
};

