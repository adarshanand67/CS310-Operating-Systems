#include <stdio.h>
int main()
{
  printf("HELLO - WORLD\n");
}

// Implement in C the following Linux commands using System calls : cat and mv
// cat : Reads the contents of a file and prints it on the screen
// mv : Moves a file from one location to another

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main()
{
  char buff[100], fn[10];
  int fd, n;
  printf("Enter the filename - ");
  scanf("%s", fn);
  fd = open(fn, O_RDONLY);
  while ((n = read(fd, buff, 100)) > 0)
    write(1, buff, n);
  close(fd);
}
