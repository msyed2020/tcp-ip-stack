#include "net.h"
#include "graph.c"

// Network Node Property APIs

bool_t nodeSetLoopbackAddress(node_t *node, char *ip_addr) {
    assert(ip_addr);

    node->nodeNetworkProp.isLoopback = true;
    strncpy(NODE_LO_ADDR(node), ip_addr, 16);
    NODE_LO_ADDR(node)[15] = '\0';
    return true;
}

bool_t nodeSetInterfaceIPAddress(node_t *node, char *localInterface, char *ip_addr, char mask) {
    interface_t *interface = getNodeIfByName(node, localInterface);
    if (!interface) {
        assert(0);
    }
    strncpy(IF_IP(interface), ip_addr, 16);
    IF_IP(interface)[15] = '\0';
    interface->interfaceNetworkProp.mask = mask;
    interface->interfaceNetworkProp.isIP = true;
    return true;
}

bool_t nodeRemoveInterfaceIPAddress(node_t *node, char *localInterface) {
    return true;
}