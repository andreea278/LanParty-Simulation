#include "stacks.h"

typedef struct match
{
    Team team1, team2;
} Match;

typedef struct nodeQueue
{
    Match game;
    struct nodeQueue *next;
} NodeQueue;

typedef struct teamQueue
{
    NodeQueue *front, *rear;
} TeamQueue;

Team allocMemoryTeam(Team team);
NodeQueue *NewNodeQueue(Match game);
void enqueue(TeamQueue *, Match);
TeamQueue *createQueue();
Match deQueue(TeamQueue *);
int IsQueueEmpty(TeamQueue *);
void freeNodeQueue(NodeQueue *node);
void deleteQueue(TeamQueue *queue);
void freeGames(Match *game, int nr_matches);