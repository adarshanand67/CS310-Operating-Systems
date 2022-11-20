// cat
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
int main(int argc, char *argv[3])
{
  int fd, i;                          // file descriptor
  char buf[2];                        // buffer for reading
  fd = open(argv[1], O_RDONLY, 0777); // open file
  if (fd == -argc)
  {
    printf("file open error\n"); // error
  }
  else
  {
    while ((i = read(fd, buf, 1)) > 0)
    {
      printf("%c", buf[0]); // print
    }
    printf("\n"); // new line
    close(fd);
  }
}

// // mv
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <stdio.h>
// #include <fcntl.h>
// int main(int argc, char *argv[])
// {
//   int i, fd1, fd2;                           // file descriptors
//   char *file1, *file2, buf[2];               // file names and buffer
//   file1 = argv[1];                           // source file
//   file2 = argv[2];                           // destination file
//   printf("file1=%s file2=%s", file1, file2); // print file names
//   fd1 = open(file1, O_RDONLY, 0777);         // open source file
//   fd2 = creat(file2, 0777);                  // create destination file
//   while (i = read(fd1, buf, 1) > 0)          // read source file
//     write(fd2, buf, 1);                      // write to destination file
//   remove(file1);                             // remove source file
//   close(fd1);
//   close(fd2);
// }