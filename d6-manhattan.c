/*
 * Solution to parts 1 and 2 of this puzzle https://adventofcode.com/2018/day/6
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define testing true    // 'true' loads a smaller puzzle file, and sends some trace to stdout.

#define max_co_ords 55
#define max_x 500
#define max_y 500

static int grid[max_x][max_y];

int x_cord[max_co_ords];
int y_cord[max_co_ords];

int main()
{
    FILE * fp;

    int x=0;
    int y=0;
    int co_ord_count=0;

    int i=0;

    int this_distance=0;
    int nearest_distance_so_far=9999;
    int nearest_tie=false;
    int nearest_co_ord=0;

    int this_area=0;
    int biggest_area=0;
    int this_area_infinite=false;
    
    int near_square_count=0;
    int this_square_total_dist=0;

    // Initialiase the grid to -1, which indiactes nobody owns the square.
    for (y=0;y<max_y;y++)
        for (x=0;x<max_x;x++)
            grid[x][y]=-1;

    if (testing)
        fp = fopen("test.txt", "r");
    else fp = fopen("input.txt", "r");
  
    if (fp == NULL)
        exit(EXIT_FAILURE);
  
    // Load co-ords into 2 arrays (1 for x, 1 for y). 
    while (fscanf(fp, "%d, %d\n", &x_cord[co_ord_count], &y_cord[co_ord_count]) != EOF)
    {
        if (testing)
            printf("letter=%c   x=%d   y=%d\n", ('A'+co_ord_count), x_cord[co_ord_count], y_cord[co_ord_count]);
      
        co_ord_count++;
        
        if (co_ord_count > max_co_ords)
            exit(EXIT_FAILURE);
    }
    fclose(fp);
        
    if (testing)
        printf("co_ord_count=%d\n", co_ord_count);   
   
    for (y=0;y<max_y;y++)
        for (x=0;x<max_x;x++)
        {
            nearest_distance_so_far=9999;         // Set to high value, so first letter will beat this.
            nearest_tie=false;
            
            for (i=0;i<co_ord_count;i++)
            {    
                this_distance=abs(x_cord[i] - x) + abs(y_cord[i] - y);    // Distance between (x,y) and co ordinates of i'th co-ordinate.
                
                if (this_distance < nearest_distance_so_far)   // This co-ordinate is a new winner - closer than any before.
                {
                    nearest_distance_so_far=this_distance;
                    nearest_co_ord=i;
                    nearest_tie=false;
                }
                
                else if (this_distance == nearest_distance_so_far)
                    nearest_tie=true;
            }
            
            if (!nearest_tie)
                grid[x][y]=nearest_co_ord;      // So, if there was a nearest tie, then the square stays as -1.
                
        }
    
    /* In test mode, print out 10x10 top-left corner of grid. */
    if (testing)
        for (y=0;y<10;y++)
        {
            for (x=0;x<10;x++)
                if (grid[x][y] == -1)                       // -1 indicates, no co-ordinate owns the square.
                    printf(".");
                else printf("%c", ('A' + grid[x][y]));      // 0='A', 1='B', etc.
            printf("\n");
        }    
    
    // Look for the co-ordinate with the biggest (non infinite) area.
    for (i=0;i<co_ord_count;i++)        // Test each co-ordinate number in turn.
    {
        this_area=0;                    // Reset area, and infinite flag for each co-ordinate.
        this_area_infinite=false;
        
        for (y=0;y<max_y;y++)
            for (x=0;x<max_x;x++)
                if (grid[x][y] == i)    // This square grid[x][y] contains the co-ordinate that we're testing. */
                {
                    if (x==0 || y==0 || x==(max_x - 1) || y==(max_y - 1))       // This co-ordinate is at the edge - hence it is infinite.
                        this_area_infinite=true;
                    else this_area++;                                           // Otherwise add this square to this co-ord's total area.
                }
        if (this_area > biggest_area  && !this_area_infinite)
            biggest_area = this_area;
    }

    printf("biggest_area=%d\n", biggest_area); 
   
    // Count squares with total distance of all co-ordinates near to that square.
    for (y=0;y<max_y;y++)
        for (x=0;x<max_x;x++)
        {
            this_square_total_dist=0;    // Reset total distance for this square.
            
            for (i=0;i<co_ord_count;i++)
                this_square_total_dist=this_square_total_dist + abs(x_cord[i] - x) + abs(y_cord[i] - y);

            // The puzzle wording gives these figures for max distance, for either test or real puzzle data.
            if (testing && this_square_total_dist < 32)
                near_square_count++;
                
            if (!testing && this_square_total_dist < 10000)
                near_square_count++;
        }
  
    printf("near_square_count=%d\n", near_square_count);
    
	return 0;
}
