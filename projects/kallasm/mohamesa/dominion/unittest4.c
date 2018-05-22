#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "testHelper.h"
#include <signal.h>


#define SEED 10
#define PRINT 1
#define NO_PRINT 0
#define NUM_PLAYERS 4

int segFaultFlag = 0;

//source: https://stackoverflow.com/questions/2663456/how-to-write-a-signal-handler-to-catch-sigsegv
static void handler(int sig, siginfo_t *si, void *unused){
	segFaultFlag = 1;
}

int main(){

	//Define error handler for out-of-range test
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler;
	sigaction(SIGSEGV, &action, NULL);

	struct gameState g; //defined in dominion.h
	struct gameState * game = &g;
	memset(game, 0, sizeof(struct gameState));
	int success = 1;

	printf("\n\n\n\n########## Beginning Test of handCard() ##########\n");

	printf("\n# Check Card == 1 at position 0\n");
	int ok = 0;
	int passed = 1;
	int currentPlayer = 0;
	int handPos = 0;
	g.hand[currentPlayer][handPos] = 1;
	struct gameState saveState = g;
	ok = handCard(handPos, game);
	if (ok == 1) printf("  PASS: Card at position 0 is 1\n");
	else{
		printf("  FAIL: Card at position 0 is %d\n", ok);
		passed = 0;
	}
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0;}
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert(passed, "Check Card == 1 at position 0");
	if(!passed) success = 0;

	printf("\n# Check Card == 0 at position 5\n");
	ok = 0;
	passed = 1;
	currentPlayer = 0;
	handPos = 5;
	g.hand[currentPlayer][handPos] = 0;
	saveState = g;
	ok = handCard(handPos, game);
	if (ok == 0) printf("  PASS: Card at position 5 is 0\n");
	else{
		printf("  FAIL: Card at position 5 is %d\n", ok);
		passed = 0;
	}
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0;}
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert(passed, "Check card == 0 at position 5");
	if(!passed) success = 0;

	printf("\n# Check Card == treasure_map at position MAX_HAND\n");
	ok = 0;
	passed = 1;
	currentPlayer = 0;
	handPos = MAX_HAND -1;
	g.hand[currentPlayer][handPos] = treasure_map;
	saveState = g;
	ok = handCard(handPos, game);
	if (ok == treasure_map) printf("  PASS: Card at position MAX_HAND is treasure_map\n");
	else{
		printf("  FAIL: Card at position MAX_HAND is %d\n", ok);
		passed = 0;
	}
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0;}
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert(passed, "Check max card value at max hand position");
	if(!passed) success = 0;

	printf("\n# Check for error when accessing position > handCount\n");
	ok = 0;
	passed = 1;
	handPos = 6;
	int handCount = 5;
	memset(game, 0, sizeof(struct gameState));
	g.hand[currentPlayer][handPos] = 1;
	g.handCount[currentPlayer] = handCount;
	saveState = g;
	ok = handCard(handPos, game);
	if (ok == 1){
		printf("  FAIL: Return value is 1\n");
		passed = 0;
	}
	else{
		printf("  PASS: Return value is %d\n", ok);
	}
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0;}
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert(passed, "Check for error value when position is greater than handCount");
	if(!passed) success = 0;


	printf("\n# Check for error when accessing position > MAX_HAND\n");
	ok = 0;
	passed = 1;
	handPos = MAX_HAND + 1;
	handCount = 5;
	memset(game, 0, sizeof(struct gameState));
	saveState = g;
	ok = handCard(handPos, game);
	if (ok >= 0 && ok <= treasure_map && !segFaultFlag){
		printf("  FAIL: Return value is a standard card value\n");
		passed = 0;
	}
	else if (segFaultFlag){
		printf("  FAIL: Return value is a standard card value or seg fault encountered\n");
		passed = 0;
	}
	else if (ok > 0){
		printf("  ALERT: Return value is not a standard card but is positive\n");
	}
	if (passed) printf("  PASS: Return value is %d\n", ok);
	ok = anyChange(game, &saveState, NUM_PLAYERS, PRINT);
	if (ok){ passed = 0;}
	else printf("  PASS: No change to any portion of gameState.\n");
	testAssert(passed, "Check for error value when position is greater than handCount");
	if(!passed) success = 0;

	if (success) printf("\n ########## PASSED Test of handCard() ##########\n");
	else printf("\n ########## FAILED Test of handCard() ##########\n");

	return 0;
}
