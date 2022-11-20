// Function to print 100 prime numbers

#include <math.h>
#include <stdio.h>

int main() {
    while (1) {
        int i, j, k, n, count = 0;
        for (i = 2; i <= 100; i++) {
            for (j = 2; j <= i; j++) {
                if (i % j == 0) {
                    break;
                }
            }
            if (j == i) {
                printf("%d ", i);
                count++;
            }
        }
        printf("\n");
        printf("Total prime numbers: %d\n", count);
    }
    return 0;
}