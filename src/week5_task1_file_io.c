// Student: Hazal Guc (231ADB264)
// Week 5 – Task 1: Read & Write text files

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *fp;
  char filename[100] = "data.txt";
  char line[256];

  fp = fopen(filename, "w");
  if (!fp) {
    perror("fopen write");
    return 1;
  }

  printf("Writing lines to %s...\n", filename);
  fprintf(fp, "Hello, file I/O in C!\n");
  fprintf(fp, "This is another line.\n");
  fclose(fp);

  fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen read");
    return 1;
  }

  printf("Reading contents:\n");
  while (fgets(line, sizeof line, fp)) {
    fputs(line, stdout);
  }
  fclose(fp);
  return 0;
}
