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
	printf("#################### Begin Test Smithy ####################\n");
	//for a bunch of times
	for(i = 0; i < MAX_RUNS; i++){
		strcpy(pass, " ");
		strcpy(fail, " ");
		//pick a seed
		seed = rand();
		//randomize state
		memset(g, 0, sizeof(struct gameState));
		randomizeGameState(g, seed);
		//smithy card in hand
		numPlayers = gs.numPlayers;
		player = gs.whoseTurn;
		handPos = gs.handCount[player] - 1;
		if (handPos < 0){
			handPos = 0;
			gs.handCount[player] = 1;
		}
		gs.hand[player][handPos] = smithy;
		//save state
		save = gs;
		//playsmithy
		cardEffect(smithy, 0, 0, 0, g, handPos, NULL);
		//Confirm card count is the same:
        totalG = gs.handCount[player] + gs.deckCount[player] + gs.discardCount[player] + gs.playedCardCount;
        totalS = save.handCount[player] + save.deckCount[player] + save.discardCount[player] + save.playedCardCount;
		if (totalG == totalS){
			strcat(pass, "Total card count, ");
		}
		else strcat(fail, "Total card count, ");
		//Confirm hand has 2 extra card - -1 smithy +3 cards
		if ((gs.handCount[player] - save.handCount[player]) == 2) strcat(pass, "Hand count, ");
		else strcat(fail, "Hand count, ");
		//Confirm deck count -3
		if (save.deckCount[player] >= 3){
			if ((gs.deckCount[player] - save.deckCount[player]) == -3) strcat(pass, "Deck count, ");
			else strcat(fail, "Deck count, ");
		}
		//must shuffle discard to deck
		else{
			int count = save.deckCount[player] + save.discardCount[player];
			if (gs.deckCount[player] == (count-3)) strcat(pass, "Deck count, ");
			else strcat(fail, "Deck count, ");
		}
		// top 3 deck are in hand
		int j;
		int* countArr = NULL;
		countArr = calloc(treasure_map+1, sizeof(int));
		cardInHandChange(g, &save, player, countArr, treasure_map+1, -1);
		totalS = save.deckCount[player];
		int* topDeck = NULL;
		if (totalS >= 3){
			int success = 1;
			topDeck = calloc(treasure_map+1, sizeof(int));
			//count cards on top of deck from save
			for (j = 1; j < 4; j++){
				int card = save.deck[player][totalS-j];
				topDeck[card]++;
			}
			for (j = 0; j < treasure_map+1; j++){
				if (topDeck[j]){
					//see if top cards from save are now in hand
					if(j != smithy){
						if(countArr[j] == topDeck[j]) continue;
						else success = 0;
					}	
				}
			}
			if (success) strcat(pass, "Top deck cards to hand, ");
			else strcat(fail, "Top deck cards to hand, ");
		}
		// check smithy was removed from hand
		if (topDeck != NULL){
			if(countArr[smithy] == topDeck[smithy] - 1) strcat(pass, "Smithy removed from hand, ");
			else strcat(fail, "Smithy removed from hand, ");
		}
		else{
			if(countArr[smithy] == -1) strcat(pass, "Smithy removed from hand, ");
			else strcat(fail, "Smithy removed from hand, ");
		}
		free(topDeck);
		topDeck = NULL;
		
		// check if extra smithy in playedCards
		free(countArr);
		countArr = NULL;
		countArr = calloc(treasure_map+1, sizeof(int));
		cardInPlayedChange(g, &save, countArr, treasure_map+1, -1);
		if(countArr[smithy] == 1) strcat(pass, "Smithy in played, ");
		else strcat(fail, "Smithy in played, ");
		
		//Confirm no other player attributes have changes:
		int * plyrAttr = calloc(PLAYER_ATTR_NUM, sizeof(int));
		int result = otherPlayersChanged(g, &save, plyrAttr, player, numPlayers, PRINT);
		if (result) strcat(fail, "All other player's states unchanged ");
		else strcat(pass, "All other player's states unchanged ");
		printf("# Run %d. Seed %d. Pass: %s. Fail: %s\n", i, seed, pass, fail);

	}
		
	return 0;
}
