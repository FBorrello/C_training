//Q1
void set_value(int **pp) {
    **pp = 42;
}

//Q2
int is_power_of_two(int n) {
    if (n == 0) return -1;
    
    int bits = sizeof(int) * 8;
    int leadingZero = 1;
    int ones_count = 0;

    for (int i = bits - 1; i >= 0; i--) {
        
        int bit = (n >> i) & 1;

        if (bit == 1 || !leadingZero) {
            leadingZero = 0;
            if (bit == 1) ones_count += 1;
        }
    }
    if (ones_count == 1) return 0;
    return -1;
}

//Q3
int sum_2d_array(int (*arr)[3], int rows) {
    int i, j, sum = 0;
    int *p_array = arr;
    
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < 3; j++)
        {
            sum += *p_array;
            p_array++;
        }
    }
    
    return sum;
}

//Q4
int count_alpha(const char *str) {
    int i = 0, count_alpha = 0;
    for (; str[i] != '\0'; i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z') count_alpha++;
    }
    return count_alpha;
}

//Q5
int* create_array(int n) {
    return (int*)malloc(sizeof(int) * n);
}

//Q8
void reverse_string(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;
    char temp;
    while (start < end)
    {
        temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}

void allocate_and_init(int **p, int value) {
    *p = malloc(sizeof(int));
    if (*p != NULL) {
        **p = value;
    }
}

float average(float *data, int size) {
    if (data == NULL || size <= 0)
    {
        printf("data pointer is NULL or size equal or less than 0");
        return 0;
    }
    
    int i, sum = 0;
    float *p_array = data;
    for (i = 0; i < size; i++)
    {
        sum += *p_array;
        *p_array++;
    }
    return (float) sum / size;
}