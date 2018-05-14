#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// fail counter variables
int cardEffectFails = 0;
int discardCardFails = 0;
int drawCardFails = 0;
int deckHandCountFails = 0;
int coinCountFails = 0;

// function to check the stewardCard
void checkStewardCard(int p, struct gameState *post) {
    int r,s,t,v,w,x;
    int choice;

    // game state variable to manually act on the functions actions
    struct gameState pre;

    // copy the passed in game state to pre
    memcpy(&pre,post,sizeof(struct gameState));
    int bonus = 0;

    for(choice=1;choice<4;choice++) {
        // call the card effect function with the steward card
        r = cardEffect(steward,choice,1,2,post,0,&bonus); //choice 1

        if(choice == 1) {

            // call draw card 2 times
            s = drawCard(p,&pre);
            t = drawCard(p,&pre);

            // call discardCard
            v = discardCard(0, p, &pre, 0);

            // get values of hand and deck counts
            int postHC = post->handCount[p];
            int postDC = post->deckCount[p];
            int preHC = pre.handCount[p];
            int preDC = pre.deckCount[p];

            // check if any drawcard failed
            if (s == -1 && pre.deckCount[p] != 0)
                drawCardFails++;
            if (t == -1 && pre.deckCount[p] != 0)
                drawCardFails++;

            // check if cardeffect or discardCard failed
            if (!(r == 0 && v == 0)) {
                if (r)
                    cardEffectFails++;
                if (v)
                    discardCardFails++;
            }

            // check if the hand and deck counts dont match up
            if (!(postHC == preHC && postDC == preDC))
                deckHandCountFails++;
        } else if (choice == 2) {
            
            if(post->coins != pre.coins+2)
                coinCountFails++;
            
        } else {
            // call discardCard
            v = discardCard(0, p, &pre, 1);
            w = discardCard(1, p, &pre, 1);
            x = discardCard(2, p, &pre, 0);

            int postHC = post->handCount[p];
            int postDC = post->deckCount[p];
            int preHC = pre.handCount[p];
            int preDC = pre.deckCount[p];
            
            //check if any discardCard failed
            if (v != 0 )
                discardCardFails++;
            if (w != 0 )
                discardCardFails++;
            if (x != 0 )
                discardCardFails++;
       
            //printf("postHC = %d, preHC = %d, postDC = %d, preDC = %d\n", postHC, preHC, postDC, preDC);
            // check if the hand and deck counts dont match up
            if (!(postHC == preHC-1 && postDC == preDC))
                deckHandCountFails++;
        }
    }
}

int main () {
    printf("***** RANDOM TEST *****\n");
    printf("Function: stewardCard()\n");
    printf("***********************\n");

    int iterations = 10000;
    int i, n, player;
    struct gameState G;
    srand(time(NULL)); //replace seed here

    // randomly initialized the game state
    for (n = 0; n < iterations; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        // randomly select appropriate values
        player = floor(Random() * MAX_PLAYERS);
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * (MAX_DECK-1));
        G.whoseTurn = player;
        // call the check function
        checkStewardCard(player,&G);
    }
    int totalFails = cardEffectFails + discardCardFails +
                        drawCardFails + deckHandCountFails +
                        coinCountFails;
    printf("\n***** RESULTS *****\n");
    printf("PASSED TESTS: %d\n",iterations - totalFails);
    printf("FAILED TESTS: %d\n",totalFails);

    if (totalFails == 0)
        printf ("***** PASSED RANDOM TEST *****\n\n");
    else {
        printf("\n***** FAILURE REPORT *****\n");
        printf("drawCard() failed: %d\n",drawCardFails);
        printf("cardEffect() failed: %d\n",cardEffectFails);
        printf("discardCard() failed: %d\n",discardCardFails);
        printf("coinCount() failed: %d\n",coinCountFails);
        printf("Hand/Deck Count mismatch: %d\n",deckHandCountFails);
        printf ("***** FAILED RANDOM TEST *****\n\n");
    }
    printf ("****** COVERAGE ******\n");
    return 0;
}
