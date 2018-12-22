/*
 * Solutiuon to Advent of Code Day 11 "Chronal Charge" - https://adventofcode.com/2018/day/11
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define width 300
#define height 300

#define serial_number 7315

int grid[width + 1][height + 1];     // +1s are because grid coordinates are from 1 to 300 (not 0 to 299).

int x=0;
int y=0;

int i=0;
int j=0;

int rack_id=0;
int power_level=0;

int square_size=1;

int best_power=INT_MIN;
int best_x=0;
int best_y=0;
int best_square_size=0;
int this_power=0;

int main()
{
    // Calculate the power level for every coordinatein the grid.    
    for (y=1; y <= height; y++)
        for (x=1; x <= width; x++)
        {
            // "Find the fuel cell's rack ID, which is its X coordinate plus 10."
            rack_id = x + 10;

            // "Begin with a power level of the rack ID times the Y coordinate."
            power_level = rack_id * y;
            
            // "Increase the power level by the value of the grid serial number (your puzzle input)."
            power_level = power_level + serial_number;
            
            // "Set the power level to itself multiplied by the rack ID."
            power_level = power_level * rack_id; 

            // "Keep only the hundreds digit of the power level (so 12345 becomes 3; numbers with no hundreds digit become 0)."
            if (power_level < 100)
                power_level = 0;
            else power_level = (power_level / 100) % 10;        
            
            // "Subtract 5 from the power level."
            power_level = power_level - 5;
            
            grid[x][y] = power_level;
        }
    
    // Try every possible square size.
    for (square_size=1; square_size <= width; square_size++)
    {
        printf("square_size=%d\n", square_size);
        
        // Try every possible top left hand corner.
        for (y=1; y <= (height - square_size +1); y++)
            for (x=1; x <= (width - square_size +1); x++)
            {
                // Add up the total power for all fuel cells in this square. 
                this_power = 0;
                
                for (j=0; j<square_size; j++)
                    for (i=0; i<square_size; i++)
                        this_power = this_power + grid[x + i][y + j];
               
                // Is this the best sqare so far?
                if (this_power > best_power)
                {
                    best_power = this_power;
                    
                    best_x = x;
                    best_y = y;
                    best_square_size = square_size;
                }
            
            }
    }
 
    printf("best_x=%d   best_y=%d   best_square_size=%d\n", best_x, best_y, best_square_size);
    
	return 0;
}
