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
	printf("\n\n\n\n######### Beginning Test of adventurer card ############\n");
	
	//adjust top five cards in deck to be feast, gardens, mine, copper, and copper
	int dc = g.deckCount[currentPlayer];
	g.deck[currentPlayer][dc -1] = feast;
	g.deck[currentPlayer][dc -2] = gardens;
	g.deck[currentPlayer][dc -3] = mine;
	g.deck[currentPlayer][dc -4] = copper;
	g.deck[currentPlayer][dc -5] = copper;
	//add adventurer to handPos of current player
	int handPos = g.handCount[currentPlayer]-1;
	g.hand[currentPlayer][handPos] = adventurer;
	//save state
	struct gameState saveState = g;
	//play adventurer
	cardEffect(adventurer, 0, 0, 0, game, handPos, NULL);
	//check adventurer passes all basics except for handCount
	int* countArr = calloc(PC_TEST_NUM, sizeof(int));
	countArr[pc_handCount] = 1;
	ok = cardPlayedBasics(game, &saveState, adventurer, countArr, treasure_map+1, PRINT);
	if(ok) passed = 0;
	//check hand count +1 : -1 adventurer and +2 others
	count = countArr[pc_handCount];
	if (count != 1){
		printf("  FAIL: Hand count changed by %d.\n", count);
		passed = 0;
	}
	else printf("  PASS: Hand count changed by %d.\n", count);
	//check deck has -5 cards
	count = g.deckCount[currentPlayer] - saveState.deckCount[currentPlayer];
	if (count != -5){
		printf("  FAIL: Deck count decreased by %d.\n", count);
		passed = 0;
	}	
	else printf("  PASS: Deck count decreased by %d.\n", count);
	//check hand has +2 copper
	free(countArr);
	countArr = calloc(treasure_map+1, sizeof(int));
	cardInHandChange(game, &saveState, currentPlayer, countArr, treasure_map+1, -1);
	ok = 0;
	if (countArr[copper] != 2){
		printf("  FAIL: Hand did not contain 2 extra coppers.\n");
		passed = 0;
		ok = 1;
	}
	if (!ok){
		printf("  PASS: Hand contained 2 extra coppers.\n");
	}
	//check discard pile has feast, gardens, mine
	free(countArr);
	countArr = calloc(treasure_map+1, sizeof(int));
	cardInDiscardChange(game, &saveState, currentPlayer, countArr, treasure_map+1, -1);
	ok = 0;
	if (countArr[feast] != 1){
		printf("  FAIL: Feast change in discard was %d.\n", countArr[feast]);
		passed = 0;
		ok = 1;
	}
	if (countArr[gardens] != 1){
		printf("  FAIL: Gardens change in discard was %d.\n", countArr[gardens]);
		passed = 0;
		ok = 1;
	}
	if (countArr[mine] != 1){
		printf("  FAIL: Mine change in discard was %d.\n", countArr[mine]);
		passed = 0;
		ok = 1;
	}
	if (!ok){
		printf("  PASS: Discard pile contains feast, gardens and mine.\n");
	}
	//check discardCount is +3
	count = g.discardCount[currentPlayer] - saveState.discardCount[currentPlayer];
	if (count != 3){
		printf("  FAIL: Discard count changed by %d.\n", count);
		passed = 0;
	}
	else printf("  PASS: Discard count changed by %d.\n", count);
	//check no other player states have changed
	int* plyrAttr = calloc(PLAYER_ATTR_NUM, sizeof(int));
	ok = otherPlayersChanged(game, &saveState, plyrAttr, currentPlayer, NUM_PLAYERS, PRINT);
	if (ok) passed = 0;

	if (passed) printf("\n ########## PASSED Test of adventurer ##########\n");
	else printf("\n ########## FAILED Test of adventurer ##########\n");

	free(countArr);
	return 0;
}
