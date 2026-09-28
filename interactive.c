#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"
#include "scheduler.h"

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf(
            "Usage: %s <FIFO/SJF> <job_sizes_comma_separated>\n",
            argv[0]
        );
        return 1;
    }

    char *policy = argv[1];

    // Make a copy because strtok modifies the string
    char *jobs_text = strdup(argv[2]);

    if (jobs_text == NULL) {
        return 1;
    }

    // First count how many jobs there are
    int count = 1;

    for (int i = 0; jobs_text[i] != '\0'; i++) {
        if (jobs_text[i] == ',') {
            count++;
        }
    }

    int *jobs = malloc(sizeof(int) * count);

    if (jobs == NULL) {
        free(jobs_text);
        return 1;
    }

    int index = 0;

    char *token = strtok(jobs_text, ",");

    while (token != NULL) {

        int job_size = atoi(token);

        if (job_size <= 0) {
            printf("Job sizes must be positive integers.\n");

            free(jobs);
            free(jobs_text);

            return 1;
        }

        jobs[index] = job_size;
        index++;

        token = strtok(NULL, ",");
    }

    float response_time;

    if (strcmp(policy, "FIFO") == 0) {

        response_time = FIFO(jobs, count);

    } else if (strcmp(policy, "SJF") == 0) {

        response_time = SJF(jobs, count);

    } else {

        printf("Scheduling policy must be FIFO or SJF.\n");

        free(jobs);
        free(jobs_text);

        return 1;
    }

    printf("Average response time: %.6f seconds\n", response_time);

    free(jobs);
    free(jobs_text);

    return 0;
}