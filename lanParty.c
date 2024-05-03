
#include "taskFunctions.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    TeamName *teams = NULL;
    // openFile(argv[1]);
    addTeams(argv[2], &teams);
    FILE *outputfile = writeTeamList(argv[3], teams);
}