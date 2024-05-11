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
        teamName[strlen(teamName) - 2] = '\0';
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
        freeTeam(teams[i]);
    }
    free(teams);
}

FILE *writeTeamList(char *nameFile, TeamName *teams)
{
    FILE *fp = fopen(nameFile, "w");
    verifyOpeningFile(fp);
    while (teams)
    {
        fprintf(fp, "%s\n", teams->team.teamName);
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

void addGames(Match **game, TeamName *teamList, int nr_matches)
{
    int i = 0;
    *game = (Match *)malloc(sizeof(Match) * (nr_matches / 2));
    while (teamList && i < nr_matches / 2)
    {
        (*game)[i].team1 = teamList->team;
        teamList = teamList->next;
        (*game)[i].team2 = teamList->team;
        teamList = teamList->next;
        i++;
    }
}

void createQueueTeams(TeamQueue **teamQueue, TeamName *teamList, int nr_matches)
{
    Match *games;
    addGames(&games, teamList, nr_matches);
    for (int i = 0; i < nr_matches / 2; i++)
    {
        enqueue(*teamQueue, games[i]);
    }
    // freeGames(&games, nr_matches);
}

void winnersVSlossers(FILE *fileInfo, TeamQueue *teamQueue, TeamName **stackWinner, TeamName **stackLosser, TeamName **topBest8, int *foundTop8)
{
    int nr_teamsTop = 0;
    *foundTop8 = 1;
    while (teamQueue->front)
    {
        Match game = deQueue(teamQueue);
        Team firstTeam = game.team1, secondTeam = game.team2;
        fprintf(fileInfo, "%-33s - %-33s\n", firstTeam.teamName, secondTeam.teamName);
        if (firstTeam.scoreTeam > secondTeam.scoreTeam)
        {
            firstTeam.scoreTeam += 1;
            push(stackWinner, firstTeam);
            if (*foundTop8)
            {
                addAtBeggining(topBest8, firstTeam);
                nr_teamsTop++;
            }
            push(stackLosser, secondTeam);
        }
        else
        {
            secondTeam.scoreTeam += 1;
            push(stackLosser, firstTeam);
            if (*foundTop8)
            {
                addAtBeggining(topBest8, secondTeam);
                nr_teamsTop++;
            }
            push(stackWinner, secondTeam);
        }
    }
    if (nr_teamsTop == 8 && *foundTop8)
    {
        *foundTop8 = 0;
    }
    else
    {
        deleleteStackLossers(topBest8);
    }
    deleleteStackLossers(stackLosser);
    fprintf(fileInfo, "\n");
}
FILE *addMatch(char *nameFile, int nr_matches, TeamName *teamslist, TeamName **WinnersList)
{
    FILE *fp = fopen(nameFile, "a");
    verifyOpeningFile(fp);
    TeamQueue **Q = (TeamQueue **)malloc(sizeof(TeamQueue *) * (nr_matches / 2));
    for (int i = 0; i < nr_matches / 2; i++)
    {
        Q[i] = createQueue();
        if (Q[i] == NULL)
        {
            return NULL;
        }
    }
    createQueueTeams(Q, teamslist, nr_matches);
    TeamName *stackwinners = NULL, *stacklossers = NULL, *topBest8 = NULL;
    int existingQueue = 1, foundTop8, i; // verifing if there still are games to play
    for (i = 0; i < nr_matches / 2 && existingQueue; i++)
    {
        fprintf(fp, "--- ROUND NO:%d\n", i + 1);
        winnersVSlossers(fp, Q[i], &stackwinners, &stacklossers, &topBest8, &foundTop8);
        fprintf(fp, "WINNERS OF ROUND NO:%d\n", i + 1);
        printWinnerStack(fp, stackwinners, nr_matches);
        int indexQueue = i + 1, x = 1; // x power of 2 for searching how many games will be in the new Queue
        while (indexQueue)
        {
            x *= 2;
            indexQueue--;
        }
        createQueueTeams(&Q[i + 1], stackwinners, nr_matches / x);
        int nr = nr_matches / 2;
        // golim din stiva echipele folosite in noua coada
        while (stackwinners && nr)
        {
            Team team = pop(&stackwinners);
            nr--;
        }
        if (Q[i + 1]->front == NULL)
        {
            existingQueue = 0;
        }
        if (!foundTop8)
        {
            while (topBest8)
            {
                addAtBeggining(WinnersList, topBest8->team);
                topBest8 = topBest8->next;
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return fp;
}
