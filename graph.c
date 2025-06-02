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
        // assigning the two links to each other and making
        // use of the link struct
        link_t *link = calloc(1, sizeof(link_t));
        strncpy(link->interfacel.ifName, fromIfName, INTERF_NAME_SIZE);
        link->interface1.ifName[INTERF_NAME_SIZE] = '\0';
        strncpy(link->interface2.ifName, toIfName, INTERF_NAME_SIZE);
        link->interface2.ifName[INTERF_NAME_SIZE] = '\0';

        // setting the pointers of the interfaces to the link

        link->interface1.link = link;
        link->interface2.link = link;

        // assigning the two linkable nodes to be the interface's
        // attached nodes

        link->interface1.attNode = node1;
        link->interface2.attNode = node2;

        link->cost = cost; // for cost later

        int emptyINTERFSlot;

        // look for empty slot in node to assign interface

        emptyINTERFSlot = getNodeINTFAvailableSlot(node1); 
        node1->interface[emptyINTERFSlot] = &link->interface1;

        emptyINTERFSlot = getNodeINTFAvailableSlot(node2);
        node2->interface[emptyINTERFSlot] = &link->interface2;
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

// edit the following functions for our code later

static inline interface_t * getNodeIfByName(node_t *node, char *ifName) {
    if (!node || !ifName) {
        return NULL;
    }

    for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
        if (node->interface[i] && strcmp(node->interface[i]->ifName, ifName) == 0) {
            return node->interface[i];
        }
    }

    return NULL;
}

static inline node_t * getNodeByNodeName(graph_t *topo, char *nodeName) {
    if (!topo || !nodeName) {
        return NULL;
    }

    node_t *currentNode = NULL;

    ITERATE_GRAPH_NODES_BEGIN(topo, currentNode) {
        if (strcmp(currentNode->nodeName, nodeName) == 0) {
            return currentNode;
        }
    } ITERATE_GRAPH_NODES_END;

    return NULL;
}