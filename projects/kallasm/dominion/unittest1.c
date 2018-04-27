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

/* Contains all checks to make sure shuffle performed correctly.
 * 	Checks all states not related to curPlayer's deck are unchanged
 * 	Checks curPlayer's deck contains the same type and number of cards
 * 	Checks if order is different - does not fail if order is same - just alerts
 *
 * Returns 1 if shuffle appears to have succeeded. 0 if shuffle failed any tests.
 *
 * cardTypes indicates max card value for the deckCardsChanged function
 */
int checkShuffle(struct gameState *cur, struct gameState *old, int curPlayer, int cardTypes){
	//Check all other players states have not changed
	int check = 0;
	int fail = 0;
	int success = 1;
	int playerAttrs[PLAYER_ATTR_NUM] = {0};
	int player;
	int i;
	for (i = 1; i < NUM_PLAYERS; i++){
		player = (i + curPlayer)%(NUM_PLAYERS);	
		check = checkPlayerChanged(cur, old, playerAttrs, player, PRINT);
		if (check) fail = 1;
	}
	if (!fail) printf("  PASS: All other player's states are unchanged.\n");
	else success = 0;
	fail = 0;

	//Check other cur states:
	int stateAttrs[STATE_ATTR_NUM] = {0};
	check = otherStateChanged(cur, old, stateAttrs, PRINT);
	if(!check) printf("  PASS: No state changes to other general state attributes. \n");
	else success = 0;

	//Check current player's discard and hand are unchanged:
	memset(stateAttrs, 0, sizeof(playerAttrs));
	playerAttrs[pa_deck] = 1; //ignore deck changes
	check = checkPlayerChanged(cur, old, playerAttrs, curPlayer, PRINT);
	if (!check) printf("  PASS: All states of current player that are not deck are unchanged. \n");	
	else success = 0;
	
	//Check that deck contains each card 0 to MAX_DECK-1
	int *countArr = calloc(cardTypes, sizeof(int));
	check = deckCardsChanged(cur, old, curPlayer, cardTypes, countArr);
	if (!check) printf("  PASS: Number of each card in deck is identical in deck after shuffle. \n");
	else{
		printf(" FAIL: Found error for card value %d. Difference: %d. \n", check, countArr[check]);
		success = 0;
	}

	//Check that decks are not in the same order
	int max = cur->deckCount[curPlayer];
	int diff = 0;
	int overlap = 0;
	if (max != old->deckCount[curPlayer]){
		printf("  FAIL: Did not check deck order. Deck counts were different.\n");
		success = 0;	
	}
	for (i=0; i < max; i++){
		if (cur->deck[curPlayer][i] == old->deck[curPlayer][i]) overlap++;
		else diff++;
	}
	if (diff) printf("  PASS: %d deck positions were different after shuffle of %d positions.\n", diff, max); 
	else printf("  ALERT: No deck positions were different after shuffle of %d positions. \n", max);
	
	free(countArr);
	return success;
}

int main(){
	//Initialize needed game atate
	int kCards[10] = {adventurer, gardens, council_room, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState g; //defined in dominion.h
	struct gameState * game = &g;
	memset(game, 0, sizeof(struct gameState));
	int ok = 0;
	
	//NUM_PLAYERS, kingdomCards, randomSeed, gameState *
	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	int currentPlayer = whoseTurn(game);
	printf("\n\n######### Beginning Test of shuffle()############\n");

	printf("\n# Fill deck with MAX_DECK unique cards\n");
	//Fill deck with cards 0 to MAX_DECK-1
	int i;
	g.deckCount[currentPlayer] = 0;
	for (i = 0; i < MAX_DECK; i++){
		g.deck[currentPlayer][i] = i;
		g.deckCount[currentPlayer]++;	
	}
	struct gameState saveState = g;
	
	//shuffle
	shuffle(currentPlayer, game);
	ok = checkShuffle(game, &saveState, currentPlayer, MAX_DECK);
	testAssert(ok, "Fill deck with MAX_DECK unique cards");
	return 0;
}
