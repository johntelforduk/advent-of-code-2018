/*
 * Solution to Part 1 & Part 2 of https://adventofcode.com/2018/day/3
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define testing false       // 'true' loads a smaller test file, and sends some trace to stdout.

#define fabric_width 1000
#define fabric_height 1000

int main(void)
{
    FILE * fp;
 
    int claim=0;
    int from_left=0;
    int from_top=0;
    int width=0;
    int height=0;
  
    int i=0;
    int j=0;
    
    int two_or_more=0;

    int uncontested=false;

    int *fabric = (int *) calloc(fabric_width * fabric_height, sizeof(int));   // int fabric[fabric_width][fabric_height];
      
    if (testing)
    fp = fopen("test.txt", "r");
        else fp = fopen("input.txt", "r");
  
    if (fp == NULL)
      exit(EXIT_FAILURE);
      
    while (fscanf(fp, "#%d @ %d,%d: %dx%d\n",&claim,&from_left,&from_top,&width,&height) != EOF)
    {
        if (testing)
            printf("claim=%d  from_left=%d  from_top=%d  width=%d  height=%d\n",claim,from_left,from_top,width,height);

        // Check the claim doesn't go off the edge of the fabric.
        if (fabric_width <= (from_left+width)
            || fabric_height <= (from_top+height)) 
                exit(EXIT_FAILURE);
  
        for (i=from_top;i<=(from_top+height-1);i++)
            for (j=from_left;j<=(from_left+width-1);j++)
            {
                *(fabric + i*fabric_height + j)=*(fabric + i*fabric_height + j)+1;  //  fabric[j][i]++;
    
                if (*(fabric + i*fabric_height + j) ==2)     //                if (fabric[j][i] ==2)
                    two_or_more++;
            }
    }

    if (testing)
    {
        /* Print out the fabric */
        for (i=0;i<=10;i++)
        {
            for (j=0;j<=10;j++)
   
                if (*(fabric + i*fabric_height + j) == 0)       // (fabric[j][i]==0)
                    printf("0");
                else printf("%d", *(fabric + i*fabric_height + j));   // printf("%d",fabric[j][i]);
            
            printf("\n");
        }
    }
    
    printf("Two or more=%d\n",two_or_more);
    
    /* Look for an unchallenged claim */
    rewind(fp);
    
    while (fscanf(fp, "#%d @ %d,%d: %dx%d\n",&claim,&from_left,&from_top,&width,&height) != EOF)
    {
        // Assume the claim is uncontested at start.
        uncontested=true;
        
        for (i=from_top;i<=(from_top+height-1);i++)
            for (j=from_left;j<=(from_left+width-1);j++)
                 if (*(fabric + i*fabric_height + j) !=1)
                     uncontested=false;

        if (uncontested)
            printf("uncontested claim=%d  from_left=%d  from_top=%d  width=%d  height=%d\n",claim,from_left,from_top,width,height);
    }
    
    fclose(fp);
    return 0;
}