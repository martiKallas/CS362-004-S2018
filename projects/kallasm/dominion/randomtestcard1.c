#include "testHelper.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
	srand(time(NULL));
	struct gameState gs;
	struct gamestate* g = &gs;
	
	memset(g, 0, sizeof(struct gameState));
	int seed = rand()%100;
	randomizeGameState(g, seed);
	printGameState(g);
	return 0;
}
