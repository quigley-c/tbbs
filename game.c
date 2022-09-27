#include "game.h"

int main()	{
	play();
	return 0;
}

void play()	{
	int usrin;
	int pphase = 1;
	char *prompt = (char*)malloc(sizeof(char)*256);
	char *scene = (char*)malloc(sizeof(char)*256);

	// generate player initial values
	struct player p;
	genPlayer(&p);

	struct enemy e;
	getEnemy(&e);

	// print player stats
	system("clear");
	printStats(p);

	// main loop
	while(true)	{
		// break condition
		if(p.hp < 1)	{
			free(prompt);
			free(scene);
			printf("You have been killed.\n");
			printf("GAME OVER\n");
			printf("[0. Exit] [1. Restart]\n");
			scanf("%d", &usrin);
			if(usrin == 1)
				play();
			break;
		}

		if(e.hp < 1)	{
			// The enemy died
			printf("%s has been defeated!\n", e.name);
			getEnemy(&e);
			printf("A new enemy approaches!\n");
		}

		// determine whose turn it is
		if(pphase)	{
			// display the scenario
			getScene(&scene);
			printf("%s", scene);

			// display prompt
			getPrompt(&prompt, p);
			printf("%s", prompt);

			// get terminal input
			scanf("%d", &usrin);
			system("clear");

			// parse user command
			playerPhase(usrin, &p, &e);
			pphase = 0;
		} else	{
			// enemy turn
			enemyPhase(&p, &e);
			pphase = 1;
		}

	}
}

void playerPhase(int input, struct player *p, struct enemy *e)	{
	if(input == 0)	{
		// user wants to attack
		printf("%s strikes!\n%s suffers %d damage.\n", p->name, e->name, p->strength);
		e->hp -= p->strength;
	} else if(input == 1)	{
		// user wants to heal.
		if(p->hp < p->maxhp)	{
			printf("%s bandages a wound.\n%s recovers 1hp\n", p->name, p->name);
			p->hp += 1;
		}
	}
}

void enemyPhase(struct player *p, struct enemy *e)	{
	// The enemy deals some damage to the player.
	int dmg = dogPhase(e);
	printf("%s suffers %d damage.\n", p->name, dmg);
	p->hp -= dmg;
}

int dogPhase(struct enemy *e)	{
	// function denoting dog abilities
	srand((time(NULL)));
	int choice = rand()%10;

	if(choice >= 0 && choice < 5)	{
		printf("%s makes a savage lunge!\n", e->name);
		return e->strength;
	} else if(choice == 9)	{
		printf("%s licks their wounds.\n", e->name);
		if (e->hp < e->maxhp)	{
			printf("%s recovers 1hp\n", e->name);
			e->hp += 1;
		}
		return 0;
	}

	printf("%s lets out a ferocious \"WOOF\"!\n", e->name);
	return 0;

}

void printStats(struct player p)	{
	printf("name: %s\nhp: %d/%d\nstr: %d\nhands: %d\n\n",
		p.name,
		p.hp,
		p.maxhp,
		p.strength,
		p.hands
	);
}

void genPlayer(struct player *p)	{
	char usrin[20];

	// prompt player for name
	printf("enter name: \n");
	scanf("%s", &usrin);

	//player default inits
	struct player u = {"", 10, 10, 5, 0, 0};
	strcpy(u.name, usrin);
	*p = u;
}

void getEnemy(struct enemy *e)	{
	//enemy default inits
	struct enemy u = {"Whiskey", 15, 15, 2, 0, 0};
	*e = u;
}

void getScene(char **scene)	{
	strcpy(*scene, "An Enemy Approaches: Dog - Whiskey\n");
}

void getPrompt(char **prompt, struct player p)	{
	sprintf(*prompt, "hp: %d/%d - heals: %d\n[0. Attack] [1. Heal]: ", p.hp, p.maxhp, p.heals);
}
