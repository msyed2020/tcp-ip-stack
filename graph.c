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

void insertLinkBetweenNodes(node_t *node1, node_t *node2,
    char *fromIfName, char *toIfName, unsigned int cost) {
        link_t *link = calloc(1, sizeof(link_t));
        strncpy(link->interfacel.ifName, fromIfName, INTERF_NAME_SIZE);
        link->interface1.ifName[INTERF_NAME_SIZE] = '\0';
        strncpy(link->interface2.ifName, toIfName, INTERF_NAME_SIZE);
        link->interface2.ifName[INTERF_NAME_SIZE] = '\0';
    }

graph_t *createNewGraph(char *topologyName) {
    graph_t *graph = calloc(1, sizeof(graph_t));
    strncpy(graph->topologyName, topologyName, 32);
    graph->topologyName[32] = '\0';
    init_glthread(&graph->nodeList);
    return graph;
}

node_t *createGraphNode(graph_t *graph, char *nodeName) {
    node_t *node = calloc(1, sizeof(node_t));
    strncpy(node->nodeName, nodeName, NODE_NAME_SIZE);
    node->nodeName[NODE_NAME_SIZE] = '\0';
    init_glthread(&node->graphGlue);
    glthreadAddNext(&graph->nodeList, &node->graphGlue);
    return node;
}