#include "BTS.h"

NodeBTS *newNodeBts(Team teamInfo)
{
    NodeBTS *node = (NodeBTS *)malloc(sizeof(NodeBTS));
    node->team = allocMemoryTeam(teamInfo);
    node->right = node->left = NULL;
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