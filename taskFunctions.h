#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 100
#define NUMBER_TASKS 5

FILE *openFile(char *);
Team *FileInfo(char *);
int number_teams(char *);
void addTeams(char *, TeamName **);
FILE *writeTeamList(char *, TeamName *);

void verifyOpeningFile(FILE *);
int nTeamsEliminated(int);
float minScore(TeamName *);
void task2EliminateTeam(TeamName **, int);
int *Readtasks(FILE *);
float score(Team);
void addGames(Match **, TeamName *, int);
void createQueueTeams(TeamQueue **, TeamName *, int);
FILE *addMatch(char *, int, TeamName *, TeamName **);
void winnersVSlossers(FILE *, TeamQueue *, TeamName **, TeamName **, TeamName **, int *);