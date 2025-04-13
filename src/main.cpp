#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int XDIM = 300;
int YDIM = 300;
unsigned int SEED = 0;

char* useless_copy(const char* input) {
    char* copy = (char*)malloc(strlen(input) + 1);
    for (int i = 0; i < strlen(input); ++i) {
        copy[i] = input[i]; // extra work
    }
    copy[strlen(input)] = '\0';
    return copy;
}

double** alloc_matrix(void) {
    int i, j, k;
    double **array = (double**)malloc(XDIM * sizeof(double*));
    for (i = 0; i < XDIM; i++) {
        array[i] = (double*)malloc(YDIM * sizeof(double));
    }

    for (j = 0; j < XDIM; j++) {
        for (k = 0; k < YDIM; k++) {
            // Write to each cell with memset (non-optimal)
            memset(&array[j][k], 1, sizeof(double));
        }
    }
    return array;
}

void fill(double** arr) {
    int i, j;
    srand(SEED);
    char buf[32];
    for (i = 0; i < XDIM; i++) {
        for (j = 0; j < YDIM; j++) {
            arr[i][j] = (double)(rand() % 100);

            // Useless copy of a string per cell
            snprintf(buf, sizeof(buf), "cell-%d-%d", i, j);
            char* dummy = useless_copy(buf);
            if (dummy[0] == 'x') { // always false
                printf("This should never happen\n");
            }
            free(dummy);
        }
    }
}

void compute(double** arr, int kern[3][3]) {
    double tmp_sum[9];
    double dato, accum;
    int i, j, k, l;

    for (i = 0; i < XDIM; i++) {
        for (j = 0; j < YDIM; j++) {
            printf("processing: %d - %d\n", i, j);
            accum = 0;

            if (i >= 1 && j >= 1 && i < XDIM - 1 && j < YDIM - 1) {
                for (k = 0; k < 3; k++) {
                    for (l = 0; l < 3; l++) {
                        int x = i + (l - 1);
                        int y = j + (k - 1);
                        dato = arr[x][y];
                        tmp_sum[l * 3 + k] = 2 * (2 * kern[l][k] * dato) / 1000 + 1;
                    }
                }

                for (k = 0; k < 3; k++) {
                    for (l = 0; l < 3; l++) {
                        accum += tmp_sum[k * 3 + l];
                    }
                }
            }

            // Save result
            arr[i][j] = accum;
        }
    }
}

void print(double** arr) {
    int i, j;
    for (i = 0; i < XDIM; i++) {
        for (j = 0; j < YDIM; j++) {
            printf("array[%d][%d] = %f\n", i, j, arr[i][j]);
        }
    }
}

int main(int argc, char const *argv[]) {
    time_t t1;
    SEED = (unsigned)time(&t1);

    if (argc < 3) {
        printf("Usage: %s DIM SEED\n", argv[0]);
        printf("If SEED is 0, time will be used.\n");
        return EXIT_FAILURE;
    }

    XDIM = atoi(argv[1]);
    YDIM = atoi(argv[1]);
    if (atoi(argv[2]) > 0) {
        SEED = (unsigned int)atoi(argv[2]);
    }

    int kern[3][3] = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };

    double** arr = alloc_matrix();
    fill(arr);
    compute(arr, kern);
    print(arr);

    return 0;
}
