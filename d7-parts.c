/*
 * A solution to Part 1 this problem https://adventofcode.com/2018/day/7
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define testing false   // 'true' loads a smaller puzzle input file.
#define max_steps 26
#define max_rules 150

int main()
{
    FILE * fp;
    int rules=0;

    char step[max_rules];
    char need[max_rules];

    char made[max_steps];
    int made_so_far=0;

    char i;
    int j=0;
    int k=0;
    int next_step_found=true;
    int skip=false;
    int step_done=false;

    if (testing)
        fp = fopen("test.txt", "r");
    else fp = fopen("input.txt", "r");
  
    if (fp == NULL)
        exit(EXIT_FAILURE);
  
    // Load rules into pair of arrays.
    while (fscanf(fp, "Step %c must be finished before step %c can begin.\n", &need[rules], &step[rules]) != EOF)
    {
        printf("Step %C    Need %C\n", step[rules], need[rules]);
        rules++;
        
        if (rules >= max_rules)
            exit(EXIT_FAILURE);
    }    
    fclose(fp);

    if (testing)
        printf("rules=%d\n", rules);
    do
    {
        i='A';                    // Try each Step from A to Z in order, and see if it iw ready to be the next step.
        next_step_found=false;    // This will be set to True when next step to be done is found.
        skip=false;               // Becomes True if the step we are trying cannot be the next step to be done.
        
        while (i<('A' + max_steps) && !next_step_found)
        {
            skip=true;     // Set to True of it's time to try the next Step.
            
            // Does this step need to be done at all?
            for (j=0; j<rules; j++)             // Check if this step is mentioned on either side of any rule.
                if (i==need[j] || i==step[j])
                    skip=false;

            if (!skip)
            {
                // Has it already been done?
                j=0;
                while (j<made_so_far && !skip)
                {
                    if (i == made[j])   // Is this step has been made, then skip consideration of making this step again.
                        skip=true;
                    j++;
                }
            }
            
            // Have the previous steps that are needed already made?
            if (!skip)
            {
                for (j=0; j<rules;j++)      // Check each rule.
                    if (step[j] == i)       // Does this rule relate to the STEP we are considering?
                    {
                        step_done=false;    // Assume the NEEDed step hasn't been done yet, until we find it in the list of steps made.
                    
                        k=0;
                        while (k<made_so_far && !step_done)    // Check if this needed step has been done yet.
                        {
                            if (need[j] == made[k])
                                step_done=true;
                            k++;
                        }
                        
                        if (!step_done)
                            skip=true;
                    }
            }
            
            if (skip)                   // If Skip is set to True, then try the next letter...
                i++;
            else next_step_found=true;  // ... otherwise, we've found the next step.
        }

        if (next_step_found)
        {
            printf("%c",i);

            // Record that step has been done.
            made[made_so_far]=i;
            made_so_far++;
        }
    } while (next_step_found);
    
    printf("\n");
    
	return 0;
}
