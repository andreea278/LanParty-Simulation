#include "queue.h"
typedef struct nodeBts
{
    Team team;
    int height;
    struct nodeBts *left, *right;
} NodeBTS;
NodeBTS *newNodeBts(Team teamInfo);
NodeBTS *insert(NodeBTS *node, Team teamInfo);
void printBTS(FILE *fp, NodeBTS *winners);
int nodeHeightAVL(NodeBTS *root);
NodeBTS *RightRotattion(NodeBTS *z);
NodeBTS *LeftRotation(NodeBTS *z);
NodeBTS *LRRotation(NodeBTS *z);
NodeBTS *RLRotation(NodeBTS *z);
int max(int a, int b);
NodeBTS *insertAVL(NodeBTS *node, Team teamInfo);
void addBTSinAVL(NodeBTS *node, NodeBTS **AVL);
void printInOrder(FILE *fp, NodeBTS *root);