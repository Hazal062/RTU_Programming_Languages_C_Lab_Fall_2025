/*
 * Lab 3, Task 3
 * Name: Hazal Guc
 * Student ID: 231ADB264
 *
 * Manual string handling:
 *  - implement my_strlen (count chars, not including '\0')
 *  - implement my_strcpy (copy src -> dest including '\0')
 *
 * Rules:
 *  - Do NOT use <string.h> (no strlen/strcpy)
 *  - Use loops or pointer arithmetic.
 */

#include <stdio.h>

/* prototypes (given by template) */
int my_strlen(const char *str);
void my_strcpy(char *dest, const char *src);

/* --- implementations --- */

int my_strlen(const char *str) {
  if (!str) return 0;  // null guard
  int len = 0;
  while (str[len] != '\0') {
    len++;
  }
  return len;
}

void my_strcpy(char *dest, const char *src) {
  if (!dest || !src) return;  // null guard
  // copy including the terminating '\0'
  while ((*dest++ = *src++) != '\0') {
    // nothing inside, assignment + check does the job
  }
}

/* --- quick demo tests --- */
int main(void) {
  char text[] = "hello";
  int len = my_strlen(text);
  printf("len = %d\n", len);  // 5

  char buffer[100];
  my_strcpy(buffer, text);
  printf("%s\n", buffer);  // hello

  // extra tiny checks
  char empty[] = "";
  printf("len(empty) = %d\n", my_strlen(empty));  // 0
  my_strcpy(buffer, "RTU");
  printf("%s\n", buffer);  // RTU

  return 0;
}
