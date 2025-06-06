#include <stdlib.h>
#include "graph.h"
#include <string.h>
#include <stdio.h>

static inline node_t* getNBRNode(interface_t *interface) {
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
        strncpy(link->interface1.ifName, fromIfName, INTERF_NAME_SIZE);
        link->interface1.ifName[INTERF_NAME_SIZE - 1] = '\0';
        strncpy(link->interface2.ifName, toIfName, INTERF_NAME_SIZE);
        link->interface2.ifName[INTERF_NAME_SIZE - 1] = '\0';

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
        node1->interfaces[emptyINTERFSlot] = &link->interface1;

        emptyINTERFSlot = getNodeINTFAvailableSlot(node2);
        node2->interfaces[emptyINTERFSlot] = &link->interface2;
    }

graph_t *createNewGraph(char *topologyName) {
    graph_t *graph = calloc(1, sizeof(graph_t));
    strncpy(graph->topologyName, topologyName, sizeof(graph->topologyName) - 1);
    graph->topologyName[sizeof(graph->topologyName) - 1] = '\0';
    initGluedLL(&graph->nodeList, offsetof(node_t, graphGlue));
    return graph;
}

node_t *createGraphNode(graph_t *graph, char *nodeName) {
    node_t *node = calloc(1, sizeof(node_t));
    strncpy(node->nodeName, nodeName, NODE_NAME_SIZE);
    node->nodeName[NODE_NAME_SIZE] = '\0';
    initGluedLL(&node->graphGlue);
    gluedLLAddFront(&graph->nodeList, &node->graphGlue);
    return node;
}

// edit the following functions for our code later

static inline interface_t * getNodeIfByName(node_t *node, char *ifName) {
    if (!node || !ifName) {
        return NULL;
    }

    for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
        if (node->interfaces[i] && strcmp(node->interfaces[i]->ifName, ifName) == 0) {
            return node->interfaces[i];
        }
    }

    return NULL;
}


static inline node_t *getNodeByNodeName(graph_t *topo, char *nodeName) {
    if (!topo || !nodeName)
        return NULL;

    node_t *currentNode = NULL;

    ITERATE_GLUED_LL_BEGIN(&topo->nodeList, node_t, currentNode) {
        if (strcmp(currentNode->nodeName, nodeName) == 0) {
            return currentNode;
        }
    } ITERATE_GLUED_LL_END;

    return NULL;
}

graph_t *buildFirstTopo() { // ensure this crap works
    graph_t *topo = createNewGraph("MyFirstTopo");

    node_t *R1 = createGraphNode(topo, "R1");
    node_t *R2 = createGraphNode(topo, "R2");
    node_t *R3 = createGraphNode(topo, "R3");

    insertLinkBetweenNodes(R1, R2, "eth0", "eth1", 1);
    insertLinkBetweenNodes(R2, R3, "eth2", "eth3", 1);
    insertLinkBetweenNodes(R1, R3, "eth4", "eth5", 3);

    return topo;
}

void dumpGraph(graph_t *graph) { // and this too
    printf("Topology: %s\n", graph->topologyName);

    node_t *node = NULL;
    ITERATE_GLUED_LL_BEGIN(&graph->nodeList, node_t, node) {
        printf("Node: %s\n", node->nodeName);

        for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
            interface_t *intf = node->interfaces[i];
            if (intf && intf->link) {
                node_t *nbr = (intf == &intf->link->interface1)
                                ? intf->link->interface2.attNode
                                : intf->link->interface1.attNode;

                printf("  Interface: %s --> %s (cost: %u)\n",
                    intf->ifName, nbr->nodeName, intf->link->cost);
            }
        }
    } ITERATE_GLUED_LL_END;
}