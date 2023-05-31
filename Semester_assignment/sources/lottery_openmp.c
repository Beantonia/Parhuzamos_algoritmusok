#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void runProgram(FILE* file, int number, int lower_limit, int upper_limit) {
    int i, j;
    int match_count = 0;

    clock_t start_time, end_time;
    double execution_time;

    // Initialize the random generator
    srand(time(NULL));

     // Start measuring execution time
    start_time = clock();

    // Generate the first array
    int* array1 = (int*)malloc(number * sizeof(int));
    #pragma omp parallel for private(i)
    for (i = 0; i < number; i++) {
        int num;
        do {
            num = (rand() % (upper_limit - lower_limit + 1)) + lower_limit;
        } while (i > 0 && num == array1[i - 1]);

        array1[i] = num;
        printf("%d ",array1[i]);
    }

    // Generate the second array
    int* array2 = (int*)malloc(number * sizeof(int));
    #pragma omp parallel for private(i)
    for (i = 0; i < number; i++) {
        int num;
        do {
            num = (rand() % (upper_limit - lower_limit + 1)) + lower_limit;
        } while (i > 0 && num == array2[i - 1]);

        array2[i] = num;
        printf("%d ",array2[i]);
    }

    // Search for matching numbers
    #pragma omp parallel for private(i, j) reduction(+:match_count)
    for (i = 0; i < number; i++) {
        for (j = 0; j < number; j++) {
            if (array1[i] == array2[j]) {
                match_count++;
                break;
            }
        }
    }

    // End measuring execution time
    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Write results to file
    int time = 1000*execution_time;
    fprintf(file, "%d %d\n", number, time);

    // Free dynamically allocated arrays
    free(array1);
    free(array2);
}

int main() {
    const char* filename = "lottery_openmp.txt";
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for writing.\n", filename);
        return 1;
    }

    int lower_limit = 0;
    int upper_limit = 1000;

    // Run the program 1000 times with increasing number of generated numbers
    for (int number = 10; number <= 1000; number += 10) {
        runProgram(file, number, lower_limit, upper_limit);
    }

    fclose(file);

    printf("\nResults have been saved to '%s'.\n", filename);

    return 0;
}
