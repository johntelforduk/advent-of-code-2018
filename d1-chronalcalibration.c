/*
 * Solutiuon to Advent of Code Day 1 "Chronal Calibration" - https://adventofcode.com/2018/day/1
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define testing false           // "true" reads from test file.
#define arr_size 1000000

FILE * fp;

int this_val;                   // Latest value read from file.
int curr_frequency=0;           // Total of all values.
 
int frequencies[arr_size];      // Array of frequencies seen so far.
int frequency_count=0;          // Current position in the array.
int done=false;                 // Flags that solution has been found.

int i=0;

int main()
{
    if (testing)
        fp = fopen("test.txt", "r");
    else fp = fopen("input.txt", "r");
    
    if (fp == NULL)
      exit(EXIT_FAILURE); 
 
    while (!done && frequency_count < arr_size)
    {
        while (!done && frequency_count < arr_size && fscanf(fp, "%d", &this_val)!=EOF)
        {
           frequencies[frequency_count] = curr_frequency;

            // Have we seen this frequency before?
            for (i=0; i < frequency_count; i++)
                if (curr_frequency == frequencies[i] && i != frequency_count)
                    done=true;
            if (!done)
            {
                // Get ready for next iteration.
                frequency_count++;
                curr_frequency += this_val;         // Increase current frequency by most recently read value from input file.
            }
        }

        if (!done)                                  // Go back to start of input file.
            rewind(fp);
    }

    if (done)
        printf("curr_frequency=%d\n", curr_frequency);
        
    if (frequency_count == arr_size)
        printf("Ran out of array size.");

    fclose(fp);
	return 0;
}
