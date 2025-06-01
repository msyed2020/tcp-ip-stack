#include <stdlib.h>
#include <graph.h>

static inline node_t* get_nbr_node(interface_t *interface) {
    return &interface->attrNode;
}

static inline int get_node_intf_available_slot(node_t *node) {
    for(int i=0; i < MAX_INTERFACES_PER_NODE; i++) {
        if(node->interfaces[i] == NULL)
            return i;
    }
    return -1;
}