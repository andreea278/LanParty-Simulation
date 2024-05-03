#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

FILE *openFile(char *);
Team *FileInfo(char *);
int number_teams(char *);
void addTeams(char *, TeamName **);
FILE *writeTeamList(char *, TeamName *);
void freeTeam(Team);
void verifyOpeningFile(FILE*);