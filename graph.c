#include <stdlib.h>
#include <graph.h>

static inline node_t* get_nbr_node(interface_t *interface) {
    return &interface->attrNode;
}