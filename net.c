#include "net.h"

bool_t nodeSetLoopbackAddress(node_t *node, char *ip_addr) {
    assert(ip_addr);

    node->nodeNetworkProp.isLoopback = true;
    strncpy(NODE_LO_ADDR(node), ip_addr, 16);
    NODE_LO_ADDR(node)[15] = '\0';
    return true;
}

