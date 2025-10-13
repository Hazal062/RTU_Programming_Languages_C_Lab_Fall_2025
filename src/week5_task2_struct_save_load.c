// Student: Hazal Guc (231ADB264)
// Week 5 – Task 2: Save & Load a struct from text file

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char name[50];
  int age;
  float gpa;
} Student;

int save_student(Student s, const char *filename) {
  FILE *fp = fopen(filename, "w");
  if (!fp) {
    perror("fopen write");
    return 0;
  }
  if (fprintf(fp, "%s %d %.2f\n", s.name, s.age, s.gpa) < 0) {
    perror("fprintf");
    fclose(fp);
    return 0;
  }
  fclose(fp);
  return 1;
}

Student load_student(const char *filename) {
  Student s = {0};
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    perror("fopen read");
    return s;
  }
  if (fscanf(fp, "%49s %d %f", s.name, &s.age, &s.gpa) != 3) {
    fprintf(stderr, "parse error\n");
  }
  fclose(fp);
  return s;
}

int main(void) {
  const char *filename = "student.txt";

  Student me = {"Hazal_Guc", 21, 3.75f};
  printf("Saving student to file...\n");
  if (!save_student(me, filename)) return 1;

  printf("Loading student from file...\n");
  Student r = load_student(filename);
  printf("Loaded student: %s, %d, GPA %.2f\n", r.name, r.age, r.gpa);
  return 0;
}
