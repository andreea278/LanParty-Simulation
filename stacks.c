#include "stacks.h"

int isEmpty(TeamName *top)
{
    return top == NULL;
}

void push(TeamName **top, Team team_inf)
{
    TeamName *new_node = newNode(team_inf);
    new_node->next = *top;
    *top = new_node;
}

Team pop(TeamName **top)
{
    TeamName *temp = (*top);
    Team aux = temp->team;
    *top = (*top)->next;
    freeNode(temp);
    return aux;
}

void deleleteStackLossers(TeamName **top)
{
    TeamName *temp;
    while (!isEmpty(*top))
    {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

void printWinnerStack(FILE *fp, TeamName *top)
{
    while (top)
    {
        printf("%-30s - %.02f\n", top->team.teamName, top->team.scoreTeam);
        top = top->next;
    }
}