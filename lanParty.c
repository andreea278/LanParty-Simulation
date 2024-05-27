
#include "taskFunctions.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    TeamName *teams = NULL;
    fp = openFile(argv[1]);
    verifyOpeningFile(fp);
    int *tasks = Readtasks(fp);
    // printf("%d\n", sumTasks(tasks));
    switch (sumTasks(tasks))
    {
    case 1:
        FILE *outputfile = writeTeamList(argv[2], argv[3]);
        break;
    case 2:
        outputfile = task2EliminateTeam(argv[2], argv[3], &teams, number_teams(argv[2]));
        freeList(&teams);
        break;
    case 3:
        outputfile = task2EliminateTeam(argv[2], argv[3], &teams, number_teams(argv[2]));
        TeamName *winnerList = NULL;
        outputfile = addMatch(argv[2], argv[3], nTeamsEliminated(number_teams(argv[2])), &winnerList, teams);
        freeList(&winnerList);
        break;

    case 4:
        NodeBTS *topWinners;
        task4BTS(argv[3], argv[2], &topWinners);
        break;
    case 5:
        task5AVL(argv[3], argv[2]);
    }
    free(tasks);

    return 0;
}