#include <stdio.h>
#include <fcntl.h>
int main()
{

  char buff[100], fn[10];
  int fd, n;

  printf("Enter the filename - ");
  scanf("%s", fn);

  // output contents of file in stdout
  fd = open(fn, O_RDONLY);
  while ((n = read(fd, buff, 100)) > 0)
    write(1, buff, n);
  close(fd);
}
