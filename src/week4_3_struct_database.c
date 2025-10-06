/*
 * File: week4_3_struct_database.c
 * Author: Hazal Guc
 * Student ID: 231ADB264
 * Description:
 *   Build an in-memory database (array of Student structs) using malloc.
 *   Read N students, then print a simple table. Free all allocated memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50

typedef struct {
  char name[NAME_LEN];
  int id;
  float grade;
} Student;

static void read_line(char *buf, size_t sz) {
  if (fgets(buf, sz, stdin)) {
    size_t len = strlen(buf);
    if (len && buf[len - 1] == '\n') buf[len - 1] = '\0';
  }
}

static void clear_stdin(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

int main(void) {
  int n;
  printf("Enter number of students: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    fprintf(stderr, "Invalid count.\n");
    return 1;
  }
  clear_stdin();

  Student *students = (Student *)malloc((size_t)n * sizeof *students);
  if (!students) {
    perror("malloc");
    return 1;
  }

  for (int i = 0; i < n; i++) {
    printf("Enter data for student %d\n", i + 1);

    printf("  Name: ");
    read_line(students[i].name, sizeof students[i].name);

    printf("  ID: ");
    while (scanf("%d", &students[i].id) != 1) {
      clear_stdin();
      printf("  ID: ");
    }

    printf("  Grade: ");
    while (scanf("%f", &students[i].grade) != 1) {
      clear_stdin();
      printf("  Grade: ");
    }
    clear_stdin();
  }

  printf("\n%-6s %-20s %s\n", "ID", "Name", "Grade");
  for (int i = 0; i < n; i++) {
    printf("%-6d %-20s %.1f\n", students[i].id, students[i].name,
           students[i].grade);
  }

  free(students);
  return 0;
}
