#include "lists.h"

TeamName *newNode(Team team_inf)
{
    TeamName *node = (TeamName *)malloc(sizeof(TeamName));
    node->team.nr_players = team_inf.nr_players;
    node->team.teamName = (char *)malloc(strlen(team_inf.teamName) + 1);
    strcpy(node->team.teamName, team_inf.teamName);
    node->team.players = (Player *)malloc(sizeof(Player) * team_inf.nr_players);
    for (int i = 0; i < team_inf.nr_players; i++)
    {
        node->team.players[i].firstName = (char *)malloc(strlen(team_inf.players[i].firstName) + 1);
        strcpy(node->team.players[i].firstName, team_inf.players[i].firstName);
        node->team.players[i].secondName = (char *)malloc(strlen(team_inf.players[i].secondName) + 1);
        strcpy(node->team.players[i].secondName, team_inf.players[i].secondName);
        node->team.players[i].points = team_inf.players[i].points;
    }
    node->next = NULL;
    return node;
}
void freeNode(TeamName *node)
{
    free(node->team.teamName);
    for (int i = 0; i < node->team.nr_players; i++)
    {
        free(node->team.players[i].firstName);
        free(node->team.players[i].secondName);
    }
    free(node->team.players);
    free(node);
}
void addAtBeggining(TeamName **head, Team team_inf)
{
    TeamName *new_node = newNode(team_inf);
    new_node->next = *head;
    *head = new_node;
}

void addAtEnd(TeamName **head, Team team_inf)
{
    TeamName *new_node = newNode(team_inf);
    TeamName *aux = *head;
    if (*head == NULL)
    {
        addAtBeggining(&*head, team_inf);
        return;
    }
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = new_node;
    new_node->next = NULL;
}