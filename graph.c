#include <stdlib.h>
#include "graph.h"
#include <string.h>
#include <stdio.h>

static inline node_t* get_NBRNode(interface_t *interface) {
    return interface->attNode;
}

static inline int getNodeINTFAvailableSlot(node_t *node) {
    for(int i=0; i < MAX_INTF_PER_NODE; i++) {
        if(node->interfaces[i] == NULL)
            return i;
    }
    return -1;
}

graph_t *createNewGraph(char *topologyName) {
    graph_t *graph = calloc(1, sizeof(graph_t));
    strncpy(graph->topologyName, topologyName, 32);
    graph->topologyName[32] = '\0';
    init_glthread(&graph->nodeList);
    return graph;
}