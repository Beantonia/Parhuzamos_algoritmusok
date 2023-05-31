#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void runProgram(FILE* file, int num, int lower_limit, int upper_limit) {
    clock_t start_time, end_time;
    double execution_time;
    int sum = 0;

    // Start measuring time
    start_time = clock();

    // Generate random numbers and calculate sum
    srand(time(NULL));
    for (int i = 0; i < num; i++) {
        int random_number = (rand() % (upper_limit - lower_limit + 1)) + lower_limit;
        sum += random_number;
        printf("%d ",random_number);
    }

    // Calculate average
    double average = (double)sum / num;

    // End measuring time
    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Write results to file
    int time = execution_time*1000;
    fprintf(file, "%d %d\n", num, time);
}

int main() {
    const char* filename = "average_of_random_numbers.txt";
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for writing.\n", filename);
        return 1;
    }

    int num = 0;
    int lower_limit = 0;
    int upper_limit = 1000;

    // Run the program 1000 times with different number of random numbers
    for (int i = 0; i < 100; i++) {
        num += 10;

        runProgram(file, num, lower_limit, upper_limit);
    }

    fclose(file);

    printf("Results have been saved to '%s'.\n", filename);

    return 0;
}
