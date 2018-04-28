/* Description: Functions to help with unit testing of dominion game
 * Author: Marti Kallas
 * Date: 4/26/2018
 */
#ifndef MK_TESTHELPER_H
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "interface.h"
#include "rngs.h"

#define STATE_ATTR_NUM 9
#define PLAYER_ATTR_NUM 6

//Used to track non-player-specific attributes in gameState struct
//	enums are variable name in gameState struct prepended with sa_
//	These are separate from PLAYER_ATTRIBUTE because they do not 
//	require a player index to identify the correct variable
enum STATE_ATTRIBUTE{
	sa_numPlayers = 0,
	sa_outpostPlayed,
	sa_outpostTurn,
	sa_whoseTurn,
	sa_phase,
	sa_numActions,
	sa_coins,
	sa_numBuys,
	sa_playedCardCount
};

//Used to track player-specific attributes in gameState struct
//	enums are variable name in gameState struct prepended with pa_
//	These require a player index value to identify the correct variable
enum PLAYER_ATTRIBUTE{
	pa_hand = 0,
	pa_handCount,
	pa_deck,
	pa_deckCount,
	pa_discard,
	pa_discardCount
};

/* Description: if test is 0, prints "<testName> failed"
 * 	If test is not 0, prints "<testName> succeeded"
 * 	Returns 1 if test is true. Returns 0 otherwise.
 * 	Returns -1 in case of error.
 */
int testAssert(int test, char * testName);

/* Description: Returns 0 if hand of player is identical in
 * 	cur and old. Returns other numbers depending on point of failure
 * 	-1 : Hand sizes are not the same
 * 	1+ : Index of card + 1 in current state than does not match old state
 * 		Must use index + 1 because index starts at 0 which is no change
 */
int handChanged(struct gameState* cur, struct gameState* old, int player);

/* Description: Returns 0 if discard of player is identical in
 * 	cur and old. Returns other numbers depending on point of failure
 * 	-1 : Discard sizes are not the same
 * 	1+ : Index of card + 1 in current state than does not match old state
 * 		Must use index + 1 because index starts at 0 which is no change
 */
int discardChanged(struct gameState* cur, struct gameState* old, int player);

/* Description: Returns 0 if deck of player is identical in
 * 	cur and old. Returns other numbers depending on point of failure
 * 	-1 : Deck sizes are not the same
 * 	1+ : Index of card + 1 in current state than does not match old state
 * 		Must use index + 1 because index starts at 0 which is no change
 */
int deckChanged(struct gameState* cur, struct gameState* old, int player);

/* Description: Returns 0 if played cards are identical in
 * 	cur and old. Returns other numbers depending on point of failure
 * 	-1 : playedCard sizes are not the same
 * 	1+ : Index of card + 1 in current state than does not match old state
 * 		Must use index + 1 because index starts at 0 which is no change
 */
int playedChanged(struct gameState* cur, struct gameState* old);

/* Description: Has two running options:
 * 	Card == -1: Checks all cards in supply. If supply hasn't changed from
 * 		old to cur then returns 0. Otherwise, returns the index + 1 of the first
 * 		card that changed. Index + 1 so 0 represents unchanged.
 * 	Card >= 0 or <= treasure_map: Checks only if that specific card changed.
 * 		Returns the cur quantity minus the old quantity.
 */
int supplyChanged(struct gameState* cur, struct gameState* old, int card);


/* Description: Has two running options:
 * 	Card == -1: Checks all cards in embargo. If embargo hasn't changed from
 * 		old to cur then returns 0. Otherwise, returns the index + 1 of the first
 * 		card that changed. Index + 1 so 0 represents unchanged.
 * 	Card >= 0 or <= treasure_map: Checks only if that specific card changed.
 * 		Returns the cur quantity minus the old quantity.
 */
int embargoChanged(struct gameState* cur, struct gameState* old, int card);

/* Description: Deterimines if certain state attributes have changed from old to 
 * 	cur. Attributes are defined in enum STATE_ATTRIBUTE. 
 * 	Any STATE_ATTRIBUTE index set to 1 in stateAttrs will not affect the return int. 
 * 	Returns 0 if no changes to any attributes. Returns 1 if any state changed that was not ignored.
 * 	If printFail is non-zero, the function will print failure message on any non-ignored change.
 * Preconditions: All indicies in stateAttrs must be 0 affect return value.
 * Postconditions: stateAttrs array will be set to 0 for didn't change or the difference of cur - old
 * 	for each STATE_ATTRIBUTE if that attribute did change.
 */
int otherStateChanged(struct gameState* cur, struct gameState* old, int stateAttrs[STATE_ATTR_NUM], int printFail);

/* Desctiption: Determines if certain player game state attributes have changed from old to cur.
 * 	Attributes are defined in enum PLAYER_ATTRIBUTE.
 * 	Any PLAYER_ATTRIBUTE index set to 1 in playerAttrs will not affect the return int.
 * 	Returns 0 if no changes to any attributes. Retruns 1 if any state changed that was not ignored.
 * 	If printFail is non-zero, the function will print failure message on any non-ignored change.
 * Preconditions: All indices in playerAttrs must be 0 to affect return value.
 * Postconditions: playerAttrs will be set to difference of cur - old.
 */
int checkPlayerChanged(	struct gameState* cur, 
			struct gameState* old, 
			int playerAttrs[PLAYER_ATTR_NUM], 
			int player, 
			int printFail);

/* Description: Determines if deck contains same count of cards between cur and old.
 * 	Uses hash counting to increment countArr[card] for each card in deck[player][].
 * 	Returns index of first difference in countArr if there is a difference.
 * 	Returns 0 if no differences found.
 * 	size indicates max value of cards that can be found in deck (by card type not quantity)
 * Preconditions: countArr is an array initialized to all 0 and of size, size.
 * 	deckCount should be accurate for both cur and old. 
 * Postconditions: countArr[card] contains difference cur - old for card value
 */
int deckCardsChanged(struct gameState* cur, struct gameState* old, int player, int size, int *countArr);

/* Description: Runs checkPlayerChanged on all players except for curPlayer.
 * 	Returns 0 if no change or 1 if change.
 */
int otherPlayersChanged(struct gameState* cur, 
			struct gameState* old, 
			int playerAttrs[PLAYER_ATTR_NUM], 
			int curPlayer, 
			int numPlayers,
			int printFail);

/* Description: Determines if cards in hand have changed.
 * 	Similar to deckCardsChanged. Uses hash counting to increment countArr for each card in deck[player][]
 * 	Returns index of first difference in countArr if there is a difference.
 * 	Returns 0 if no differences found.
 * 	size = size of countArr, should be max card value for hash counting
 * 	Can ignore a card with the ignore flag. This will check all cards have changed except for that card
 * 		Set ignore to -1 to check all card values
 * Preconditions: countArr is initialized to all 0
 * 	handCount should be accurate for both cur and old
 * Postconditions: countArr[card] contains difference cur - old for card value
 */
int cardInHandChange(	struct gameState* cur, 
			struct gameState* old, 
			int player, 
			int *countArr, 
			int size, 
			int ignore);

/* Description: Determines if cards in discard have changed.
 * 	Similar to deckCardsChanged. Uses hash counting to increment countArr for each card in deck[player][]
 * 	Returns index of first difference in countArr if there is a difference.
 * 	Returns 0 if no differences found.
 * 	size = size of countArr, should be max card value for hash counting
 * 	Can ignore a card with the ignore flag. This will check all cards have changed except for that card
 * 		Set ignore to -1 to check all card values
 * Preconditions: countArr is initialized to all 0
 * 	discardCount should be accurate for both cur and old
 * Postconditions: countArr[card] contains difference cur - old for card value
 */
int cardInDiscardChange(struct gameState* cur, 
			struct gameState* old, 
			int player, 
			int *countArr, 
			int size, 
			int ignore);

/* Description: Returns 1 if there is any change to the game state. Returns 0 otherwise.
 */
int anyChange(struct gameState* cur, struct gameState* old, int numPlayers, int printFail);

#endif
