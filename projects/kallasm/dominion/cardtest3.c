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
	int kCards[10] = {adventurer, gardens, council_room, smithy, minion, mine, cutpurse, sea_hag, tribute, village};
	struct gameState g; //defined in dominion.h
	struct gameState * game = &g;
	memset(game, 0, sizeof(struct gameState));
	int ok = 0;
	int passed = 1;
	int count = 0;
	ok = initializeGame(NUM_PLAYERS, kCards, SEED, game);
	int currentPlayer = whoseTurn(game);
	printf("\n\n\n\n######### Beginning Test of village card ############\n");
	
	//adjust top card in deck to be feast
	g.deckCount[currentPlayer] = 10;
	int dc = g.deckCount[currentPlayer];
	g.deck[currentPlayer][dc-1] = feast;
	//add village to handPos of current player
	int handPos = g.handCount[currentPlayer]-1;
	g.hand[currentPlayer][handPos] = village;
	//save state
	struct gameState saveState = g;
	//play village
	cardEffect(village, 0, 0, 0, game, handPos, NULL);
	//check village passes all basics except for handCount
	int* countArr = calloc(PC_TEST_NUM, sizeof(int));
	countArr[pc_handCount] = 1;
	ok = cardPlayedBasics(game, &saveState, village, countArr, treasure_map+1, PRINT);
	if(ok) passed = 0;
	//check hand count changes by 0 : -1 village + 1 feast
	count = countArr[pc_handCount];
	if (count != 0){
		printf("  FAIL: Hand count changed by %d.\n", count);
		passed = 0;
	}
	else printf("  PASS: Hand count changed by %d.\n", count);
	//check deck has -1 cards
	count = g.deckCount[currentPlayer] - saveState.deckCount[currentPlayer];
	if (count != -1){
		printf("  FAIL: Deck count decreased by %d.\n", count);
		passed = 0;
	}	
	else printf("  PASS: Deck count decreased by %d.\n", count);
	//check hand has +1 feast
	free(countArr);
	countArr = calloc(treasure_map+1, sizeof(int));
	cardInHandChange(game, &saveState, currentPlayer, countArr, treasure_map+1, -1);
	ok = 0;
	if (countArr[feast] != 1){
		printf("  FAIL: Hand did not contain extra feast.\n");
		passed = 0;
	}
	else printf("  PASS: Hand contained an extra feast.\n");
	//check num actions hasn't changed: -1 to play card, +1 from card
	count = g.numActions - saveState.numActions;
	if(count != 1){
		passed = 0;
		printf("  FAIL: Actions change: %d.\n", count);
	}
	else printf("  PASS: Number of available actions increased by %d.\n", count);
	//check no other player states have changed
	int* plyrAttr = calloc(PLAYER_ATTR_NUM, sizeof(int));
	ok = otherPlayersChanged(game, &saveState, plyrAttr, currentPlayer, NUM_PLAYERS, PRINT);
	if (ok) passed = 0;

	if (passed) printf("\n ########## PASSED Test of village ##########\n");
	else printf("\n ########## FAILED Test of village ##########\n");

	free(countArr);
	return 0;
}
