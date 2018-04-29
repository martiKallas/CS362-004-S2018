#include <stdlib.h>
#include <string.h>
#include "testHelper.h"
#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include <stdio.h>

#define SEED 10
#define PRINT 1
#define NO_PRINT 0
#define NUM_PLAYERS 4

int main(){
	//setup game - player has only copper and estate cards
	int kCards[10] = {adventurer, gardens, council_room, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState g; //defined in dominion.h
	struct gameState * game = &g;
	memset(game, 0, sizeof(struct gameState));
	int ok = 0;
	int passed = 1;
	int count = 0;
	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	int currentPlayer = whoseTurn(game);
	printf("\n\n\n\n######### Beginning Test of sea hag card ############\n");

	//adjust all other player's top deck to be feast
	int i;
	int dc;
	for (i = 1; i < NUM_PLAYERS; i++){
		dc = g.deckCount[i] - 1;
		g.deck[i][dc] = feast;		
	}
	
	//add village to handPos of current player
	dc = g.handCount[currentPlayer]-1;
	g.hand[currentPlayer][dc] = sea_hag;
	//save state
	struct gameState saveState = g;
	//play village
	cardEffect(sea_hag, 0, 0, 0, game, dc, NULL);

	//check sea_ahg passes all basics except for handCount
	int* countArr = calloc(PC_TEST_NUM, sizeof(int));
	ok = cardPlayedBasics(game, &saveState, sea_hag, countArr, treasure_map+1, PRINT);
	if(ok) passed = 0;

	//check deck count is same for each player -1 top card +1 curse
	for (i = 1; i < NUM_PLAYERS; i++){
		count = g.deckCount[i] - saveState.deckCount[i];
		if (count != 1){
			printf("  FAIL: Player %d deck count change: %d.\n", i, count);
			passed = 0;
		}
		else printf("  PASS: Player %d deck count changed by %d.\n", i, count);
	}

	//check discard count ++
	for (i = 1; i < NUM_PLAYERS; i++){
		count = g.discardCount[i] - saveState.discardCount[i];
		if (count != 1){
			printf("  FAIL: Player %d discard count change: %d.\n", i, count);
			passed = 0;
		}
		else printf("  PASS: Player %d discard count changed by %d.\n", i, count);
	}

	//check each other player has feast on top of discard pile
	for (i = 1; i < NUM_PLAYERS; i++){
		dc = g.discardCount[i]-1; 
		count = g.discard[i][dc];
		if (count != feast){
			printf("  FAIL: Player %d top discard is %d.\n", i, count);
			passed = 0;
		}
		else printf("  PASS: Hand count changed by %d.\n", count);
	}

	//check each other player has curse on top of deck 
	for (i = 1; i < NUM_PLAYERS; i++){
		dc = g.deckCount[i] - 1;
		count = g.deck[i][dc];
		if (count != curse){
			printf("  FAIL: Player %d top deck is %d.\n", i, count);
			passed = 0;
		}
		else printf("  PASS: Player %d top deck is %d.\n", i, count);
	}

	//check other players hands haven't changed
	int* plyrAttr = calloc(PLAYER_ATTR_NUM, sizeof(int));
	plyrAttr[pa_deck] = 1;
	plyrAttr[pa_deckCount] = 1;
	plyrAttr[pa_discard] = 1;
	plyrAttr[pa_discardCount] = 1;
	ok = otherPlayersChanged(game, &saveState, plyrAttr, currentPlayer, NUM_PLAYERS, PRINT);
	if (ok) passed = 0;

	if (passed) printf("\n ########## PASSED Test of sea hag ##########\n");
	else printf("\n ########## FAILED Test of sea hag ##########\n");

	free(plyrAttr);
	free(countArr);
	return 0;
}
