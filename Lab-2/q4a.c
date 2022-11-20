// and enter into a long loop.
// Start three to four processes of the same program
// and observe the printed address values.
// Show how two processes which are members of the relationship parent child are concurrent from execution point of view, initially the child is copy of the parent, but every process has its own data.
#include <stdio.h>
int main() {
    int a = 10;
    printf("%p\n", &a);
    while (1)
        ;
}
