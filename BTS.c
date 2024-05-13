#include "BTS.h"

NodeBTS *newNodeBts(Team teamInfo)
{
    NodeBTS *node = (NodeBTS *)malloc(sizeof(NodeBTS));
    node->team = allocMemoryTeam(teamInfo);
    node->right = node->left = NULL;
    node->height = 0;
    return node;
}

NodeBTS *insert(NodeBTS *node, Team teamInfo)
{
    if (node == NULL)
        return newNodeBts(teamInfo);
    if (teamInfo.scoreTeam < node->team.scoreTeam)
    {
        node->left = insert(node->left, teamInfo);
    }
    else if (teamInfo.scoreTeam > node->team.scoreTeam)
    {
        node->right = insert(node->right, teamInfo);
    }
    else if (teamInfo.scoreTeam == node->team.scoreTeam)
    {
        if (strcmp(teamInfo.teamName, node->team.teamName) < 0)
        {
            node->left = insert(node->left, teamInfo);
        }
        else if (strcmp(teamInfo.teamName, node->team.teamName) > 0)
        {
            node->right = insert(node->right, teamInfo);
        }
    }
    return node;
}

void printBTS(FILE *fp, NodeBTS *winners)
{
    if (winners == NULL)
    {
        return;
    }
    printBTS(fp, winners->right);
    fprintf(fp, "%-33s -  %.02f\n", winners->team.teamName, winners->team.scoreTeam);
    printBTS(fp, winners->left);
}
int max(int a, int b)
{
    return ((a > b) ? a : b);
}
int nodeHeightAVL(NodeBTS *root)
{
    if (root == NULL)
    {
        return 1;
    }
    else
        return root->height;
}

NodeBTS *RightRotattion(NodeBTS *z)
{
    NodeBTS *y = z->left;
    NodeBTS *T3 = y->right;
    y->right = z;
    z->left = T3;
    z->height = max(nodeHeightAVL(z->left), nodeHeightAVL(z->right)) + 1;
    y->height = max(nodeHeightAVL(y->left), nodeHeightAVL(y->right)) + 1;
    return y;
}

NodeBTS *LeftRotation(NodeBTS *z)
{
    NodeBTS *y = z->right;
    NodeBTS *T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = max(nodeHeightAVL(z->left), nodeHeightAVL(z->right)) + 1;
    y->height = max(nodeHeightAVL(y->left), nodeHeightAVL(y->right)) + 1;
    return y;
}

NodeBTS *LRRotation(NodeBTS *z)
{
    z->left = LeftRotation(z->left);
    return RightRotattion(z);
}
NodeBTS *RLRotation(NodeBTS *z)
{
    z->right = RightRotattion(z->right);
    return LeftRotation(z);
}

NodeBTS *insertAVL(NodeBTS *node, Team teamInfo)
{
    if (node == NULL)
    {
        node = newNodeBts(teamInfo);
        return node;
    }
    if (teamInfo.scoreTeam < node->team.scoreTeam)
        node->left = insertAVL(node->left, teamInfo);
    else if (teamInfo.scoreTeam > node->team.scoreTeam)
        node->right = insertAVL(node->right, teamInfo);
    else
    {
        if (strcmp(teamInfo.teamName, node->team.teamName) < 0)
        {
            node->left = insertAVL(node->left, teamInfo);
        }
        else if (strcmp(teamInfo.teamName, node->team.teamName) > 0)
        {
            node->right = insertAVL(node->right, teamInfo);
        }
        // else
        //     return node;
    }
    node->height = 1 + max(nodeHeightAVL(node->left), nodeHeightAVL(node->right));
    int k = nodeHeightAVL(node->left) - nodeHeightAVL(node->right);
    if (k > 1 && teamInfo.scoreTeam < node->left->team.scoreTeam)
        return RightRotattion(node);
    if (k < -1 && teamInfo.scoreTeam > node->right->team.scoreTeam)
        return LeftRotation(node);
    if (k > 1 && teamInfo.scoreTeam > node->left->team.scoreTeam)
        return LRRotation(node);
    if (k < -1 && teamInfo.scoreTeam < node->right->team.scoreTeam)
        return RLRotation(node);
    return node;
}

void addBTSinAVL(NodeBTS *node, NodeBTS **AVL)
{
    if (node == NULL)
    {
        return;
    }
    addBTSinAVL(node->right, AVL);
    *AVL = insertAVL(*AVL, node->team);
    addBTSinAVL(node->left, AVL);
}

void printInOrder(FILE *fp, NodeBTS *root)
{
    if (root != NULL)
    {
        printInOrder(fp, root->right);
        if (root->height == 2)
            fprintf(fp, "%s\n", root->team.teamName);
        printInOrder(fp, root->left);
    }
}