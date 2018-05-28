/* -----------------------------------------------------------------------
 * Card Test 1 of adventurer card
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
    int i, card;
    int seed = 1000;
    int err_cnt = 0;
    int numPlayer = 2;
    int player0 = 0;
    int player1 = 1;
    int tCountG = 0;
    int tCountOG = 0;
    int hp = 0;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int bonus = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, OG;

    printf ("TESTING adventurerC():\n");
   
    memset(&G,23,sizeof(struct gameState));
    memset(&OG,23,sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);

    //Copy original state
    memcpy(&OG, &G, sizeof(struct gameState));
    
    cardEffect(adventurer, choice1, choice2, choice3, &G, hp, &bonus);
    
    printf("\tPlayer0 gains 2 cards:\n");
    assertTrue(G.handCount[player0],OG.handCount[player0]+2,&err_cnt);
    
    //Check how much treasure is gained
    for (i = 0; i < G.handCount[player0]; i++) {
        card = G.hand[player0][i];
        if (card == copper || card == silver || card == gold)
            tCountG++;
    }
    
    //Check default treasure count
    for (i = 0; i < OG.handCount[player0]; i++) {
        card = OG.hand[player0][i];
        if (card == copper || card == silver || card == gold)
            tCountOG++;
    }
    
    printf("\tPlayer 0 gains 2 treasure cards:\n");
    assertTrue(tCountOG+2,tCountG,&err_cnt);
    
    printf("\tNo change to victory card piles:\n");
    printf("\tProvince Pile\n");
    assertTrue(G.supplyCount[province],OG.supplyCount[province],&err_cnt);
    printf("\tDuchy Pile\n");
    assertTrue(G.supplyCount[duchy],OG.supplyCount[duchy],&err_cnt);
    printf("\tEstate Pile\n");
    assertTrue(G.supplyCount[estate],OG.supplyCount[estate],&err_cnt);
    
    printf("\tNo change to kingdom card piles:\n");
    for (i = 0; i < 10; i++) {
        printf("\tChecking card piles...\n");
        assertTrue(G.supplyCount[k[i]],OG.supplyCount[k[i]],&err_cnt);
    }
    
    printf("\tPlayer1 was not affected:\n");
    printf("\tHand Count\n");
    assertTrue(G.handCount[player1],OG.handCount[player1],&err_cnt);
    printf("\tDeck Count\n");
    assertTrue(G.deckCount[player1],OG.deckCount[player1],&err_cnt);

    if(err_cnt != 0)
        printf("\nFailure - Not all test passed!\n");
    else
        printf("\nAll tests passed!\n");

    return 0;
}
