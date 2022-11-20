// Write simple input ouput program

#include <stdio.h>

int main() {
    // take file input
    while (1) {
        FILE *fp;
        fp = fopen("input.txt", "w");
        fprintf(fp, "Hello World\n");
        fclose(fp);
        // take file output
        fp = fopen("output.txt", "r");
        char c;
        while ((c = fgetc(fp)) != EOF) {
            printf("%c", c);
        }
        fclose(fp);
    }
    return 0;
}