#include "BTS.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 100
#define NUMBER_TASKS 5

FILE *openFile(char *);
Team *FileInfo(char *);
int number_teams(char *);
void addTeams(char *, TeamName **);
FILE *writeTeamList(char *InfoFile, char *nameFile);

void verifyOpeningFile(FILE *);
int nTeamsEliminated(int);
float minScore(TeamName *);
FILE *task2EliminateTeam(char *InfoFile, char *FileOutput, TeamName **teamlist, int nr_teams);
int *Readtasks(FILE *);
int sumTasks(int *);
float score(Team);
void addGames(Match **, TeamName *, int);
void createQueueTeams(TeamQueue **, TeamName *, int);
FILE *addMatch(char *inputFile, char *outputFile, int nr_matches, TeamName **WinnersList, TeamName *);
void winnersVSlossers(FILE *, TeamQueue *, TeamName **, TeamName **, TeamName **, int *);
void *AddMatch(char *inputFile, char *outputFile, int nr_matches, TeamName **WinnersList, TeamName *);
void task4BTS(char *outputfile, char *inputfile);