/*
 * Solutions to Part 1 and Part 2 of this problem https://adventofcode.com/2018/day/8
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define testing false             // 'true' loads a smaller puzzle input file, and send some traces to stdout.

#define max_child_nodes 100
#define max_metadata_values 100

int sum_node_metadata(void);
int sum_node_value(void);

FILE * fp;
int rv=0;


int main()
{
    if (testing)
        fp = fopen("test.txt", "r");
    else fp = fopen("input.txt", "r");
  
    if (fp == NULL)
        exit(EXIT_FAILURE);

    printf("sum_node_metadata=%d\n", sum_node_metadata());

    rewind(fp);                                         // Let's re-process the file from the start.
    printf("sum_node_value=%d\n", sum_node_value());

    fclose(fp);
	return 0;
}

int sum_node_metadata(void)
{
    int num_child_nodes=0;
    int num_metadata_entries=0;

    int metadata_entry=0;
    int metadata_sum=0;

    int i=0;
    
    rv = fscanf(fp, "%d %d", &num_child_nodes, &num_metadata_entries);   // The header is always these 2 numbers.
    if (rv==EOF)
        exit(EXIT_FAILURE);
    
    if (testing)
        printf("num_child_nodes=%d    num_metadata_entries=%d\n", num_child_nodes, num_metadata_entries);
    
    while (i<num_child_nodes)
    {
        metadata_sum = metadata_sum + sum_node_metadata();     // Recursive call to process however many child nodes there are.
        i++;
    }
        
    for (i=0;i<num_metadata_entries;i++)
    {
        rv = fscanf(fp, " %d", &metadata_entry);
        if (rv==EOF)
            exit(EXIT_FAILURE);
        
        metadata_sum=metadata_sum + metadata_entry;
    }

    return (metadata_sum);
}


int sum_node_value(void)
{
    int num_child_nodes=0;
    int num_metadata_entries=0;

    int child_value[max_child_nodes];
    int metadata_value[max_metadata_values];
    
    int metadata_entry=0;
    int metadata_sum=0;

    int node_value=0;

    int i=0;
    
    rv = fscanf(fp, "%d %d", &num_child_nodes, &num_metadata_entries);   // The header is always these first 2 numbers.
    if (rv==EOF)
        exit(EXIT_FAILURE);
    
    while (i<num_child_nodes)               // Store the value of each child in an array.
    {
        child_value[i]=sum_node_value();    // Recursive call to process however many child nodes there are.
        i++;
    }
        
    for (i=0;i<num_metadata_entries;i++)
    {
        rv = fscanf(fp, " %d", &metadata_entry);
        if (rv==EOF)
           exit(EXIT_FAILURE);
        
        metadata_sum=metadata_sum + metadata_entry;
        metadata_value[i]=metadata_entry;               // Store each metadata entry in an array.
    }

    if (num_child_nodes==0)         // If no child nodes, return sum of its metadata entries.
        node_value=metadata_sum;
    else                            // If there are child nodes, do the index lookup.
    {
        if (testing)
        {
            printf("num_child_nodes=%d\n", num_child_nodes);
            for (i=0;i<num_child_nodes;i++)
                printf("i=%d   child_value[i]=%d\n",i,child_value[i]);
                
            printf("num_metadata_entries=%d\n", num_metadata_entries);
            for (i=0;i<num_metadata_entries;i++)
                printf("i=%d   metadata_value[i]=%d\n",i, metadata_value[i]);
        }

        for (i=0;i<num_metadata_entries;i++)
        {
            if (testing)
                printf("i=%d   metadata_value[i]=%d    num_child_nodes=%d\n", i, metadata_value[i], num_child_nodes);
            
            if ((metadata_value[i]) <= num_child_nodes)
                node_value=node_value + child_value[metadata_value[i]-1];   // Off by 1, for example index=1, should look up position [0] in array.
        }     
    }
    if(testing)
        printf("returning %d\n\n", node_value);
    
    return(node_value);
}