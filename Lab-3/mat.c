#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

char *Usage = "print-rand-matrix -r rows -c cols\n";
#define ARGS "r:c:"

int Rows;
int Cols;

int main(int argc, char **argv) {
    int c;
    int i;
    int j;
    double r;
    struct timeval tm;
    unsigned long seed;

    while ((c = getopt(argc, argv, ARGS)) != EOF) {
        switch (c) {
        case 'r':
            Rows = atoi(optarg);
            break;
        case 'c':
            Cols = atoi(optarg);
            break;
        default:
            fprintf(stderr, "unrecognized command %c\n",
                    (char)c);
            fprintf(stderr, "usage: %s", Usage);
            exit(1);
        }
    }

    if (Rows <= 0) {
        fprintf(stderr, "must enter rows\n");
        fprintf(stderr, "usage: %s", Usage);
        exit(1);
    }

    if (Cols <= 0) {
        fprintf(stderr, "must enter columns\n");
        fprintf(stderr, "usage: %s", Usage);
        exit(1);
    }

    gettimeofday(&tm, NULL);
    seed = tm.tv_sec + tm.tv_usec;
    srand48(seed);

    // Print output in input1.txt file
    FILE *fp;
    fp = fopen("input1.txt", "w+");
    fprintf(fp, "%d %d \n", Rows, Cols);
    for (i = 0; i < Rows; i++) {
        fprintf(fp, "# Row %d \n", i);
        for (j = 0; j < Cols; j++) {
            r = drand48();
            fprintf(fp, "%f \n", r);
        }
    }
    fclose(fp);

    // Print output in input2.txt file
    FILE *fp2;
    fp2 = fopen("input2.txt", "w+");
    fprintf(fp2, "%d %d \n", Rows, Cols);
    for (i = 0; i < Rows; i++) {
        fprintf(fp2, "# Row %d \n", i);
        for (j = 0; j < Cols; j++) {
            r = drand48();
            fprintf(fp2, "%f \n", r);
        }
    }
    fclose(fp2);

    exit(0);
}
