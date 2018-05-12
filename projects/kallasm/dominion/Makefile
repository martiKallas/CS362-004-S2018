CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

testHelper.o: testHelper.h testHelper.c dominion.o interface.o rngs.o
	gcc -c testHelper.c -g $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randadvent: randomtestadventurer.c dominion.o interface.o rngs.o testHelper.o
	gcc -o randadvent randomtestadventurer.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

testRandomizer: testRandomizer.c dominion.o interface.o rngs.o testHelper.o
	gcc -o testRandomizer testRandomizer.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

unittestresults.out: randadvent testRandomizer
	./randadvent &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	./testRandomizer >> unittestresults.out
	gcov dominion.c >> unittestresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
