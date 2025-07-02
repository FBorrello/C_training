/*
Task: Write a C program that prints a pattern of numbers based on user input n (1 ≤ n ≤ 9). 
The pattern should follow this logic: for each row i (1 to n), print numbers from 1 to i, but skip numbers divisible by 3. 
If no numbers are printed in a row, print "Skip". For example, for n = 4:

1
1 2
Skip
1 2 4

Requirements:

Use loops and control structures (no arrays or pointers).
Handle invalid input (print "Invalid" if n < 1 or n > 9).

Example Output:
Enter n: 4
1
1 2
Skip
1 2 4
Enter n: 0
Invalid
*/

#include <stdio.h>

int main()
{
    int user_entry;
    int result;
    do{
        printf("Enter n: ");
        result = scanf("%d", &user_entry);
        if (result != 1)
        {
            printf("Error: Please enter a valid integer.\n");
            while (getchar() != '\n');
        }
        else if (user_entry < 1 || 9 < user_entry)
        {
            printf("Invalid\n");
            return 1;
        }
    } while (result != 1 || (user_entry < 1 || 9 < user_entry));

    int i, j;
    for (i = 1; i <= user_entry; i++)
    {
        if (i % 3 == 0)
        {
            printf("Skip\n");
        } else {
            for (j = 1; j <= i; j++)
            {
                if (j % 3 == 0) continue;
                printf("%d ", j);
            }
            printf("\n");
        }
    }
    
    return 0;
}