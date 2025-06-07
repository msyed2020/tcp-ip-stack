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