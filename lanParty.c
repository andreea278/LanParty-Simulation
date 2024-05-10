
#include "taskFunctions.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    TeamName *teams = NULL;
    fp = openFile(argv[1]);
    verifyOpeningFile(fp);
    int *tasks = Readtasks(fp);
    // if (tasks[0] == 1)
    // {
    //     addTeams(argv[2], &teams);
    //     if (tasks[1] == 1)
    //     {

    //         task2EliminateTeam(&teams, number_teams(argv[2]));
    //         FILE *outputfile = writeTeamList(argv[3], teams);
    //     }
    //     else
    //     {
    //         FILE *outputfile = writeTeamList(argv[3], teams);
    //     }
    // }
    Match *games;
    addTeams(argv[2], &teams);
    task2EliminateTeam(&teams, number_teams(argv[2]));
    FILE *outputfile = writeTeamList(argv[3], teams);
    // TeamQueue *t;
    // t = createQueue();
    // createQueueTeams(&t, teams, nTeamsEliminated(number_teams(argv[2])));
    // TeamName *stackWinners, *stacklossers;
    // winnersVSlossers(t, &stackWinners, &stacklossers);
    addMatch(argv[2], nTeamsEliminated(number_teams(argv[2])), teams);
    // while (stackWinners)
    // {
    //     printf("%s - %.02f\n", stackWinners->team.teamName, stackWinners->team.scoreTeam);
    //     stackWinners = stackWinners->next;
    // }
    // addMatch(argv[3], nTeamsEliminated(number_teams(argv[2])) / 2, teams);
    // for (int i = 0; i < nTeamsEliminated(number_teams(argv[2])) / 2; i++)
    // {
    //     printf("%s   -   %s\n", games[i].team1.teamName, games[i].team2.teamName);
    // }
    // FILE *outputfile = writeTeamList(argv[3], teams);
    free(tasks);
    // freeGames(&games, nTeamsEliminated(number_teams(argv[2])) / 2);

    return 0;
}