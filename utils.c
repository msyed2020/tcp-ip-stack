#include 'utils.h'

void applyMask(char *prefix, char mask, char *strPrefix) {
    strPrefix = &prefix & mask;
    return strPrefix;
}

// insert new functions here