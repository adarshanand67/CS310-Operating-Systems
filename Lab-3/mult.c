#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

double CTimer() {
    struct timeval tm;
    gettimeofday(&tm, NULL);
    return ((double)tm.tv_sec + (double)(tm.tv_usec / 1000000.0));
}

#define ARGS "a:b:t:" // Command line arguments
char *Usage = "print-rand-matrix -a rows -b cols -t threads\n";

int c;
int i, j;
int Rows1, Cols1, Rows2, Cols2;
int Threads;
FILE *fp1, *fp2;
double **A, **B, **C, **D;

void *multiply(void *arg) {
    int thread_id = (int)arg;

    int rows_per_thread = Rows1 / Threads;
    int remainder = Rows1 % Threads;
    int start = thread_id * rows_per_thread + (thread_id < remainder ? thread_id : remainder);
    int end = start + rows_per_thread + (thread_id < remainder ? 1 : 0);
    for (int i = start; i < end; i++) {
        for (int j = 0; j < Cols2; j++) {
            for (int k = 0; k < Cols1; k++) {
                D[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Take in 2 input matrix from input1.txt and input2.txt
    // Multiply them and print the result to output.txt
    while ((c = getopt(argc, argv, ARGS)) != EOF) {
        switch (c) {
        case 'a':
            // read matrix A fron given file name skip first reading
            fp1 = fopen(optarg, "r");
            fscanf(fp1, "%d %d", &Rows1, &Cols1);
            A = (double **)malloc(Rows1 * sizeof(double *));
            for (int i = 0; i < Rows1; i++) {
                A[i] = (double *)malloc(Cols1 * sizeof(double));
                for (int j = 0; j < Cols1; j++) {
                    char c = fgetc(fp1);
                    if (c == '#') {
                        while (c != '\n') {
                            c = fgetc(fp1); // skip the comment
                        }
                    } else {
                        fseek(fp1, -1, SEEK_CUR);
                        fscanf(fp1, "%lf", &A[i][j]);
                    }
                }
            }
            fclose(fp1);
        case 'b':
            // read matrix B fron given file name skip first reading
            fp2 = fopen(optarg, "r");
            fscanf(fp2, "%d %d", &Rows2, &Cols2);
            B = (double **)malloc(Rows2 * sizeof(double *));
            for (int i = 0; i < Rows2; i++) {
                B[i] = (double *)malloc(Cols2 * sizeof(double));
                for (int j = 0; j < Cols2; j++) {
                    char c = fgetc(fp2);
                    if (c == '#') {
                        while (c != '\n') {
                            c = fgetc(fp2); // skip the comment
                        }
                    } else {
                        fseek(fp2, -1, SEEK_CUR);
                        fscanf(fp2, "%lf", &B[i][j]);
                    }
                }
            }
            fclose(fp2);

            break;
        case 't':
            Threads = atoi(optarg);
            break;
        default:
            fprintf(stderr, "unrecognized command %c\n", (char)c);
            fprintf(stderr, "usage: %s", Usage);
            exit(1);
        }
    }
    // Print first row of A
    // printf("A = \n");
    // for (int i = 0; i < Cols1; i++) {
    //     printf("%lf ", A[0][i]);
    // }

    //* 1. Product without using threads
    double **C;
    C = (double **)malloc(Rows1 * sizeof(double *));
    for (int i = 0; i < Rows1; i++) {
        C[i] = (double *)malloc(Cols2 * sizeof(double));
    }
    double start = CTimer();
    for (int i = 0; i < Rows1; i++) {
        for (int j = 0; j < Cols2; j++) {
            for (int k = 0; k < Cols1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double end = CTimer();
    printf("Time taken without threads: %lf", end - start);
    // Append an time_without_thread.txt file to store the time taken
    FILE *fp3 = fopen("time_without_thread.txt", "a");
    fprintf(fp3, "%lf \n", end - start);
    fclose(fp3);

    // Send matrix product to output.txt
    // FILE *fp3;
    // fp3 = fopen("output.txt", "w");
    // fprintf(fp3, "%d %d \n", Rows1, Cols2);
    // for (int i = 0; i < Rows1; i++) {
    //     fprintf(fp3, "# Row %d \n", i);
    //     for (int j = 0; j < Cols2; j++) {
    //         fprintf(fp3, "%lf ", C[i][j]);
    //     }
    //     fprintf(fp3, "\n");
    // }
    // fclose(fp3);

    //* 2. Product with threads

    D = (double **)malloc(Rows1 * sizeof(double *));
    for (int i = 0; i < Rows1; i++) {
        D[i] = (double *)malloc(Cols2 * sizeof(double));
    }
    double start = CTimer();
    pthread_t *threads = (pthread_t *)malloc(Threads * sizeof(pthread_t));
    for (int i = 0; i < Threads; i++) {
        pthread_create(&threads[i], NULL, multiply, (void *)i);
    }
    for (int i = 0; i < Threads; i++) {
        pthread_join(threads[i], NULL);
    }
    double end = CTimer();
    printf("Time taken with threads: %lf", end - start);
    // Append an time_thread.txt file to store the time taken
    FILE *fp4;
    fp4 = fopen("time_thread.txt", "a");
    fprintf(fp4, "%lf \n", end - start);
    fclose(fp4);
}