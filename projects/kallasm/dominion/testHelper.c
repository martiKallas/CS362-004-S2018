#include "testHelper.h"

int testAssert(int test, char * testName){
	if (test == 0){
		printf("#   FAIL: %s failed.\n", testName); 
		return 0;
	}
	else if (test != 0){
		printf("# PASSED: %s succeeded.\n", testName); 
		return 1;
	}
	else{
		printf("Error in testAssert.\n");
		return -1;
	}
}

int handChanged(struct gameState* cur, struct gameState* old, int player){
	int curHand = cur->handCount[player];
	int oldHand = old->handCount[player];
	if (curHand != oldHand) return -1;
	int i;
	for (i = 0; i < oldHand; i++){
		if(cur->hand[player][i] != old->hand[player][i]) return i+1;
	}
	return 0;
}
	
int discardChanged(struct gameState* cur, struct gameState* old, int player){
	int curDiscard = cur->discardCount[player];
	int oldDiscard = old->discardCount[player];
	if (curDiscard != oldDiscard) return -1;
	int i;
	for (i = 0; i < oldDiscard; i++){
		if(cur->discard[player][i] != old->discard[player][i]) return i+1;
	}
	return 0;
}

int deckChanged(struct gameState* cur, struct gameState* old, int player){
	int curDeck = cur->deckCount[player];
	int oldDeck = old->deckCount[player];
	if (curDeck != oldDeck) return -1;
	int i;
	for (i = 0; i < oldDeck; i++){
		if(cur->deck[player][i] != old->deck[player][i]) return i+1;
	}
	return 0;
}


int playedChanged(struct gameState* cur, struct gameState* old){
	int curPlayed = cur->playedCardCount;
	int oldPlayed = old->playedCardCount;
	if (curPlayed != oldPlayed) return -1;
	int i;
	for (i = 0; i < oldPlayed; i++){
		if(cur->playedCards[i] != old->playedCards[i]) return i+1;
	}
	return 0;
}

int supplyChanged(struct gameState* cur, struct gameState* old, int card){
	//If card is -1 check all supplies:
	if (card == -1){
		int i;
		for(i=0; i < (treasure_map+1); i++){
			if (cur->supplyCount[i] != old->supplyCount[i]) return i+1;
		}	
		return 0;
	}
	else if (card >= 0 && card <= treasure_map){
		return (cur->supplyCount[card] - old->supplyCount[card]);
	}
	else{
		printf("!!!!!!!! Error in supplyChanged() !!!!!!!!!!\n");
		printf("Card is %d. Should be -1 or 0 to treasure_map\n", card);
		printf("Exitting....\n");
		exit(EXIT_FAILURE);
	}
	return 400;
}
	

int embargoChanged(struct gameState* cur, struct gameState* old, int card){
	//If card is -1 check all supplies:
	if (card == -1){
		int i;
		for(i=0; i < (treasure_map+1); i++){
			if (cur->embargoTokens[i] != old->embargoTokens[i]) return i+1;
		}	
		return 0;
	}
	else if (card >= 0 && card <= treasure_map){
		return (cur->embargoTokens[card] - old->embargoTokens[card]);
	}
	else{
		printf("!!!!!!!! Error in embargoChanged() !!!!!!!!!!\n");
		printf("Card is %d. Should be -1 or 0 to treasure_map\n", card);
		printf("Exitting....\n");
		exit(EXIT_FAILURE);
	}
	//should not get here
	return 400;
}


int otherStateChanged(struct gameState* cur, struct gameState* old, int stateAttrs[STATE_ATTR_NUM], int printFail){
	int i;
	int change = 0;
	int diff = 0;
	for(i = 0; i < STATE_ATTR_NUM; i++){
		switch (i){
			case 0:
				diff = cur->numPlayers - old->numPlayers;
				if (!stateAttrs[i] && diff){
					change = 1;
					if (printFail){ printf(
						"  FAIL: numPlayers changed. Difference: %d.\n", diff);
					}
				}
				stateAttrs[i] = diff; 
				break;
			case 1:
				diff = cur->outpostPlayed - old->outpostPlayed;
				if (!stateAttrs[i] && diff){
					change = 1;
					if (printFail){ printf(
						"  FAIL: outpostPlayed changed. Difference: %d.\n", diff);
					}
				}
				stateAttrs[i] = diff; 
				break;
			case 2:
				diff = cur->outpostTurn - old->outpostTurn;
				if (!stateAttrs[i] && diff){
					change = 1;
					if (printFail){ printf(
						"  FAIL: outpostTurn changed. Difference: %d.\n", diff);
					}
				}
				stateAttrs[i] = diff; 
				break;
			case 3:
				diff = cur->whoseTurn - old->whoseTurn;
				if (!stateAttrs[i] && diff){
					change = 1;
					if (printFail){ printf(
						"  FAIL: whoseTurn changed. Difference: %d.\n", diff);
					}
				}
				stateAttrs[i] = diff; 
				break;
			case 4:
				diff = cur->phase - old->phase;
				if (!stateAttrs[i] && diff){
					change = 1;
					if (printFail){ printf(
						"  FAIL: phase changed. Difference: %d.\n", diff);
					}
				}
				stateAttrs[i] = diff; 
				break;
			case 5:
				diff = cur->numActions - old->numActions;
				if (!stateAttrs[i] && diff){
					change = 1;
					if (printFail){ printf(
						"  FAIL: numActions changed. Difference: %d.\n", diff);
					}
				}
				stateAttrs[i] = diff; 
				break;
			case 6:
				diff = cur->coins - old->coins;
				if (!stateAttrs[i] && diff){
					change = 1;
					if (printFail){ printf(
						"  FAIL: coins changed. Difference: %d.\n", diff);
					}
				}
				stateAttrs[i] = diff; 
				break;
			case 7:
				diff = cur->numBuys - old->numBuys;
				if (!stateAttrs[i] && diff){
					change = 1;
					if (printFail){ printf(
						"  FAIL: numBuys changed. Difference: %d.\n", diff);
					}
				}
				stateAttrs[i] = diff; 
				break;
			case 8:
				diff = cur->playedCardCount - old->playedCardCount;
				if (!stateAttrs[i] && diff){
					change = 1;
					if (printFail){ printf(
						"  FAIL: playedCardCount changed. Difference: %d.\n", diff);
					}
				}
				stateAttrs[i] = diff; 
				break;
			default:
				printf("\n!!!!!!!!!! Should not get here !!!!!!!!!!\n");
				printf("ERROR IN otherStateChanged()\n");
				printf("Exitting.... \n");
				exit(EXIT_FAILURE);
		}//switch
	}//for loop
	return change;
}

int checkPlayerChanged(struct gameState* cur, struct gameState* old, int playerAttrs[PLAYER_ATTR_NUM], int player, int printFail){
	int i;
	int change = 0;	
	int diff = 0;
	for(i = 0; i < PLAYER_ATTR_NUM; i++){
		switch (i){
			//pa_hand and pa_handCount
			case pa_hand:
				diff = handChanged(cur, old, player);
				//changes to hand cards
				if (!playerAttrs[pa_hand] && (diff > 0)){
					change = 1;
					if (printFail){ printf(
						"  FAIL: Cards in player %d's hand are different at index %d.\n",
						player, (diff-1));	
					}
				}
				if (!playerAttrs[pa_handCount] && (diff < 0)){
					change = 1;
					if (printFail){ printf(
						"  FAIL: Number of cards in player %d's hand have changed.\n",
						player);
					}
				}
				playerAttrs[i] = diff; 
				break;
			case pa_handCount:
				//already check above
				break;

			//pa_deck and pa_deckCount
			case pa_deck:
				diff = deckChanged(cur, old, player);
				//changes to deck cards
				if (!playerAttrs[pa_deck] && (diff > 0)){
					change = 1;
					if (printFail){ printf(
						"  FAIL: Cards in player %d's deck are different at index %d.\n",
						player, (diff-1));	
					}
				}
				if (!playerAttrs[pa_deckCount] && (diff < 0)){
					change = 1;
					if (printFail){ printf(
						"  FAIL: Number of cards in player %d's deck have changed.\n",
						player);
					}
				}
				playerAttrs[i] = diff; 
				break;
			case pa_deckCount:
				//already changed above
				break;

			//pa_discard and pa_discardCount
			case pa_discard:
				diff = discardChanged(cur, old, player);
				//changes to discard cards
				if (!playerAttrs[pa_discard] && (diff > 0)){
					change = 1;
					if (printFail){ printf(
						"  FAIL: Cards in player %d's discard are different at index %d.\n",
						player, (diff-1));	
					}
				}
				if (!playerAttrs[pa_discardCount] && (diff < 0)){
					change = 1;
					if (printFail){ printf(
						"  FAIL: Number of cards in player %d's discard have changed.\n",
						player);
					}
				}
				playerAttrs[i] = diff; 
				break;
			case pa_discardCount:
				//already handled above
				break;
			default:
				printf("\n!!!!!!!!!! Should not get here !!!!!!!!!!\n");
				printf("ERROR IN otherStateChanged()\n");
				printf("Exitting.... \n");
				exit(EXIT_FAILURE);
		}//switch	
	}//for loop
	return change;
}
	
int deckCardsChanged(struct gameState* cur, struct gameState* old, int player, int size, int *countArr){
	int i;
	int card = 0;
	int change = 0;
	//add cards in current state
	for (i = 0; i < cur->deckCount[player]; i++){
		card = cur->deck[player][i];
		if (card > (size-1)){
			printf("!!!!!!!!!! ERRROR IN deckCardsChanged !!!!!!!!!!!!\n");
			printf("Card value %d, larger than size %d, for player %d in current game state.\n", card, size, player);
			exit(EXIT_FAILURE);
		}	
		countArr[card]++;
	}		
	//subtract cards in old state
	for (i = 0; i < old->deckCount[player]; i++){
		card = old->deck[player][i];
		if (card > (size-1)){
			printf("!!!!!!!!!! ERRROR IN deckCardsChanged !!!!!!!!!!!!\n");
			printf("Card value %d, larger than size %d, for player %d in old game state.\n", card, size, player);
			exit(EXIT_FAILURE);
		}	
		countArr[card]--;
	}		
	//look for changes
	for (i=0; i < size; i++){
		if (countArr[i]){
			change = i;
			break;
		}
	}	

	return change;
}	

int otherPlayersChanged(struct gameState* cur, 
			struct gameState* old, 
			int playerAttrs[PLAYER_ATTR_NUM], 
			int curPlayer, 
			int numPlayers, 
			int printFail){
	int change = 0;
	int i;
	int player;
	for (i = 1; i < numPlayers; i++){
		player = (i + curPlayer)%numPlayers;
		if (checkPlayerChanged(cur, old, playerAttrs, player, printFail)) change = 1;
	}
	if (!change) printf("  PASS: All other player's states are unchanged. \n");
	else printf("  FAIL: Changes detected in other player's states.\n");
	return change;
}	

int cardInHandChange(struct gameState* cur, struct gameState* old, int player, int *countArr, int size, int ignore){
	int i;
	int card = 0;
	int change = 0;
	//add cards in current state
	for (i = 0; i < cur->handCount[player]; i++){
		card = cur->hand[player][i];
		if (card > (size-1)){
			printf("!!!!!!!!!! ERRROR IN cardInHandChange() !!!!!!!!!!!!\n");
			printf("Card value %d, larger than size %d, for player %d in current game state.\n", card, size, player);
			exit(EXIT_FAILURE);
		}	
		countArr[card]++;
	}		
	//subtract cards in old state
	for (i = 0; i < old->handCount[player]; i++){
		card = old->hand[player][i];
		if (card > (size-1)){
			printf("!!!!!!!!!! ERRROR IN cardInHandChange() !!!!!!!!!!!!\n");
			printf("Card value %d, larger than size %d, for player %d in old game state.\n", card, size, player);
			exit(EXIT_FAILURE);
		}	
		countArr[card]--;
	}		
	//look for changes
	for (i=0; i < size; i++){
		if (countArr[i] && i != ignore){
			change = i;
			break;
		}
	}	

	return change;
}	


int cardInDiscardChange(struct gameState* cur, struct gameState* old, int player, int *countArr, int size, int ignore){
	int i;
	int card = 0;
	int change = 0;
	//add cards in current state
	for (i = 0; i < cur->discardCount[player]; i++){
		card = cur->discard[player][i];
		if (card > (size-1)){
			printf("!!!!!!!!!! ERRROR IN cardInHandChange() !!!!!!!!!!!!\n");
			printf("Card value %d, larger than size %d, for player %d in current game state.\n", card, size, player);
			exit(EXIT_FAILURE);
		}	
		countArr[card]++;
	}		
	//subtract cards in old state
	for (i = 0; i < old->discardCount[player]; i++){
		card = old->discard[player][i];
		if (card > (size-1)){
			printf("!!!!!!!!!! ERRROR IN cardInHandChange() !!!!!!!!!!!!\n");
			printf("Card value %d, larger than size %d, for player %d in old game state.\n", card, size, player);
			exit(EXIT_FAILURE);
		}	
		countArr[card]--;
	}		
	//look for changes
	for (i=0; i < size; i++){
		if (countArr[i] && i != ignore){
			change = i;
			break;
		}
	}	
	return change;
}	

int anyChange(struct gameState* cur, struct gameState* old, int numPlayers, int printFail){
	int i;
	int check = 0;
	int change = 0;
	int* pAttr = calloc(PLAYER_ATTR_NUM, sizeof(int));
	//Check all states of each player
	for (i = 0; i < numPlayers; i++){
		check = checkPlayerChanged(cur, old, pAttr, i, printFail);
		if(check) change = 1;
	}
	free(pAttr);

	//Check all non-player-indexed states
	int* sAttr = calloc(STATE_ATTR_NUM, sizeof(int));
	check = otherStateChanged(cur, old, sAttr, printFail);
	if (check) change = 1;
	free(sAttr);
	return change;	
}
