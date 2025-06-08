// Extension of graph.h and graph.c to include networking properties

#ifndef __NET__
#define __NET__

// Every node has its own IP address, called as the loopback address

typedef struct ip_add { // IP address
    char ip_addr[16];
} ip_add_t;

// Every interace MUST have a MAC address and could have an IP address or mask

typedef struct mac_add { // MAC address
    char mac[48];
} mac_add_t;

typedef struct node_network_prop {
    bool_t isLoopBack;
    ip_add_t loopback_addr;
} node_network_prop_t;

static inline void initNodeNetworkProp(node_network_prop_t *nodeNetworkProp) {
    nodeNetworkProp->isLoopBack = false;
    memset(node_network_prop->loopback_addr.ip_addr, 0, 16);
}

typedef struct interface_network_prop {
    mac_add_t mac_addr;
    bool_t isIP;
    ip_add_t ip_address;
    char mask;
} interface_network_prop_t;

static inline void initInterfaceNetworkProp(interface_network_prop_t *interfaceNetworkProp) {
    memset(interfaceNetworkProp->mac_addr.mac, 0, 48);
    interfaceNetworkProp->isIP = false;
    memset(interfaceNetworkProp->ip_address.ip_addr, 0, 16);
    interfaceNetworkProp->mask = 0;
}

// MACROS
#define IF_MAC(interface_ptr)   ((interface_ptr)->interfaceNetworkProp.mac_add.mac)
#define IF_IP(interface_ptr)    ((interface_ptr)->interfaceNetworkProp.ip_add.ip_addr)
#define NODE_LO_ADDR(node_ptr)  (node_ptr->nodeNetworkProp.loopback_addr.ip_addr)

// Network Node Properties APIs

bool_t nodeSetLoopbackAddress(node_t *node, char *ip_addr);
bool_t nodeSetInterfaceIPAddress(node_t *node, char *localInterface, char *ip_addr, char mask);
bool_t nodeRemoveInterfaceIPAddress(node_t *node, char *localInterface);

#endif