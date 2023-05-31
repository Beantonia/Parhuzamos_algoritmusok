#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

typedef struct {
    int start;
    int end;
    int lowerLimit;
    int upperLimit;
    int primeCount;
    int* randomNumbers;
} ThreadData;

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

DWORD WINAPI countPrimes(LPVOID arg) {
    ThreadData* data = (ThreadData*)arg;

    for (int i = data->start; i < data->end; i++) {
        if (isPrime(data->randomNumbers[i])) {
            data->primeCount++;
        }
    }

    return 0;
}

int main() {
    FILE* fileName = fopen("primes_fork.txt", "w");
    if (fileName == NULL) {
        printf("Failed to open the output file.\n");
        return 1;
    }

    int lowerLimit = 0;
    int upperLimit = 1000;
    int primeCount = 0;

        // Start the timer
        clock_t start = clock();

    for (int num = 10; num <= 1000; num += 10) {
        int* randomNumbers = (int*)malloc(num * sizeof(int));

        // Generate random numbers
        srand(time(NULL));
        for (int i = 0; i < num; i++) {
            randomNumbers[i] = rand() % (upperLimit - lowerLimit + 1) + lowerLimit;
            printf("%d ", randomNumbers[i]);
        }

        int numThreads = 4; // Number of threads to create
        HANDLE* threads = (HANDLE*)malloc(numThreads * sizeof(HANDLE));
        ThreadData* threadData = (ThreadData*)malloc(numThreads * sizeof(ThreadData));

        // Divide the workload among threads
        int chunkSize = num / numThreads;
        int remainder = num % numThreads;

        // Create and launch threads
        for (int i = 0; i < numThreads; i++) {
            threadData[i].start = i * chunkSize + (i < remainder ? i : remainder);
            threadData[i].end = (i + 1) * chunkSize + (i < remainder ? i + 1 : remainder);
            threadData[i].lowerLimit = lowerLimit;
            threadData[i].upperLimit = upperLimit;
            threadData[i].primeCount = 0;
            threadData[i].randomNumbers = randomNumbers;

            threads[i] = CreateThread(NULL, 0, countPrimes, &threadData[i], 0, NULL);
        }

        // Wait for all threads to complete
        WaitForMultipleObjects(numThreads, threads, TRUE, INFINITE);

        // Accumulate the prime counts from each thread
        for (int i = 0; i < numThreads; i++) {
            primeCount += threadData[i].primeCount;
        }

        // Stop the timer
        clock_t end = clock();
        double execution_time = (double)(end - start) / CLOCKS_PER_SEC;

        // Print the number of random numbers and execution time to the file
        int time = 1000*execution_time;
        fprintf(fileName, "%d %d\n", num, time);

        // Cleanup
        for (int i = 0; i < numThreads; i++) {
            CloseHandle(threads[i]);
        }
        free(threads);
        free(threadData);
        free(randomNumbers);
    }

    fclose(fileName);
    printf("Number of primes: %d",primeCount);
    printf("\nProgram execution completed. Results are saved in 'output.txt'.\n");

    return 0;
}
