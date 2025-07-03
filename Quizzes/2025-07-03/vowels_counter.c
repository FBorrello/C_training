#include <stdio.h>
#include <string.h>

#define MAX_STRING 50

int countStringVowels(char* string);
int countStringNotVowels(char* string);

int  main()
{
    char user_input[50];
    printf("Input a string: ");
    fgets(user_input, MAX_STRING, stdin);
    user_input[strcspn(user_input, "\n")] = '\0';
    
    int vowels_count = countStringVowels(user_input);
    printf("User input %s contains %d vowels.\n", user_input, vowels_count);

    int notVowels_count = countStringNotVowels(user_input);
    printf("User input %s contains %d not vowels chars.\n", user_input, notVowels_count);


    return 0;
}

int countStringVowels(char* string)
{
    int vowels_count = 0, i;
    for (i = 0; string[i] != '\0'; i++)
    {
        switch(string[i])
        {
            case 'a': case 'e': case 'i': case 'o': case 'u': case 'A': case 'E': case 'I': case 'O': case 'U':
                vowels_count++;
                break;
            default:
                break;
        }
    }

    return vowels_count;
}

int countStringNotVowels(char* string)
{
    int notVowels_count = 0, i;
    for (i = 0; string[i] != '\0'; i++)
    {
        switch(string[i])
        {
            case 'a': case 'e': case 'i': case 'o': case 'u': case 'A': case 'E': case 'I': case 'O': case 'U':
                break;
            default:
            notVowels_count++;
                break;
        }
    }

    return notVowels_count;
}