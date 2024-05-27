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

void deleleteStackLosers(TeamName **top)
{
    TeamName *temp;
    while (!isEmpty(*top))
    {
        temp = *top;
        *top = (*top)->next;
        freeNode(temp);
    }
}

void printWinnerStack(FILE *fp, TeamName *top, int nr_matches)
{
    int nr = nr_matches / 2;
    while (top && nr)
    {
        fprintf(fp, "%-33s -  %.02f\n", top->team.teamName, top->team.scoreTeam);
        top = top->next;
        nr--;
    }
}

// void printWinnerStack(FILE *fp, TeamName *top, int nr_matches)
// {
//     int nr = nr_matches / 2;
//     while (top && nr > 0)
//     {
//         Team team = pop(&top);
//         printf("%s\n", team.teamName);
//         fprintf(fp, "%-33s -  %.02f\n", team.teamName, team.scoreTeam);
//         nr--;
//     }
// }