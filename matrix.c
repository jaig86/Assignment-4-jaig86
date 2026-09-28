#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_random_matrix(int rows, int cols, int *matrix) {

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            matrix[i * cols + j] = rand() % 10;
        }
    }
}


void multiply_matrices(int rows1, int cols1, int *matrix1,
                       int rows2, int cols2, int *matrix2,
                       int *result) {

    if (cols1 != rows2) {
        return;
    }

    for (int i = 0; i < rows1; i++) {

        for (int j = 0; j < cols2; j++) {

            int sum = 0;

            for (int k = 0; k < cols1; k++) {

                sum +=
                    matrix1[i * cols1 + k] *
                    matrix2[k * cols2 + j];
            }

            result[i * cols2 + j] = sum;
        }
    }
}


void display_matrix(int rows, int cols, int *matrix) {

    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            printf("%d ", matrix[i * cols + j]);
        }

        printf("\n");
    }
}


float do_job(int rows1, int cols1, int cols2, int forever) {

    int rows2 = cols1;

    int *matrix1 =
        malloc(sizeof(int) * rows1 * cols1);

    int *matrix2 =
        malloc(sizeof(int) * rows2 * cols2);

    int *result =
        malloc(sizeof(int) * rows1 * cols2);

    if (matrix1 == NULL ||
        matrix2 == NULL ||
        result == NULL) {

        free(matrix1);
        free(matrix2);
        free(result);

        return -1.0f;
    }

    generate_random_matrix(
        rows1,
        cols1,
        matrix1
    );

    generate_random_matrix(
        rows2,
        cols2,
        matrix2
    );

    struct timespec t0;
    struct timespec t1;

    float total_time = 0.0f;

    if (forever == 0) {

        timespec_get(&t0, TIME_UTC);

        multiply_matrices(
            rows1,
            cols1,
            matrix1,
            rows2,
            cols2,
            matrix2,
            result
        );

        timespec_get(&t1, TIME_UTC);

        float dns =
            (float)(t1.tv_nsec - t0.tv_nsec)
            / 1000000000.0f;

        float ds =
            (float)(t1.tv_sec - t0.tv_sec);

        total_time = ds + dns;
    }

    else {

        while (1) {

            multiply_matrices(
                rows1,
                cols1,
                matrix1,
                rows2,
                cols2,
                matrix2,
                result
            );
        }
    }

    free(matrix1);
    free(matrix2);
    free(result);

    return total_time;
}