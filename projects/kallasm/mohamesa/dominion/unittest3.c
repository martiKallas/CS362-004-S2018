#include "testHelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SEED 10
#define PRINT 1
#define NO_PRINT 0
#define NUM_PLAYERS 4

int main(){
	int kCards[10] = {adventurer, gardens, council_room, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState g; //defined in dominion.h
	struct gameState * game = &g;
	memset(game, 0, sizeof(struct gameState));
	int success = 1;

	printf("\n\n\n\n########## Beginning Test of isGameOver() ##########\n");

	//Check initialized state
	printf("\n# Check initialized state with no changes\n");
	int ok = 0;
	int over = 0;
	int passed = 1;
	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	struct gameState saveState = g;
	over = isGameOver(game);
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0; success = 0;}
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert((passed && !over), "Game is not over after initialize");

	printf("\n# Check Province pile is 1\n");
	ok = 0;
	over = 0;
	passed = 1;
	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	g.supplyCount[province] = 1;
	saveState = g;
	over = isGameOver(game);
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0; success = 0;} 
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert((passed && !over), "Game is not over with Province pile = 1");

	printf("\n# Check Province pile is 0\n");
	ok = 0;
	over = 0;
	passed = 1;
	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	g.supplyCount[province] = 0;
	saveState = g;
	over = isGameOver(game);
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0; success = 0;} 
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert((passed && over), "Game is over with Province pile = 0");
	
	printf("\n# Check estate supply pile is 0\n");
	ok = 0;
	over = 0;
	passed = 1;
	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	g.supplyCount[estate] = 0;
	saveState = g;
	over = isGameOver(game);
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0; success = 0;} 
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert((passed && !over), "Game is not over with estate pile = 0");

	printf("\n# Check estate and duchy piles are 0\n");
	ok = 0;
	over = 0;
	passed = 1;
	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	g.supplyCount[estate] = 0;
	g.supplyCount[duchy] = 0;
	saveState = g;
	over = isGameOver(game);
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0; success = 0;} 
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert((passed && !over), "Game is not over with 2 supply piles = 0");

	printf("\n# Check estate, duchy and adventurer piles are 0\n");
	ok = 0;
	over = 0;
	passed = 1;
	initializeGame(NUM_PLAYERS, kCards, SEED, game);
	g.supplyCount[estate] = 0;
	g.supplyCount[duchy] = 0;
	g.supplyCount[adventurer] = 0;
	saveState = g;
	over = isGameOver(game);
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0; success = 0;} 
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert((passed && over), "Game is over with 3 supply piles = 0");

	if (success) printf("\n ########## PASSED Test of isGameOver() ##########\n");
	else printf("\n ########## FAILED Test of isGameOver() ##########\n");

	return 0;
}
