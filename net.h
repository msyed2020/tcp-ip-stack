// Extension of graph.h and graph.c to include networking properties

#ifndef __NET__
#define __NET__

typedef struct ip_add { // IP address
    char ip_addr[16];
} ip_add_t;

typedef struct mac_add { // MAC address
    char mac[48];
} mac_add_t;