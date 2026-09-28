#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"


float FIFO(int* jobs, int size) {

    if (jobs == NULL || size <= 0) {
        return -1.0f;
    }

    float elapsed_time = 0.0f;
    float total_response_time = 0.0f;

    // Run jobs in the order they were given
    for (int i = 0; i < size; i++) {

        int n = jobs[i];

        // Run one n x n matrix multiplication
        float job_time = do_job(n, n, n, 0);

        if (job_time < 0.0f) {
            return -1.0f;
        }

        // This job finishes after all previous jobs + itself
        elapsed_time += job_time;

        // Add its response/completion time
        total_response_time += elapsed_time;
    }

    // Return average response time
    return total_response_time / size;
}


float SJF(int* jobs, int size) {

    if (jobs == NULL || size <= 0) {
        return -1.0f;
    }

    // Make a copy so we do not change the original array
    int* sorted_jobs =
        malloc(sizeof(int) * size);

    if (sorted_jobs == NULL) {
        return -1.0f;
    }

    for (int i = 0; i < size; i++) {
        sorted_jobs[i] = jobs[i];
    }

    // Sort jobs from smallest to largest
    for (int i = 0; i < size - 1; i++) {

        for (int j = i + 1; j < size; j++) {

            if (sorted_jobs[j] < sorted_jobs[i]) {

                int temp = sorted_jobs[i];
                sorted_jobs[i] = sorted_jobs[j];
                sorted_jobs[j] = temp;
            }
        }
    }

    float elapsed_time = 0.0f;
    float total_response_time = 0.0f;

    // Run shortest jobs first
    for (int i = 0; i < size; i++) {

        int n = sorted_jobs[i];

        float job_time = do_job(n, n, n, 0);

        if (job_time < 0.0f) {
            free(sorted_jobs);
            return -1.0f;
        }

        elapsed_time += job_time;
        total_response_time += elapsed_time;
    }

    free(sorted_jobs);

    return total_response_time / size;
}