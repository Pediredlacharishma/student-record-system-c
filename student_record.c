#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};
void deleteStudent();
void addStudent();
void viewStudents();
void searchStudent();

int main() {
    int choice;

    while (1) {
       printf("\n--- Student Record Management System ---\n");
printf("1. Add Student\n");
printf("2. View Students\n");
printf("3. Search Student\n");
printf("4. Exit\n");
printf("Enter your choice: ");


       switch (choice) {
    case 1:
        addStudent();
        break;
    case 2:
        viewStudents();
        break;
    case 3:
        searchStudent();
        break;
    case 4:
        exit(0);
    default:
        printf("Invalid choice. Try again.\n");
}

    }

    return 0;
}

void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("Student record added successfully!\n");
}
void viewStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("Roll: %d\n", s.roll);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f\n", s.marks);
        printf("----------------------\n");
    }

    fclose(fp);
}
void searchStudent() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            printf("\nStudent Found!\n");
            printf("Roll: %d\n", s.roll);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }

    fclose(fp);
}
void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Student record deleted successfully.\n");
    } else {
        printf("Student not found.\n");
    }
}

    fclose(fp);
}
