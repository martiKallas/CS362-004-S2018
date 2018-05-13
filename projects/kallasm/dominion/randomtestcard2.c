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
	printf("#################### Begin Test Village ####################\n");
	//for a bunch of times
	for(i = 0; i < MAX_RUNS; i++){
		strcpy(pass, " ");
		strcpy(fail, " ");
		//pick a seed
		seed = rand();
		//randomize state
		memset(g, 0, sizeof(struct gameState));
		randomizeGameState(g, seed);
		//village card in hand
		numPlayers = gs.numPlayers;
		player = gs.whoseTurn;
		handPos = gs.handCount[player] - 1;
		if (handPos < 0){
			handPos = 0;
			gs.handCount[player] = 1;
		}
		gs.hand[player][handPos] = village;
		//save state
		save = gs;
		//playvillage
		cardEffect(village, 0, 0, 0, g, handPos, NULL);
		//Confirm card count is the same:
		// + 1 for played card
		totalG = gs.handCount[player] + gs.deckCount[player] + gs.discardCount[player] + gs.playedCardCount;
		totalS = save.handCount[player] + save.deckCount[player] + save.discardCount[player] + save.playedCardCount;
		if (totalG == totalS){
			strcat(pass, "Total card count, ");
		}
		else strcat(fail, "Total card count, ");
		//Confirm hand has same number of cards: -1 village +1 from deck
		if ((gs.handCount[player] - save.handCount[player]) == 0) strcat(pass, "Hand count, ");
		else strcat(fail, "Hand count, ");
		//Confirm deck count -1
		if (save.deckCount[player] >= 1){
			if ((gs.deckCount[player] - save.deckCount[player]) == -1) strcat(pass, "Deck count, ");
			else strcat(fail, "Deck count, ");
		}
		//had to shuffle discard into deck
		else{
			int count = save.deckCount[player] + save.discardCount[player];
			if (gs.deckCount[player] == (count-1)) strcat(pass, "Deck count, ");
			else strcat(fail, "Deck count, ");
		}
		// check if top deck card in hand
		int j;
		int* countArr = NULL;
		countArr = calloc(treasure_map+1, sizeof(int));
		cardInHandChange(g, &save, player, countArr, treasure_map+1, -1);
		totalS = save.deckCount[player];
		int topDeck = -1;
		int success = 1;
		if (totalS >= 1){
			//get top card in save state
			topDeck = save.deck[player][totalS-1];
			if(topDeck != village){
				if(countArr[topDeck] != 1) success = 0;
			}	
			else{
				//use > in case village wasn't removed
				if(countArr[topDeck] >= 0) success = 0;
			}
		}
		if (success) strcat(pass, "Top deck in hand, ");
		else strcat(fail, "Top deck in hand, ");
		// check village was removed from hand
		if (topDeck != village){
			if(countArr[village] == -1) strcat(pass, "Village removed from hand, ");
			else strcat(fail, "Village removed from hand, ");
		}
		else{
			if(countArr[village] == 0) strcat(pass, "Village removed from hand, ");
			else strcat(fail, "Village removed from hand, ");
		}
		
		// check if extra village in playedCards
		free(countArr);
		countArr = NULL;
		countArr = calloc(treasure_map+1, sizeof(int));
		cardInPlayedChange(g, &save, countArr, treasure_map+1, -1);
		if(countArr[village] == 1) strcat(pass, "Village in played, ");
		else strcat(fail, "Village in played, ");

		// Check if two extra actions
		if ((gs.numActions - save.numActions) == 2) strcat(pass, "Plus 2 actions, ");
		else strcat(fail, "Plus 2 actions, ");
		
		//Confirm no other player attributes have changes:
		int * plyrAttr = calloc(PLAYER_ATTR_NUM, sizeof(int));
		int result = otherPlayersChanged(g, &save, plyrAttr, player, numPlayers, PRINT);
		if (result) strcat(fail, "All other player's states unchanged ");
		else strcat(pass, "All other player's states unchanged ");
		printf("# Run %d. Seed %d. Pass: %s. Fail: %s\n", i, seed, pass, fail);
	}
		
	return 0;
}
