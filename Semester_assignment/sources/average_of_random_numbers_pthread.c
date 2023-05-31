#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct {
    int* numbers;
    int start_index;
    int end_index;
    double* partial_sum;
} ThreadArgs;

void* calculatePartialSum(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int* numbers = args->numbers;
    int start_index = args->start_index;
    int end_index = args->end_index;
    double* partial_sum = args->partial_sum;

    for (int i = start_index; i <= end_index; i++) {
        *partial_sum += numbers[i];
    }

    pthread_exit(NULL);
}

void runProgram(FILE* file, int num, int lower_limit, int upper_limit) {
    clock_t start_time, end_time;
    double execution_time;

    // Generate random numbers
    int* numbers = (int*)malloc(num * sizeof(int));

    start_time = clock();

    srand(time(NULL));
    for (int i = 0; i < num; i++) {
        numbers[i] = (rand() % (upper_limit - lower_limit + 1)) + lower_limit;
        printf("%d ", numbers[i]);
    }

    // Calculate average using pthreads
    int thread_count = 4; // Set the number of threads for parallelization
    pthread_t* threads = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
    ThreadArgs* thread_args = (ThreadArgs*)malloc(thread_count * sizeof(ThreadArgs));
    double* partial_sums = (double*)calloc(thread_count, sizeof(double));

    int numbers_per_thread = num / thread_count;
    int remainder = num % thread_count;

    int start_index = 0;
    int end_index;
    for (int i = 0; i < thread_count; i++) {
        end_index = start_index + numbers_per_thread - 1;

        if (remainder > 0) {
            end_index++;
            remainder--;
        }

        thread_args[i].numbers = numbers;
        thread_args[i].start_index = start_index;
        thread_args[i].end_index = end_index;
        thread_args[i].partial_sum = &partial_sums[i];

        if (pthread_create(&threads[i], NULL, calculatePartialSum, (void*)&thread_args[i]) != 0) {
            printf("Error creating thread.\n");
            return;
        }

        start_index = end_index + 1;
    }

    for (int i = 0; i < thread_count; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error joining thread.\n");
            return;
        }
    }

    double sum = 0.0;
    for (int i = 0; i < thread_count; i++) {
        sum += partial_sums[i];
    }

    // Calculate average
    double average = sum / num;
    printf("Average: %f", average);

    // End measuring time
    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;


    // Write results to file
    int time = 1000*execution_time;
    fprintf(file, "%d %d\n", num, time);
    
    free(numbers);
    free(threads);
    free(thread_args);
    free(partial_sums);
}

int main() {
    const char* filename = "average_of_random_numbers_pthread.txt";
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open file '%s' for writing.\n", filename);
        return 1;
    }

    int lower_limit = 0;
    int upper_limit = 1000;

    // Run the program 1000 times with increasing number of random numbers
    for (int num = 0; num <= 1000; num += 10) {
        runProgram(file, num, lower_limit, upper_limit);
    }

    fclose(file);

    printf("\nResults have been saved to '%s'.\n", filename);

    return 0;
}
