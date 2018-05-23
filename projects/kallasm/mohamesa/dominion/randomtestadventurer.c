#include "testHelper.h"
#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define PRINT 0
#define MAX_RUNS 10000

int main(){
	srand(time(NULL));
	int i;
	int seed;
	int handPos = 0;
	int player = 0;
	int numPlayers = 0;
	struct gameState gs;
	struct gameState* g = &gs;
	struct gameState save;
	int totalG = 0;
	int totalS = 0;
	char pass[500];
	char fail[500];
	memset(pass, '\0', sizeof(pass));
	memset(fail, '\0', sizeof(fail));
	//for a bunch of times
	for(i = 0; i < MAX_RUNS; i++){
		strcpy(pass, " ");
		strcpy(fail, " ");
		//pick a seed
		seed = rand();
		//randomize state
		memset(g, 0, sizeof(struct gameState));
		randomizeGameState(g, seed);
		//setAdventurer card in hand
		numPlayers = gs.numPlayers;
		player = gs.whoseTurn;
		handPos = gs.handCount[player] - 1;
		if (handPos < 0){
			handPos = 0;
			gs.handCount[player] = 1;
		}
		gs.hand[player][handPos] = adventurer;
		//make sure discard contains two coppers to avoid infinite loop
		totalG = gs.discardCount[player];
		if (totalG < 2){
			gs.discardCount[player] = 2;
			if (gs.deckCount[player] >= MAX_DECK -2){
				gs.deckCount[player] = MAX_DECK - 3;	
			}
		}
		gs.discard[player][0] = copper;
		gs.discard[player][1] = copper;
		//save state
		save = gs;
		//playadventurer
		cardEffect(adventurer, 0, 0, 0, g, handPos, NULL);
		//Confirm card count is the same:
		totalG = gs.handCount[player] + gs.deckCount[player] + gs.discardCount[player] + gs.playedCardCount;
        totalS = save.handCount[player] + save.deckCount[player] + save.discardCount[player] + save.playedCardCount;
		if (totalG == totalS){
			strcat(pass, "Total card count, ");
		}
		else strcat(fail, "Total card count, ");
		//Confirm hand has 1 extra card - -1 adventurer +2 treasures
		if ((gs.handCount[player] - save.handCount[player]) == 1) strcat(pass, "Hand count, ");
		else strcat(fail, "Hand count, ");
		//Confirm hand has 2 extra treasures:
		totalG = countTreasures(g, player);
		totalS = countTreasures(&save, player);
		if ((totalG - totalS) == 2) strcat(pass, "Treasure count, ");
		else strcat(fail, "Treasure count, ");
		//Confirm no other player attributes have changes:
		int * plyrAttr = calloc(PLAYER_ATTR_NUM, sizeof(int));
		int result = otherPlayersChanged(g, &save, plyrAttr, player, numPlayers, PRINT);
		if (result) strcat(fail, "All other player's states unchanged ");
		else strcat(pass, "All other player's states unchanged ");
		printf("# Run %d. Seed %d. Pass: %s. Fail: %s\n", i, seed, pass, fail);

	}
		
	return 0;
}
