
#include "taskFunctions.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    TeamName *teams = NULL;
    fp = openFile(argv[1]);
    verifyOpeningFile(fp);
    int *tasks = Readtasks(fp);
    if (tasks[0] == 1)
    {
        addTeams(argv[2], &teams);
        if (tasks[1] == 1)
        {

            task2EliminateTeam(&teams, number_teams(argv[2]));
            FILE *outputfile = writeTeamList(argv[3], teams);
        }
        else
        {
            FILE *outputfile = writeTeamList(argv[3], teams);
        }
    }

    return 0;
}