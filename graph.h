typedef struct interface {
    char if_name[IF_NAME_SIZE];
    struct node *attNode;
    struct link *link;
} interface_t;

struct link {
    interface_t interface1;
    interface_t interface2;
    unsigned int cost;
}

typedef struct graph {
    char topologyName[32];
    glued_ll_t nodeList;
};

