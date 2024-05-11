#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct player
{
    char *firstName;
    char *secondName;
    int points;
} Player;

typedef struct team
{
    int nr_players;
    char *teamName;
    Player *players;
    float scoreTeam;
} Team;

typedef struct node
{
    Team team;
    struct node *next;
} TeamName;

TeamName *newNode(Team);
void addAtBeggining(TeamName **, Team);
void addAtEnd(TeamName **, Team);
void freeNode(TeamName *);
void deleteTeam(TeamName **, float);
void freeTeam(Team team);
void printTeam(FILE *fp, TeamName *teamlist);