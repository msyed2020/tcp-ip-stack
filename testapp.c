#include "graph.h"

extern graph_t *buildFirstTopo();
extern void dumpGraph(graph_t *graph);

int main(int argc, char **argv) {
    graph_t *topo = buildFirstTopo();
    dumpGraph(topo);
    return 0;
}