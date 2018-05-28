/* -----------------------------------------------------------------------
 * Unit Test 3 of isGameOver function
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
    int err_cnt = 0;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING isGameOver():\n");
  
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    G.supplyCount[province] = 0;

    printf("\tProvince cards empty:\n");
    assertTrue(isGameOver(&G),1,&err_cnt);

    G.supplyCount[province] = 1;

    G.supplyCount[0] = 0;
    G.supplyCount[1] = 0;
    G.supplyCount[2] = 0;

    printf("\tThree supply piles are empty:\n");
    assertTrue(isGameOver(&G),1,&err_cnt);

    G.supplyCount[0] = 1;
    G.supplyCount[1] = 1;
    G.supplyCount[2] = 1;

    printf("\tBoth Province cards and supply piles are not empty:\n");
    assertTrue(isGameOver(&G),0,&err_cnt);

    if(err_cnt != 0)
        printf("\nFailure - Not all test passed!\n");
    else
        printf("\nAll tests passed!\n");

    return 0;
}
