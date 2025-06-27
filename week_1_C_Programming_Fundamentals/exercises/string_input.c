#include <stdio.h>
#include <string.h>
#define MAX_NAME 50
int main() {
    char name1[MAX_NAME], name2[MAX_NAME];
    printf("Enter name with scanf: ");
    scanf("%s", name1);
    while (getchar() != '\n'); // Clear buffer
    printf("Enter name with fgets: ");
    fgets(name2, MAX_NAME, stdin);
    name2[strcspn(name2, "\n")] = '\0'; // Remove newline
    printf("scanf result: %s\n", name1);
    printf("fgets result: %s\n", name2);
    return 0;
}