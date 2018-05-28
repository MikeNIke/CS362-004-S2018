/* -----------------------------------------------------------------------
 * Unit Test 1 of handCard function
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

void assertTrue(int expected, int actual, int* err_cnt) {
    if(expected == actual) {
        printf("TEST PASSED: Expected == Actual \n");
    } else {
        printf("TEST FAILED: Expected == %d, Actual == %d \n", expected, actual);
        (*err_cnt)++;
    }
}

void assertFalse(int expected, int actual, int* err_cnt) {
    if(expected != actual) {
        printf("TEST PASSED: Expected != Actual \n");
    } else {
        printf("TEST FAILED: Expected == %d, Actual == %d \n", expected, actual);
        (*err_cnt)++;
    }
}

int main() {
    int seed = 1000;
    int hc = 0;
    int err_cnt = 0;
    int numPlayer = 2;
    int handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int p1[5] = {adventurer, council_room, feast, gardens, mine}; 
    struct gameState G;
    int maxHandCount = 5;

    printf ("TESTING handCard():\n");
#if (NOISY_TEST == 1)
    printf("\tTesting every card in a hand of %d.\n", maxHandCount);
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.handCount[0] = maxHandCount;                 // set the number of cards on hand

    memcpy(G.hand[0], p1, sizeof(int) * maxHandCount); // set all the cards to hand 1
    for (handCount = 0; handCount < maxHandCount; handCount++) {
        hc = handCard(handCount, &G);
#if (NOISY_TEST     == 1)
        printf("\tIndex = %d:\n", handCount);
#endif
        assertTrue(p1[handCount], hc, &err_cnt);
    }
    
    printf("\tIndex 5 (out of bounds):\n");
    hc = handCard(5, &G);

    assertFalse(p1[5], hc, &err_cnt);

    if(err_cnt != 0)
        printf("\nFailure - Not all test passed!\n");
    else
        printf("\nAll tests passed!\n");

    return 0;
}
