/* -----------------------------------------------------------------------
 * Unit Test 4 of buyCard function
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

void assertTrue(int actual, int expected, int* err_cnt) {
    if(expected == actual) {
        printf("TEST PASSED: Expected == Actual \n");
    } else {
        printf("TEST FAILED: Expected == %d, Actual == %d \n", expected, actual);
        (*err_cnt)++;
    }
}

void assertFalse(int actual, int expected, int* err_cnt) {
    if(expected != actual) {
        printf("TEST PASSED: Expected != Actual \n");
    } else {
        printf("TEST FAILED: Expected == %d, Actual == %d \n", expected, actual);
        (*err_cnt)++;
    }
}

int main() {
    int seed = 1000;
    int purchase = 0;
    int err_cnt = 0;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING buyCard() with Gold Card:\n");
   
    initializeGame(numPlayer, k, seed, &G);

    printf("\tNo buys left:\n");
    G.numBuys = 0;
    purchase = buyCard(6, &G);
    assertTrue(purchase, -1, &err_cnt);

    printf("\tNo coins left:\n");
    G.numBuys = 5;
    G.coins = 0;
    purchase = buyCard(6, &G);
    assertTrue(purchase, -1, &err_cnt);

    printf("\tCard supply out:\n");
    G.numBuys = 1;
    G.coins = 100;
    G.supplyCount[6] = 0;
    purchase = buyCard(6, &G);
    assertTrue(purchase, -1, &err_cnt);

    printf("\tSuccessful purchase:\n");
    G.supplyCount[6] = 1;
    G.coins = 100;
    purchase = buyCard(6, &G);
    assertTrue(purchase, 0, &err_cnt);

    if(err_cnt != 0)
        printf("\nFailure - Not all test passed!\n");
    else
        printf("\nAll tests passed!\n");

    return 0;
}
