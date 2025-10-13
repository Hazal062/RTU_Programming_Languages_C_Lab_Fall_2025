// Student: Hazal Guc (231ADB264)
// Week 5 – Task 3: Student Management System (file persistence)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define DATA_FILE "students.txt"

typedef struct {
  char name[NAME_LEN];
  int id;
  float gpa;
} Student;

static void chomp(char *s) {
  size_t n = strlen(s);
  if (n && s[n - 1] == '\n') s[n - 1] = 0;
}

void load_students(Student arr[], int *count) {
  *count = 0;
  FILE *fp = fopen(DATA_FILE, "r");
  if (!fp) return;
  char line[256];
  while (*count < MAX_STUDENTS && fgets(line, sizeof line, fp)) {
    Student s;
    if (sscanf(line, "%49s %d %f", s.name, &s.id, &s.gpa) == 3)
      arr[(*count)++] = s;
  }
  fclose(fp);
}

void save_students(Student arr[], int count) {
  FILE *fp = fopen(DATA_FILE, "w");
  if (!fp) {
    perror("fopen write");
    return;
  }
  for (int i = 0; i < count; i++)
    fprintf(fp, "%s %d %.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
  fclose(fp);
}

void list_students(Student arr[], int count) {
  if (!count) {
    puts("(no records)");
    return;
  }
  for (int i = 0; i < count; i++)
    printf("%2d) %-20s  ID:%-9d  GPA:%.2f\n", i + 1, arr[i].name, arr[i].id,
           arr[i].gpa);
}

void add_student(Student arr[], int *count) {
  if (*count >= MAX_STUDENTS) {
    puts("Capacity full.");
    return;
  }
  Student s;
  printf("Enter name (use _ instead of space): ");
  if (!fgets(s.name, sizeof s.name, stdin)) {
    puts("input error");
    return;
  }
  chomp(s.name);
  printf("Enter ID: ");
  if (scanf("%d", &s.id) != 1) {
    puts("input error");
    return;
  }
  printf("Enter GPA: ");
  if (scanf("%f", &s.gpa) != 1) {
    puts("input error");
    return;
  }
  getchar();
  arr[(*count)++] = s;
  puts("Student added successfully!");
}

int main(void) {
  Student arr[MAX_STUDENTS];
  int count = 0;
  load_students(arr, &count);

  for (;;) {
    printf("\n==== Student Management System ====\n");
    printf("1. List students\n2. Add student\n3. Save and Exit\n");
    printf("Select an option: ");
    int op = 0;
    if (scanf("%d", &op) != 1) {
      puts("bye");
      return 0;
    }
    getchar();
    if (op == 1)
      list_students(arr, count);
    else if (op == 2)
      add_student(arr, &count);
    else if (op == 3) {
      save_students(arr, count);
      puts("Data saved. Goodbye!");
      break;
    } else
      puts("Unknown option.");
  }
  return 0;
}
