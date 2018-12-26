/*
 * Solutiuon to Part 1 of Advent of Code Day 12 "Subterranean Sustainability" - https://adventofcode.com/2018/day/12
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define testing true                    // If 'true' then read use test flie, and send trace to stdout.

#define generations 20
#define min_pot -(generations)          // Reason is that leftmost plant can only creep back 1 pot per generation.
#define max_pot 40 + generations

#define note_length 6                   // Example, "##### => #" has six chars of info.
#define max_notes 100   

int generation=0;

char pots[generations + 1][max_pot - min_pot + 1];     // +1 because pot '0' is a pot.
char notes[max_notes][note_length];

int num_notes=0;

int total_indices=0;

FILE *fp;


// Set all of the pots in the parm generation to enpty pots.
void empty_pots(int gen)
{
    int pot;
    for (pot=0; pot < (max_pot - min_pot + 1); pot++)
        pots[gen][pot] = '.';
}


// Send a printout of pots in parm generation to stdout.
void print_pots (int gen)
{
    int pot;
    
    if (gen < 10)           // This is to make print outs line up across 1 and 2 digit generations.
        printf(" ");
        
    printf("%d: ", gen);
    
    for (pot=0; pot < (max_pot - min_pot + 1); pot++)
        printf("%c", pots[gen][pot]);
        
    printf("\n");
}


int main()
{
    char a_char;
    int done=false;
    int pot=0;
    int i=0;
    
	if (testing)
        fp = fopen("test.txt", "r");
    else fp = fopen("input.txt", "r");
  
    if (fp == NULL)
      exit(EXIT_FAILURE);
    
    fscanf(fp, "initial state: ");      // Read some boiler plate from the input file.


    // Read initial state of pots into generation zero of the pots array.
    empty_pots(generation); 
    done=false;
    pot=0;
    
    while (!done)
    {
        if (fscanf(fp, "%c", &a_char) == 0)
            exit(EXIT_FAILURE);
        
        if (a_char == '\n')                     // New Line indicates end of initial state string.
            done=true;
        else
        {
            pots[generation][pot -min_pot] = a_char;
            pot++;
        }    
    }
    
    fscanf(fp, "\n");       // Read a blank line.
 
    // Read notes from file.
    num_notes=0;
    while (fscanf(fp, "%c%c%c%c%c => %c\n",
                &notes[num_notes][0],
                &notes[num_notes][1],
                &notes[num_notes][2],
                &notes[num_notes][3],
                &notes[num_notes][4],
                &notes[num_notes][5]
            ) != EOF)
        num_notes++;
 
    // Print out the notes.
    if (testing)
    {
        for (i=0; i < num_notes; i++)
            printf("%c%c%c%c%c => %c\n", 
                notes[i][0],
                notes[i][1],
                notes[i][2],
                notes[i][3],
                notes[i][4],
                notes[i][5]);
    }
   
    if (testing)
        print_pots(generation);
    
    for (generation=1; generation <= generations; generation++)
    {
        empty_pots(generation);                                 // Start by setting the current generation to all empty pots.
        

        // Consider each plant in turn, and see what rule applies to it.
        for (pot=2; pot < (max_pot - min_pot -1); pot++)        // Start at 2 as it is 3 positions right of 0. For example, a rule like "..#.. => #".
                                                                // And also stop 2 places less than end.
                
            // Consider each rule in turn. Start by assuming it matches the patter around current pot in previous generation.
            for (i=0; i < num_notes; i++)
                
                // If all of the 5 pots in previous generation match pattern of note, set this generation to result of the note.
                if (   pots[generation -1][pot - 2] == notes[i][0]
                    && pots[generation -1][pot - 1] == notes[i][1]
                    && pots[generation -1][pot - 0] == notes[i][2]
                    && pots[generation -1][pot + 1] == notes[i][3]
                    && pots[generation -1][pot + 2] == notes[i][4]
                    )
                        pots[generation][pot] = notes[i][5];          // Note position 5 is the result of the note.
                    
        if (testing)
            print_pots(generation);
    }
    generation--;           // For loop leaves generation 1 higher than last one.
  
    // "After 20 generations, what is the sum of the numbers of all pots which contain a plant?"
    total_indices=0;
    for (pot=0; pot < (max_pot - min_pot + 1); pot++)
        if (pots[generation][pot] == '#')
            total_indices = total_indices + pot + min_pot;
  
    printf("total_indices=%d\n", total_indices);
    
	return 0;
}
