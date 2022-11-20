#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main()
{
  char buff[100], fn[10];
  int fd, n, i;

  printf("Enter the filename\n");
  scanf("%s", fn);
  // Append some text to the file, if file does not exist, create it
  fd = open(fn, O_WRONLY | O_APPEND | O_CREAT, 0644);
  printf("Enter the text\n");
  scanf("%s", buff);
  write(fd, buff, strlen(buff));
  close(fd);
}
