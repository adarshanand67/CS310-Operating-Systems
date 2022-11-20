// cat
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
int main(int argc, char *argv[3])
{
  int fd, i;
  char buf[2];
  fd = open(argv[1], O_RDONLY, 0777);
  if (fd == -argc)
  {
    printf("file open error");
  }
  else
  {
    while ((i = read(fd, buf, 1)) > 0)
    {
      printf("%c", buf[0]);
    }
    close(fd);
  }
}

// mv
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
  int i, fd1, fd2;
  char *file1, *file2, buf[2];
  file1 = argv[1];
  file2 = argv[2];
  printf("file1=%s file2=%s", file1, file2);
  fd1 = open(file1, O_RDONLY, 0777);
  fd2 = creat(file2, 0777);
  while (i = read(fd1, buf, 1) > 0)
    write(fd2, buf, 1);
  remove(file1);
  close(fd1);
  close(fd2);
}