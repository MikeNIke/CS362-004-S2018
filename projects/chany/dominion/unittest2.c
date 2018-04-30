/* -----------------------------------------------------------------------
 * Unit Test 2 of shuffle function
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

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
    int player = 0;
    int err_cnt = 0;
    int numPlayer = 2;
    int preShuffleCard;
    int postShuffleCard;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING shuffle():\n");

    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    G.deckCount[player] = 0;
    printf("\tPlayer deck count is 0\n");
    assertTrue(shuffle(player,&G),-1, &err_cnt);

    printf("\tPlayer deck count is 8 before and after shuffle\n");
    G.deckCount[player] = 8;
    shuffle(player,&G);
    assertTrue(G.deckCount[player], 8, &err_cnt);

    printf("\tCards are shuffled\n");
    preShuffleCard = G.deck[player][0];
    shuffle(player,&G);
    postShuffleCard = G.deck[player][0];
    if (preShuffleCard != postShuffleCard) {
        assertTrue(1,1, &err_cnt);
    } else {
        assertTrue(0,1, &err_cnt);
    }

    if(err_cnt != 0)
        printf("\nFailure - Not all test passed!\n");
    else
        printf("\nAll tests passed!\n");

    return 0;
}
