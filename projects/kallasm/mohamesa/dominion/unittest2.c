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
	//Initialize game state
	int kCards[10] = {adventurer, gardens, council_room, 
				village, minion, mine, cutpurse, 
				sea_hag, tribute, smithy};
	struct gameState g; //defined in dominion.h
	struct gameState * game = &g;
	memset(game, 0, sizeof(struct gameState));
	int ok = 0;
	int passed = 1;
	int success = 1;
	int playerAttrs[PLAYER_ATTR_NUM] = {0};
	int stateAttrs[STATE_ATTR_NUM] = {0};

	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	int currentPlayer = whoseTurn(game);
	printf("\n\n\n\n########## Beginning Test of buyCard() ##########\n");

	//Test Possible Purchase
	printf("\n# Set coins to 2 and buy Estate\n");
	g.coins = 2;
	struct gameState saveState = g;
	ok = buyCard(estate, game);
	if (ok){
		printf("  FAIL: buyCard returned error value on possible buy\n");
		passed = 0;
	}
	else printf("  PASS: buyCard returned correct value on possible buy\n");
	//All other player states should be same
	ok = otherPlayersChanged(game, &saveState, playerAttrs, currentPlayer, NUM_PLAYERS, PRINT);
	if (ok){
		printf("  FAIL: Unexpected changes in other player states\n");
		passed = 0;	
	}
	//Set attributes to ignore for current player
	playerAttrs[pa_discard] = 1;
	playerAttrs[pa_discardCount] = 1;
	//Check non-buying states for current player
	ok = checkPlayerChanged(game, &saveState, playerAttrs, currentPlayer, PRINT);
	if (ok){
		printf("  FAIL: Unexpected changes in current player state\n");
		passed = 0;
	}
	else printf("  PASS: All non-buying states unchanged for current player\n");
	int *countArr = calloc(treasure_map, sizeof(int));
	//Check new estate in discard pile
	ok = cardInDiscardChange(game, &saveState, currentPlayer, countArr, treasure_map, estate);
	if (countArr[estate] == 1) printf("  PASS: Estate increased by 1 in discard\n");
	else{
		printf("  FAIL: Estate did not change correctly in discard\n");
		passed = 0;
	}
	stateAttrs[sa_coins] = 1;
	stateAttrs[sa_numBuys] = 1;
	stateAttrs[sa_phase] = 1;
	ok = otherStateChanged(game, &saveState, stateAttrs, PRINT);
	if (ok){
		printf("  FAIL: Unexpected change in current turn state\n");
		passed = 0;
	}
	else printf("  PASS: All non-buying states unchanged for current turn\n");
	//Check number of coins is -2
	if (stateAttrs[sa_coins] == -2) printf("  PASS: Correct number of coins removed\n");
	else{
		printf("  FAIL: Incorrect number of coins removed: %d.\n", stateAttrs[sa_coins]);
		passed = 0;
	}	
	//Check numbner of buys is -1
	if (stateAttrs[sa_numBuys] == -1) printf("  PASS: Correct number of buys removed\n");	
	else{
		printf("  FAIL: Incorrect number of buys removed: %d.\n", stateAttrs[sa_numBuys]);
		passed = 0;
	}
	//Check Supply changed
	if ((ok = supplyChanged(game, &saveState, estate)) == -1) {
		printf("  PASS: Correct number of estates removed from supply.\n");
	}
	else{
		printf("  FAIL: Incorrect number of estates removed from suppply: %d.\n", ok);
		passed = 0;
	}
	testAssert(passed, "Attempt possible buy of Estate");
	if (!passed) success = 0;
	free(countArr);

	//Buy a card that has 0 supply
	printf("\n# Attempt impossible buy of estate with enough coins but no supply\n");
	passed = 1;
	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	currentPlayer = whoseTurn(game);
	g.supplyCount[estate] = 0;
	g.coins = 2;
	saveState = g;
	ok = buyCard(estate, game);
	if (ok == 0){
		printf("  FAIL: buyCard did not return error on impossible buy.\n");
		passed = 0;
	}
	else printf("  PASS: buyCard returned error value on impossible buy.\n");
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok) passed = 0;
	else printf("  PASS: No change to any game state.\n");
	if (!passed) success = 0;
	testAssert(passed, "Attempt impossible buy of Estate with no supply");

	//Buy a card that costs too much
	printf("\n# Attempt impossible buy of Smithy with not enough coins\n"); 
	passed = 1;
	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	currentPlayer = whoseTurn(game);
	g.supplyCount[smithy] = 10;
	g.coins = 3;
	saveState = g;
	ok = buyCard(smithy, game);
	if (ok == 0){
		printf("  FAIL: buyCard did not return error on impossible buy.\n");
		passed = 0;
	}
	else printf("  PASS: buyCard returned error value on impossible buy.\n");
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok) passed = 0;
	else printf("  PASS: No change to any game state.\n");
	if (!passed) success = 0;
	testAssert(passed, "Attempt impossible buy of Smithy without enough coins\n");

	if (success) printf("\n ########## PASSED Test of buyCard() ##########\n");
	else printf("\n ########## FAILED Test of buyCard() ##########\n");
	
	return 0;
}	
