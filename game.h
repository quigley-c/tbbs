#ifndef game
#define game

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct enemy{char name[20]; int maxhp; int hp; int strength; int hands; int heals;};
struct player{char name[20]; int maxhp; int hp; int strength; int hands; int heals;};

int dogPhase(struct enemy*);

void enemyPhase(struct player*, struct enemy*);
void genPlayer(struct player*);
void getEnemy(struct enemy*);
void getPrompt(char**, struct player);
void getScene(char**);
void play();
void playerPhase(int, struct player*, struct enemy*);
void printStats(struct player);

#endif
