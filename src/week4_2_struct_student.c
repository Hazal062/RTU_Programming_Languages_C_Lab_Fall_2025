/*
 * File: week4_2_struct_student.c
 * Author: Hazal Guc
 * Student ID: 231ADB264
 * Description:
 *   Define a Student struct, fill at least two students (via input),
 *   and print them in a formatted way.
 */

#include <stdio.h>
#include <string.h>

#define NAME_LEN 50

typedef struct {
    char  name[NAME_LEN];
    int   id;
    float grade;
} Student;

static void read_line(char *buf, size_t sz) {
    if (fgets(buf, sz, stdin)) {
        size_t len = strlen(buf);
        if (len && buf[len - 1] == '\n')
            buf[len - 1] = '\0';
    }
}

static void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void) {
    Student s1, s2;

    printf("Enter name for student 1: ");
    read_line(s1.name, sizeof s1.name);
    printf("Enter id for student 1: ");
    while (scanf("%d", &s1.id) != 1) { clear_stdin(); printf("Enter id for student 1: "); }
    printf("Enter grade for student 1: ");
    while (scanf("%f", &s1.grade) != 1) { clear_stdin(); printf("Enter grade for student 1: "); }
    clear_stdin();

    printf("Enter name for student 2: ");
    read_line(s2.name, sizeof s2.name);
    printf("Enter id for student 2: ");
    while (scanf("%d", &s2.id) != 1) { clear_stdin(); printf("Enter id for student 2: "); }
    printf("Enter grade for student 2: ");
    while (scanf("%f", &s2.grade) != 1) { clear_stdin(); printf("Enter grade for student 2: "); }
    clear_stdin();

    printf("Student 1: %s, ID: %d, Grade: %.1f\n", s1.name, s1.id, s1.grade);
    printf("Student 2: %s, ID: %d, Grade: %.1f\n", s2.name, s2.id, s2.grade);

    return 0;
}
