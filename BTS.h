#include "queue.h"
typedef struct nodeBts
{
    Team team;
    struct nodeBts *left, *right;
} NodeBTS;
NodeBTS *newNodeBts(Team teamInfo);
NodeBTS *insert(NodeBTS *node, Team teamInfo);
void printBTS(FILE *fp, NodeBTS *winners);