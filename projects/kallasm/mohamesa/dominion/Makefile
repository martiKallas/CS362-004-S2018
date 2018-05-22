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

rta: randomtestadventurer.c dominion.o interface.o rngs.o testHelper.o
	gcc -o rta randomtestadventurer.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

rt1: randomtestcard1.c dominion.o interface.o rngs.o testHelper.o
	gcc -o rt1 randomtestcard1.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

rt2: randomtestcard2.c dominion.o interface.o rngs.o testHelper.o
	gcc -o rt2 randomtestcard2.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

testRandomizer: testRandomizer.c dominion.o interface.o rngs.o testHelper.o
	gcc -o testRandomizer testRandomizer.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

runrandom: rta rt1 rt2
	./rta &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	./rt1 &> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	./rt2 &> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

unittest1: unittest1.c dominion.o interface.o rngs.o testHelper.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

unittest2: unittest2.c dominion.o interface.o rngs.o testHelper.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

unittest3: unittest3.c dominion.o interface.o rngs.o testHelper.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

unittest4: unittest4.c dominion.o interface.o rngs.o testHelper.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o interface.o rngs.o testHelper.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o interface.o rngs.o testHelper.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o interface.o rngs.o testHelper.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o interface.o rngs.o testHelper.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o interface.o testHelper.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

runtests: rta rt1 rt2 unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 
	./rta &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	./rt1 &> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	./rt2 &> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out rta rt1 rt2 unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
