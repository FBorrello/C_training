#include <stdio.h>
#define PI 3.14159
#ifdef DEBUG
#define LOG(msg) printf("Debug: %s\n", msg)
#else
#define LOG(msg)
#endif
int main() {
    LOG("Starting program");
    float radius = 5.0;
    printf("Area of circle: %.2f\n", PI * radius * radius);
    return 0;
}

/*
gcc -DDEBUG circle.c -o circle && ./circle
Debug: Starting program
Area of circle: 78.54
*/

/*
cc circle.c -o circle && ./circle
Area of circle: 78.54
*/