/* -----------------------------------------------------------------------
 * Card Test 3 of steward card
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
    int cardsInHand = 0;
    int discardNum = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    //, OG;

    printf ("TESTING stewardC():\n");
   
    memset(&G,23,sizeof(struct gameState));
    //memset(&OG,23,sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    //Copy original state
    //memcpy(&OG, &G, sizeof(struct gameState));
    
    printf("\tPlayer0 gains 2 cards:\n");
    choice1 = 1;
    cardsInHand = numHandCards(&G);
    cardEffect(steward, choice1, choice2, choice3, &G, hp, NULL);
    assertTrue(numHandCards(&G), cardsInHand+1, &err_cnt);

    printf("\tPlayer0 gains 2 coins:\n");
    choice1 = 2;
    G.coins = 5;
    cardEffect(steward, choice1, choice2, choice3, &G, hp, NULL);
    assertTrue(G.coins, 7, &err_cnt);
    
    printf("\tPlayer0 discards 2 cards:\n");
    choice1 = 0;
    discardNum = G.discardCount[0];
    cardEffect(steward, choice1, choice2, choice3, &G, hp, NULL);
    assertTrue(G.discardCount[0], discardNum+2, &err_cnt);

    if(err_cnt != 0)
        printf("\nFailure - Not all test passed!\n");
    else
        printf("\nAll tests passed!\n");

    return 0;
}
