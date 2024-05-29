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

int sumTasks(int *tasks)
{
    int sum_task = 0;
    for (int i = 0; i < NUMBER_TASKS; i++)
    {
        sum_task += tasks[i];
    }
    return sum_task;
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
        freeTeam(&teams[i]);
    }
    free(teams);
}

FILE *writeTeamList(char *InfoFile, char *nameFile)
{
    TeamName *teams;
    addTeams(InfoFile, &teams);
    FILE *fp = fopen(nameFile, "w");
    verifyOpeningFile(fp);
    printTeam(fp, teams);
    freeList(&teams);
    fclose(fp);
    return fp;
}

/*task 2*/
int nTeamsEliminated(int nr_teams)
{
    int n = 2;
    while (n <= nr_teams)
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

FILE *task2EliminateTeam(char *InfoFile, char *FileOutput, TeamName **teamlist, int nr_teams)
{
    addTeams(InfoFile, teamlist);
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
    FILE *fp = fopen(FileOutput, "w");
    verifyOpeningFile(fp);
    printTeam(fp, *teamlist);
    fclose(fp);

    return fp;
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
    *teamQueue = createQueue();
    for (int i = 0; i < nr_matches / 2; i++)
    {
        enqueue(*teamQueue, games[i]);
    }
}

void winnersVSlosers(FILE *fileInfo, TeamQueue *teamQueue, TeamName **stackWinner, TeamName **stackLoser, TeamName **topBest8, int *foundTop8)
{
    int nr_teamsTop = 0;
    *foundTop8 = 1;
    while (teamQueue->front)
    {
        Match game = deQueue(teamQueue);
        Team firstTeam = game.team1, secondTeam = game.team2;
        if (secondTeam.teamName[strlen(secondTeam.teamName) - 1] == ' ')
        {
            secondTeam.teamName[strlen(secondTeam.teamName) - 1] = '\0';
        }
        fprintf(fileInfo, "%-32s - %32s\n", firstTeam.teamName, secondTeam.teamName);
        if (firstTeam.scoreTeam > secondTeam.scoreTeam)
        {
            firstTeam.scoreTeam += 1;
            push(stackWinner, firstTeam);
            if (*foundTop8)
            {
                addAtBeggining(topBest8, firstTeam);
                nr_teamsTop++;
            }
            push(stackLoser, secondTeam);
        }
        else
        {
            secondTeam.scoreTeam += 1;
            push(stackLoser, firstTeam);
            if (*foundTop8)
            {
                addAtBeggining(topBest8, secondTeam);
                nr_teamsTop++;
            }
            push(stackWinner, secondTeam);
        }
        freeTeam(&firstTeam);
        freeTeam(&secondTeam);
    }
    if (nr_teamsTop == 8 && *foundTop8)
    {
        *foundTop8 = 0;
    }
    else
    {
        freeList(topBest8);
    }
    deleleteStackLosers(stackLoser);
    fprintf(fileInfo, "\n");
}

FILE *addMatch(char *inputFile, char *outputFile, int nr_matches, TeamName **WinnersList, TeamName *teamslist)
{
    FILE *outFILE = fopen(outputFile, "a");
    verifyOpeningFile(outFILE);
    fprintf(outFILE, "\n");
    TeamQueue *Q = (TeamQueue *)malloc(sizeof(TeamQueue) * (nr_matches / 2));
    createQueueTeams(&Q, teamslist, nr_matches);
    TeamName *stackwinners = NULL, *stacklossers = NULL, *topBest8 = NULL;
    int existingQueue = 1, foundTop8, i = 0; // verifing if there still are games to play
    while (Q->front && i < nr_matches / 2 && existingQueue)
    {
        fprintf(outFILE, "--- ROUND NO:%d\n", i + 1);
        winnersVSlosers(outFILE, Q, &stackwinners, &stacklossers, &topBest8, &foundTop8);
        fprintf(outFILE, "WINNERS OF ROUND NO:%d\n", i + 1);
        int indexQueue = i + 1, x = 1; // x power of 2 for searching how many games will be in the new Queue
        while (indexQueue)
        {
            x *= 2;
            indexQueue--;
        }
        deleteQueue(Q);
        createQueueTeams(&Q, stackwinners, nr_matches / x);
        printWinnerStack(outFILE, stackwinners, nr_matches / x);
        i++;
        if (Q->front == NULL)
        {
            existingQueue = 0;
        }
        int nr = nr_matches / 2;
        deleleteStackLosers(&stackwinners);
        if (!foundTop8)
        {
            while (topBest8)
            {
                addAtBeggining(WinnersList, topBest8->team);
                topBest8 = topBest8->next;
            }
            freeList(&topBest8);
        }
        if (existingQueue)
            fprintf(outFILE, "\n");
    }
    deleteQueue(Q);
    deleleteStackLosers(&stackwinners);
    freeList(&teamslist);
    fclose(outFILE);
    return outFILE;
}

void task4BTS(char *outputfile, char *inputfile, NodeBTS **topWinners)
{
    TeamName *teams;
    FILE *outFile = task2EliminateTeam(inputfile, outputfile, &teams, number_teams(inputfile));
    TeamName *winnerList = NULL;
    outFile = addMatch(inputfile, outputfile, nTeamsEliminated(number_teams(inputfile)), &winnerList, teams);
    outFile = fopen(outputfile, "a");
    verifyOpeningFile(outFile);
    fprintf(outFile, "\nTOP 8 TEAMS:\n");
    *topWinners = NULL;
    while (winnerList)
    {
        *topWinners = insert(*topWinners, winnerList->team);
        winnerList = winnerList->next;
    }
    printBTS(outFile, *topWinners);
    fclose(outFile);
}

void task5AVL(char *outputfile, char *inputfile)
{
    NodeBTS *topWinners = NULL;
    task4BTS(outputfile, inputfile, &topWinners);
    FILE *outFile = fopen(outputfile, "a");
    verifyOpeningFile(outFile);
    fprintf(outFile, "\nTHE LEVEL 2 TEAMS ARE:\n");
    NodeBTS *AVL = NULL;
    addBTSinAVL(topWinners, &AVL);
    printInOrder(outFile, AVL);
    fclose(outFile);
}
