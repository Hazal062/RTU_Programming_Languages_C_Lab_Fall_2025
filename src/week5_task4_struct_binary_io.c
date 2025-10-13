// Student: Hazal Guc (231ADB264)
// Week 5 – Bonus: Binary I/O with fread/fwrite

#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

int main(void) {
    const char *path = "student.bin";
    Student s = {"Hazal_Guc", 21, 3.75f};
    Student t = {0};

    puts("Saving student in binary format...");
    FILE *fp = fopen(path, "wb");
    if (!fp) { perror("fopen wb"); return 1; }
    if (fwrite(&s, sizeof(Student), 1, fp) != 1) {
        perror("fwrite"); fclose(fp); return 1;
    }
    fclose(fp);

    puts("Loading student from binary file...");
    fp = fopen(path, "rb");
    if (!fp) { perror("fopen rb"); return 1; }
    if (fread(&t, sizeof(Student), 1, fp) != 1) {
        perror("fread"); fclose(fp); return 1;
    }
    fclose(fp);

    printf("Loaded student: %s, %d, GPA %.2f\n", t.name, t.age, t.gpa);
    return 0;
}
