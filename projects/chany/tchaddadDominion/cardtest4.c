/* -----------------------------------------------------------------------
 * Card Test 4 of embargo card
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

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
    int err_cnt = 0;
    int numPlayer = 2;
    int hp = 0;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int embCoins = 0;
    int discardNum = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    //, OG;

    printf ("TESTING embargoC():\n");
   
    memset(&G,23,sizeof(struct gameState));
    //memset(&OG,23,sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    //Copy original state
    //memcpy(&OG, &G, sizeof(struct gameState));
    
    G.coins = 5;
    G.supplyCount[choice1] = 1;
    embCoins = G.embargoTokens[choice1];
    discardNum = G.discardCount[0];
    printf("\tSelected pile is not in play:\n");
    cardEffect(embargo, choice1, choice2, choice3, &G, hp, NULL);
    printf("\tPlayer0 gains 2 coins:\n");
    assertTrue(G.coins, 7, &err_cnt);
    
    printf("\tPlayer0 adds embargo token to supply pile:\n");
    assertTrue(G.embargoTokens[choice1], embCoins+2, &err_cnt);

    printf("\tPlayer0 discards card after:\n");
    assertTrue(G.discardCount[0], discardNum+1, &err_cnt);

    printf("\tSelected pile is in play:\n");
    G.coins = 5;
    G.supplyCount[choice1] = -1;
    discardNum = G.discardCount[0];
    cardEffect(embargo, choice1, choice2, choice3, &G, hp, NULL);

    printf("\tPlayer0 gains 2 coins:\n");
    assertTrue(G.coins, 7, &err_cnt);
    printf("\tPlayer0 adds embargo token to supply pile:\n");
    assertTrue(G.embargoTokens[choice1], embCoins, &err_cnt);
    printf("\tPlayer0 discards card after:\n");
    assertTrue(G.discardCount[0], discardNum, &err_cnt);

    if(err_cnt != 0)
        printf("\nFailure - Not all test passed!\n");
    else
        printf("\nAll tests passed!\n");

    return 0;
}
