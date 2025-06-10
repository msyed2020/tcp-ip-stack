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

// Functionality Subprograms

void interfaceAssignMacAddress(interface_t *interface) {
    node_t *node = interface->att_node;

    if(!node) return;

    unsigned int hash_code_val = 0;
    hash_code_val = hash_code(node->node_name, NODE_NAME_SIZE);
    hash_code_val *= hash_code(interface->if_name, IF_NAME_SIZE);
    memset(IF_MAC(interface), 0, sizeof(IF_MAC(interface)));
    memcpy(IF_MAC(interface), (char *)&hash_code_val, sizeof(unsigned int));

}

static unsigned int hash_code(void *ptr, unsigned int size) {
    unsigned int value=0, i =0;
    char *str = (char*) ptr;
    while(i < size) {
        value += *str;
        value*=97;
        str++;
        i++;
    }
    return value;

}