CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
	-./testme >> testme.out
	gcov testme >> testme.out
	cat testme.c.gcov >> testme.out

clean:
	rm -f testme *.o *.gcov *.gcda *.gcno *.so *.out
