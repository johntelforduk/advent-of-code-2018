/*
 * Solutiuon to Advent of Code Day 9 "Marble Mania" - https://adventofcode.com/2018/day/9
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define testing false               // 'true' sends some trace to stdout.

#define num_players 459             // Number of players in this round of the game.
#define last_marble 71320           // Value of the last marble that will be played.

int circle[last_marble + 1];
int current_player=0;               // Number of the player who is about to place a marble.
int circle_size=0;                  // Number of marbles currently in the circle.
int player_score[num_players + 1];  // player_score[1] is score of Player 1, etc.  
int current_marble=0;               // Position in the circle of the marble that is designated the current marble.
int lowest_remaining_marble=0;


// Print out current set of marbles in the circle.
void print_circle(void)
{        
    int i=0;

    printf("[%d] ", current_player);
    for (i=0; i<circle_size; i++)
        if (i == current_marble)
            printf("(%d) ", circle[i]);          // Current marble should be printed with a brackets around it.
        else printf("%d ", circle[i]);               
    printf("\n");
}  


// Insert a marble into the circle.
void insert(int insert_place)   // Location that the insert will be done at.
                                // Insert place "1" actually means insert between places "0" and "1".
{
    int i=0;
    
    /* Case where there are existing marble(s) to the right (clockwise) of the insert place.
     * 
     * circle_size      2
     * circle[]        [0]   [1]
     * Marbles          0    (1)
     *
     * insert(1)
     * 
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles          0    (2)    1
     * current_marble   1
     */
    
    // Does this insert require us to shuffle some other stones to the right (clockwise)?
    if (insert_place<circle_size)
    {
        circle_size++;                               // Grow the circle size to make space for the new marble.
        
        for (i=circle_size; i>insert_place; i--)    // Shuffle is from right to left.
            circle[i]=circle[i-1];
    }


    /* Case where insert place is to the right (clockwise) of all existing marbles.
     * 
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles          0    (2)    1
     *
     * insert(3)
     * 
     * circle_size      4
     * circle[]        [0]   [1]   [2]   [3]
     * Marbles          0     2     1    (3)
     * current_marble   3
     */
    else
        circle_size++;      // Grow the circle size to make space for the new marble.

    circle[insert_place]=lowest_remaining_marble;   // Put the new marble into it's place.
    current_marble=insert_place;                    // This newly inserted marble is designated as the current marble.

    lowest_remaining_marble++;                      // Marble used up, so increment LRM.
}

// Move the current marble pointer one place to the right (clockwise).
void clockwise_1(void)
{
    /*
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles          0    (2)    1
     * current_marble   1
     * 
     * clockwise_1()
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles          0     2    (1)
     * current_marble   2
     */

    if (current_marble < (circle_size - 1)) 
        current_marble++;
        
    /*
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles          0     2    (1)
     * current_marble   2
     * 
     * clockwise_1()
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles         (0)    2     1
     * current_marble   0
     */

    else current_marble=0;
}

        
// Move the current marble pointer right (clockwise) by parm number of places.
void clockwise(int n)
{
    int i=0;
    
    for (i=0; i<n; i++)
        clockwise_1();
}


// Move the current marble pointer one place to the left (counter-clockwise).
void counter_clockwise_1(void)
{
    /*
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles          0    (2)    1
     * current_marble   1
     * 
     * counter_clockwise_1()
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles         (0)    2     1
     * current_marble   0
     */

    if (current_marble > 0) 
        current_marble--;
        
    /*
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles         (0)    2     1
     * current_marble   0
     * 
     * clockwise_1()
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles          0     2     1
     * current_marble   0
     */

    else current_marble=circle_size - 1;
}

        
// Move the current marble pointer right (clockwise) by parm number of places.
void counter_clockwise(int n)
{
    int i=0;
    
    for (i=0; i<n; i++)
        counter_clockwise_1();
}


// Take marble at current marble location.
void take_marble(void)
{
    int i=0;

    player_score[current_player]=player_score[current_player] + circle[current_marble];    // Player takes the current, and adds it to his score.
    
    /*
     * circle_size      4
     * circle[]        [0]   [1]   [2]   [3]
     * Marbles          3    (2)    1     0
     * current_marble   1
     * 
     * take_marble()
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles          3    (1)    0
     * current_marble   1
     */
         
    if (current_marble < (circle_size - 1))
    
    // Shuffle marbles leftward.
    for (i=current_marble; i<(circle_size -1); i++)
        circle[i]=circle[i+1];

    /*
     * circle_size      3
     * circle[]        [0]   [1]   [2]
     * Marbles          3     1    (0)
     * current_marble   2
     * 
     * take_marble()
     * circle_size      2
     * circle[]        [0]   [1]
     * Marbles         (3)    1
     * current_marble   0
     */
 
    else current_marble=0;
     
    // A marble has been taken so reduce the circle size.
    circle_size--;

    lowest_remaining_marble++;
}


int main()
{
    int high_score=0;
    int i=0;
    
    // Set scores to zero.
    for (i=0; i<num_players; i++)
    {
        player_score[i]=0;
        
        if (testing)
            printf("player_score[%d]=%d\n", i, player_score[i]);
    }
    
    insert(current_marble);
    if (testing)
        print_circle();
    
    while (lowest_remaining_marble <= (last_marble))
    {
        current_player++;                           // Next player's turn.
        if (current_player >= (num_players+1))
            current_player=1;

        if ((lowest_remaining_marble % 23) ==0)     // Special rule if the marble thatis about to be placed is a multiple of 23.
        {
            player_score[current_player]=player_score[current_player] + lowest_remaining_marble;    // Player keeps this marble.
            
            // Move the Current Marble pointer 7 places counter-clockwise.
            counter_clockwise(7);
            
            // Take the current marble.
            take_marble();
        }
        else
        {                                           // otherwise... follow the normal rule.
            clockwise(2);                           // Move the Current Marble pointer 2 places clockwise.
            insert(current_marble);
        }
        
        if (testing)
            print_circle();
    }
    
    // Game over. Find the highest score.
    for (i=1; i<num_players; i++)
        if (player_score[i] > high_score)
            high_score=player_score[i];
  
    printf("high_score=%d\n", high_score);
  
 	return 0;
}


  
  
