#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

void runProgram(FILE* file, int num, int lowerLimit, int upperLimit) {
    int primeCount = 0;
    int* randomNumbers = (int*)malloc(num * sizeof(int));

    // Generate random numbers
    clock_t start_time = clock();
    srand(start_time); // Seed the random number generator

    for (int i = 0; i < num; i++) {
        randomNumbers[i] = rand() % (upperLimit - lowerLimit + 1) + lowerLimit;
        printf("%d ", randomNumbers[i]);
        if (isPrime(randomNumbers[i])) {
            primeCount++;
        }
    }

    printf("Number of primes: %d", primeCount);

     clock_t end_time = clock();

    // Calculate execution time
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    // Write results to file
    int time = 1000*execution_time;
    fprintf(file, "%d %d\n", num, time);

    // Free allocated memory
    free(randomNumbers);
}

int main() {
    const char* filename = "primes.txt";
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for writing.\n", filename);
        return 1;
    }

    int lowerLimit = 0;
    int upperLimit = 1000;

    // Run the program 1000 times with increasing number of generated numbers
    for (int num = 10; num <= 1000; num += 10) {
        runProgram(file, num, lowerLimit, upperLimit);
    }

    fclose(file);

    printf("\nResults have been saved to '%s'.\n", filename);

    return 0;
}
