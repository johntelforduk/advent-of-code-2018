/*
 * Solutiuon to Advent of Code Day 10 "The Stars Align" - https://adventofcode.com/2018/day/10
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define testing false               // 'true' reads from test file, and sends some trace to stdout.
#define max_stars 400
#define buff_sz 10                  // Coordinates of stars, their volocities and size of star field are all stored in a rotating buffer.

int x[max_stars] [buff_sz];         // Co ordinates of each star.
int y[max_stars] [buff_sz];

int xv[max_stars];                  // Velocity of each star.
int yv[max_stars];

int num_coords=0;

int buff_pos=0;                     // Pointer to current position in buffer.
int prev_buff_pos=0;

int min_x[buff_sz];
int min_y[buff_sz];
int max_x[buff_sz];
int max_y[buff_sz];

int width[buff_sz];
int height[buff_sz];
int done=false;


FILE * fp;

int secs=0;                         // Number of seconds elapsed.

int i=0;                            // General purpose counters.
int j=0;
int k=0;

int star_found=false;

int main()
{
    // Read co-ords from file into array.
    
    if (testing)
    fp = fopen("test.txt", "r");
        else fp = fopen("input.txt", "r");

    if (fp == NULL)
      exit(EXIT_FAILURE);

      
    while (fscanf(fp, "position=<%d, %d> velocity=<%d, %d>\n", &x[num_coords][buff_pos], &y[num_coords][buff_pos], &xv[num_coords], &yv[num_coords]) != EOF)
    {
        if (testing)
            printf("x=%d   y=%d   xv=%d   yv=%d\n", x[num_coords][buff_pos], y[num_coords][buff_pos], xv[num_coords], yv[num_coords]);
    
        num_coords++;
        if (num_coords > max_stars)
            exit(EXIT_FAILURE);
    }


    while (!done)
    {
        // Figure out width and height of current star pattern.
        
        // Set max and mins to extremes. This mean 1st coord checked will beat it.
        min_x[buff_pos]=INT_MAX;
        max_x[buff_pos]=INT_MIN;
        min_y[buff_pos]=INT_MAX;
        max_y[buff_pos]=INT_MIN;
        
        for (i=0; i<num_coords; i++)
        {
            if (x[i][buff_pos] < min_x[buff_pos])
                min_x[buff_pos]=x[i][buff_pos];
            if (x[i][buff_pos] > max_x[buff_pos])
                max_x[buff_pos]=x[i][buff_pos];
                
            if (y[i][buff_pos] < min_y[buff_pos])
                min_y[buff_pos]=y[i][buff_pos];
            if (y[i][buff_pos] > max_y[buff_pos])
                max_y[buff_pos]=y[i][buff_pos];        
        }
        
        width[buff_pos] = max_x[buff_pos] - min_x[buff_pos] + 1;            // Need the +1... (gatepost error).
        height[buff_pos] = max_y[buff_pos] - min_y[buff_pos] + 1;
        
        if (testing)
            printf("secs=%d    width=%d    height=%d\n", secs, width[buff_pos], height[buff_pos]);
          
          
        // Except for the first second of time (when there is no previous position), check size of star field compared to previous second.  
        if (secs>0)
        {
            // First idea was to see if area of star gield rectangle is bigger than last time? If so, then the stars have started to diverge again.
            // Code...
            //    if ( (width[buff_pos] * height[buff_pos]) > (width[prev_buff_pos] * height[prev_buff_pos]) )
            // But this gave false positives.
            // So instead just look to see if width alone has increased.

              if ( width[buff_pos] > width[prev_buff_pos])
                done=true;
        }
  
        if (!done)
        {
            // Move stars to their new location.
        
            prev_buff_pos = buff_pos;

            secs++;
            buff_pos=secs % buff_sz; 
            
            for (i=0; i<num_coords; i++)
            {
                x[i][buff_pos] = x[i][prev_buff_pos] + xv[i];       // Add velocity numbers to previous position.
                y[i][buff_pos] = y[i][prev_buff_pos] + yv[i];
            }        
        }
    }
    
    
    // Print out the previous star pattern.
    printf("After %d secs.\n", (secs - 1));
    
    for (j=min_y[prev_buff_pos]; j<=max_y[prev_buff_pos]; j++)          // Vertical first.
    {
        for (i=min_x[prev_buff_pos]; i<=max_x[prev_buff_pos]; i++)      // Then horizontal.
        {
            // Is there at least 1 star in this position?
            star_found=false;
            
            for (k=0; k < num_coords; k++)
                if (x[k][prev_buff_pos] == i && y[k][prev_buff_pos]==j)
                    star_found = true;
            
            if (star_found)
                printf("#");
            else printf(".");
        }
        printf("\n");
    }

	return 0;
}
