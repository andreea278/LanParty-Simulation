#include "taskFunctions.h"

void verifyOpeningFile(FILE *fp)
{
    if (fp == NULL)
    {
        fprintf(stderr, "Error: hereeee \n");
        fclose(fp);
        return;
    }
}

int *Readtasks(FILE *fp)
{
    int *tasks = (int *)malloc(sizeof(int) * NUMBER_TASKS);
    for (int i = 0; i < NUMBER_TASKS; i++)
    {
        fscanf(fp, "%d", &tasks[i]);
    }
    fclose(fp);
    return tasks;
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

void freeTeam(Team *team)
{
    free(team->teamName);
    for (int i = 0; i < team->nr_players; i++)
    {
        free(team->players[i].firstName);
        free(team->players[i].secondName);
    }
    free(team->players);
}

float score(Team team)
{
    int score = 0;
    for (int i = 0; i < team.nr_players; i++)
    {
        score += team.players[i].points;
    }
    float m_score = (float)score / team.nr_players;
    return m_score;
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
            fscanf(fp, "%s", buffer);
            teams[i].players[j].firstName = (char *)malloc(strlen(buffer) + 1);
            strcpy(teams[i].players[j].firstName, buffer);
            fscanf(fp, "%s", buffer);
            teams[i].players[j].secondName = (char *)malloc(strlen(buffer) + 1);
            strcpy(teams[i].players[j].secondName, buffer);
            fscanf(fp, "%d", &teams[i].players[j].points);
        }
        teams[i].scoreTeam = score(teams[i]);
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
        freeTeam(&teams[i]);
    }
    free(teams);
}

FILE *writeTeamList(char *nameFile, TeamName *teams)
{
    FILE *fp = fopen(nameFile, "w");
    verifyOpeningFile(fp);
    while (teams)
    {
        fputs(teams->team.teamName, fp);
        teams = teams->next;
    }
    fclose(fp);
    return fp;
}

/*task 2*/
int nTeamsEliminated(int nr_teams)
{
    int n = 2;
    while (n < nr_teams)
    {
        n = n * 2;
    }
    return n / 2;
}

float minScore(TeamName *team)
{
    float min_score = team->team.scoreTeam;
    while (team)
    {
        if (team->team.scoreTeam < min_score)
            min_score = team->team.scoreTeam;
        team = team->next;
    }
    return min_score;
}

void task2EliminateTeam(TeamName **teamlist, int nr_teams)
{
    int i = nTeamsEliminated(nr_teams);
    while (i < nr_teams)
    {
        TeamName *temp = *teamlist;
        float score = minScore(*teamlist);
        while (temp)
        {
            if (temp->team.scoreTeam == score)
            {
                deleteTeam(teamlist, score);
                break;
            }
            temp = temp->next;
        }
        i++;
    }
}
