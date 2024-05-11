#include "queue.h"
int IsEmpty(TeamQueue *q)
{
    return (q->front == NULL);
}
Team allocMemoryTeam(Team team)
{
    Team teamG;
    teamG.nr_players = team.nr_players;
    teamG.teamName = (char *)malloc(strlen(team.teamName) + 1);
    strcpy(teamG.teamName, team.teamName);
    teamG.players = (Player *)malloc(sizeof(Player) * teamG.nr_players);
    for (int i = 0; i < teamG.nr_players; i++)
    {
        teamG.players[i].firstName = (char *)malloc(strlen(team.players[i].firstName) + 1);
        strcpy(teamG.players[i].firstName, team.players[i].firstName);
        teamG.players[i].secondName = (char *)malloc(strlen(team.players[i].secondName) + 1);
        strcpy(teamG.players[i].secondName, team.players[i].secondName);
        teamG.players[i].points = team.players[i].points;
    }
    teamG.scoreTeam = team.scoreTeam;
    return teamG;
}

NodeQueue *NewNodeQueue(Match game)
{
    NodeQueue *newNode = (NodeQueue *)malloc(sizeof(NodeQueue));
    newNode->game.team1 = allocMemoryTeam(game.team1);
    newNode->game.team2 = allocMemoryTeam(game.team2);
    newNode->next = NULL;
    return newNode;
}

void freeNodeQueue(NodeQueue *node)
{
    freeTeam(node->game.team1);
    freeTeam(node->game.team2);
    free(node);
}
void freeGames(Match *game, int nr_matches)
{
    for (int i = 0; i < nr_matches; i++)
    {
        freeTeam(game[i].team1);
        freeTeam(game[i].team2);
    }
    free(game);
}

void deleteQueue(TeamQueue *queue)
{
    Match aux;
    while (!IsEmpty(queue))
    {
        aux = deQueue(queue);
    }
    free(queue);
}

TeamQueue *createQueue()
{
    TeamQueue *q;
    q = (TeamQueue *)malloc(sizeof(TeamQueue));
    if (q == NULL)
        return NULL;
    q->front = q->rear = NULL;
    return q;
}

void enqueue(TeamQueue *head, Match game)
{
    NodeQueue *new_Node = NewNodeQueue(game);
    if (head->rear == NULL)
    {
        head->rear = new_Node;
    }
    else
    {
        (head->rear)->next = new_Node;
        head->rear = new_Node;
    }
    if (head->front == NULL)
    {
        head->front = head->rear;
    }
}

Match deQueue(TeamQueue *q)
{
    NodeQueue *aux;
    Match game;
    aux = q->front;
    game = aux->game;
    q->front = q->front->next;
    free(aux);
    return game;
}
