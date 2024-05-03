#include "taskFunctions.h"
#define MAX_LENGTH 50

void verifyOpeningFile(FILE *fp)
{
    if (fp == NULL)
    {
        fprintf(stderr, "Error: hereeee \n");
        fclose(fp);
        return;
    }
}

FILE *openFile(char *nameFile)
{
    FILE *fp;
    fp = fopen(nameFile, "r");
    verifyOpeningFile(fp);
    return fp;
}

int number_teams(char *nameFile)
{
    FILE *fp = openFile(nameFile);
    verifyOpeningFile(fp);
    int nr_teams;
    fscanf(fp, "%d", &nr_teams);
    fclose(fp);
    return nr_teams;
}
void freeTeam(Team team)
{
    free(team.teamName);
    for (int i = 0; i < team.nr_players; i++)
    {
        free(team.players[i].firstName);
        free(team.players[i].secondName);
    }
    free(team.players);
}

Team *FileInfo(char *nameFile)
{
    FILE *fp = openFile(nameFile);
    int nr_teams;
    fscanf(fp, "%d", &nr_teams);
    char buffer[MAX_LENGTH], teamName[MAX_LENGTH];
    Team *teams = (Team *)malloc(sizeof(Team) * nr_teams);
    for (int i = 0; i < nr_teams; i++)
    {
        char ch;
        fscanf(fp, "%d%c", &teams[i].nr_players, &ch);
        fgets(teamName, MAX_LENGTH, fp);
        teams[i].teamName = (char *)malloc(strlen(teamName) + 1);
        strcpy(teams[i].teamName, teamName);
        teams[i].players = (Player *)malloc(sizeof(Player) * teams[i].nr_players);
        if (teams[i].players == NULL)
        {
            return NULL;
        }
        for (int j = 0; j < teams[i].nr_players; j++)
        {
            fscanf(fp, "%s%c", buffer, &ch);
            teams[i].players[j].firstName = (char *)malloc(strlen(buffer) + 1);
            strcpy(teams[i].players[j].firstName, buffer);
            fscanf(fp, "%s%c", buffer, &ch);
            teams[i].players[j].secondName = (char *)malloc(strlen(buffer) + 1);
            strcpy(teams[i].players[j].secondName, buffer);
            fscanf(fp, "%d", &teams[i].players[j].points);
        }
    }
    fclose(fp);
    return teams;
}

void addTeams(char *nameFile, TeamName **teamList)
{
    Team *teams = NULL;
    *teamList = NULL;
    int nr_teams = number_teams(nameFile);
    teams = FileInfo(nameFile);
    for (int i = 0; i < nr_teams; i++)
    {
        addAtBeggining(teamList, teams[i]);
    }
    for (int i = 0; i < nr_teams; i++)
    {
        freeTeam(teams[i]);
    }
    free(teams);
}

FILE *writeTeamList(char *nameFile, TeamName *teams)
{
    FILE *fp = fopen(nameFile, "w");
    verifyOpeningFile(fp);
    TeamName *aux = NULL;
    while (teams)
    {
        fputs(teams->team.teamName, fp);
        aux = teams->next;
        freeNode(teams);
        teams = aux;
    }
    fclose(fp);
    return fp;
}
