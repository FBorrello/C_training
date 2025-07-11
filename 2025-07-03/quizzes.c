#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Quiz 1: Pointers - Pointer to Pointer
void quiz1() {
    int x = 42;
    int *p = &x;
    int **pp = &p;
    **pp = 99;
    printf("%d", x);
}
// Options: A) 42 B) 99 C) 0 D) Undefined

// Quiz 2: Strings - String Reversal
void quiz2() {
    char str[] = "IoT";
    char *start = str;
    char *end = str + strlen(str) - 1;
    char temp;
    while (start < end) {
        temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
    printf("%s", str);
}
// Options: A) IoT B) ToI C) TIo D) Undefined

// Quiz 3: Dynamic Memory Allocation - Array Allocation
void quiz3() {
    int *arr = (int *)malloc(3 * sizeof(int));
    if (arr == NULL) {
        printf("NULL");
        return;
    }
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    printf("%d", arr[1]);
    free(arr);
}
// Options: A) 1 B) 2 C) 3 D) NULL

// Quiz 4: Pointers - Array of Pointers
void quiz4() {
    int a = 10, b = 20, c = 30;
    int *arr[3] = {&a, &b, &c};
    printf("%d", *arr[1] + *arr[2]);
}
// Options: A) 30 B) 50 C) 60 D) Undefined

// Quiz 5: Strings - Character Counting
void quiz5() {
    char str[] = "AIoT2025!";
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
            count++;
        }
    }
    printf("%d", count);
}
// Options: A) 6 B) 7 C) 8 D) 9

// Quiz 6: Arrays - 2D Array Sum
void quiz6() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int sum = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            sum += arr[i][j];
        }
    }
    printf("%d", sum);
}
// Options: A) 12 B) 15 C) 18 D) 21

// Quiz 7: Pointers - Function Pointer
void quiz7() {
    int add(int a, int b) { return a + b; }
    int (*func)(int, int) = add;
    printf("%d", func(5, 3));
}
// Options: A) 5 B) 3 C) 8 D) Undefined

// Quiz 8: Dynamic Memory Allocation - Struct Allocation
void quiz8() {
    struct Sensor { int id; float value; };
    struct Sensor *s = (struct Sensor *)malloc(sizeof(struct Sensor));
    if (s == NULL) {
        printf("NULL");
        return;
    }
    s->id = 1;
    s->value = 25.5;
    printf("%.1f", s->value);
    free(s);
}
// Options: A) 1.0 B) 25.5 C) NULL D) Undefined

// Quiz 9: Control Structures - Bit Manipulation
void quiz9() {
    unsigned int x = 0x0F;
    unsigned int y = 0xF0;
    printf("%X", x | y);
}
// Options: A) 0F B) F0 C) FF D) 00

// Quiz 10: Pointers - Null Pointer Check
void quiz10() {
    int *p = NULL;
    int x = 10;
    if (p == NULL) {
        p = &x;
    }
    printf("%d", *p);
}
// Options: A) 0 B) 10 C) NULL D) Undefined

int main()
{
    quiz2();
    return 0;
}