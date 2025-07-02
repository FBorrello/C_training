/*
Print a triangular pattern for input n (1 ≤ n ≤ 10) 
where each row i contains numbers from 1 to i with exactly two 1s in their binary representation (e.g., 3 = 11, 5 = 101, 6 = 110). 
Print "None" for empty rows. Handle invalid input (n < 1 or n > 10) by printing "Invalid" and exiting. 
Use only loops, control structures, and bitwise operations.
*/
#include <stdio.h>

/*
@brief This function  check if the binary representation of the integer past as argument contains 2 ones.

@param number integer.
@return 1 if the binaty representation of the numver contains two ones.
*/
int containsTwoOnes(int number);

int main()
{
    // Require user input
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
        else if (user_entry < 1 || 10 < user_entry)
        {
            printf("Invalid\n");
            return 1;
        }
    } while (result != 1 || (user_entry < 1 || 10 < user_entry));

    // Iterate each row of the triangular pattern and check if the condition is met before printing the number
    int i, j, twoOnesFound = 0;
    for (i = 1; i <= user_entry; i++)
    {
        for (j = 1; j <= i; j++)
        {
            if (containsTwoOnes(j) && !twoOnesFound) twoOnesFound = 1; 
            if (twoOnesFound) printf("%d ", j);
        }
        
        if (!twoOnesFound)
        {
            printf("None\n");
        } else {
            printf("\n");
        }

        twoOnesFound = 0;
    }
    
    return 0;
}

int containsTwoOnes(int number)
{   
    if (number == 0) return 0;

    // Size of int in bits (typically 32, but can vary)
    int bits = sizeof(int) * 8; // 8 bits per byte
    int leadingZero = 1; // Flag to skip leading zeros
    int ones_count = 0;

    // Loop from most significant bit to least significant bit
    for (int i = bits - 1; i >= 0; i--) {
        // Extract the i-th bit using right shift and AND
        int bit = (number >> i) & 1;

        // Only print after encountering the first 1 to skip leading zeros
        if (bit == 1 || !leadingZero) {
            leadingZero = 0; // Start printing all bits after first 1
            if (bit == 1) ones_count += 1;
        }
    }
    if (ones_count == 2) return 1;
    return 0;
}