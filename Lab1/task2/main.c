#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 40

typedef struct {
    char course_code[20];    // directly specifying length
    char course_name[50];    // directly specifying length
} Course;

typedef struct {
    int mark;                // Mark between 0 and 100
    char the_grade;          // Grade character (A, B, C, D, E)
    int grade_locked;        // Flag to ensure grade is not altered once calculated
} Grade;

typedef struct {
    char registration_number[20];  // directly specifying length
    char name[50];                 // directly specifying length
    int age;                       // Age of the student
    Course course;                 // Course object
    Grade grade;                   // Grade object
} Student;

// Function prototypes
void add_student(Student students[], int *count);
void edit_student(Student *student);
void add_marks(Student *student);
void display_student(const Student *student);
char calculate_grade_from_mark(int mark);
void clear_stdin_buffer();

int main() {
    Student students[MAX_STUDENTS];
    int student_count = 0;
    int choice;

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Edit Student\n");
        printf("3. Add Marks and Calculate Grades\n");
        printf("4. Display Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clear_stdin_buffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        clear_stdin_buffer();

        if (choice == 5) {
            printf("Exiting program.\n");
            break;
        }

        switch (choice) {
            case 1:
                if (student_count < MAX_STUDENTS) {
                    add_student(students, &student_count);
                } else {
                    printf("Maximum student limit reached (%d).\n", MAX_STUDENTS);
                }
                break;

            case 2:
                if (student_count == 0) {
                    printf("No students to edit.\n");
                    break;
                }
                {
                    int index;
                    printf("Enter student index to edit (0 - %d): ", student_count - 1);
                    if (scanf("%d", &index) != 1 || index < 0 || index >= student_count) {
                        clear_stdin_buffer();
                        printf("Invalid index.\n");
                        break;
                    }
                    clear_stdin_buffer();
                    edit_student(&students[index]);
                }
                break;

            case 3:
                if (student_count == 0) {
                    printf("No students to add marks.\n");
                    break;
                }
                {
                    int index;
                    printf("Enter student index to add marks (0 - %d): ", student_count - 1);
                    if (scanf("%d", &index) != 1 || index < 0 || index >= student_count) {
                        clear_stdin_buffer();
                        printf("Invalid index.\n");
                        break;
                    }
                    clear_stdin_buffer();
                    add_marks(&students[index]);
                }
                break;

            case 4:
                if (student_count == 0) {
                    printf("No students to display.\n");
                    break;
                }
                for (int i = 0; i < student_count; i++) {
                    printf("Student index: %d\n", i);
                    display_student(&students[i]);
                    printf("-------------------------------\n");
                }
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void clear_stdin_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void add_student(Student students[], int *count) {
    Student *s = &students[*count];

    printf("Enter registration number (max 19 chars): ");
    fgets(s->registration_number, sizeof(s->registration_number), stdin);
    s->registration_number[strcspn(s->registration_number, "\n")] = 0; // remove newline

    printf("Enter name (max 49 chars): ");
    fgets(s->name, sizeof(s->name), stdin);
    s->name[strcspn(s->name, "\n")] = 0;

    printf("Enter age: ");
    while (scanf("%d", &s->age) != 1) {
        printf("Invalid input. Enter a valid age: ");
        clear_stdin_buffer();
    }
    clear_stdin_buffer();

    printf("Enter course code (max 19 chars): ");
    fgets(s->course.course_code, sizeof(s->course.course_code), stdin);
    s->course.course_code[strcspn(s->course.course_code, "\n")] = 0;

    printf("Enter course name (max 49 chars): ");
    fgets(s->course.course_name, sizeof(s->course.course_name), stdin);
    s->course.course_name[strcspn(s->course.course_name, "\n")] = 0;

    s->grade.mark = -1;          // mark not yet assigned
    s->grade.the_grade = '\0';   // no grade yet
    s->grade.grade_locked = 0;   // not locked yet

    (*count)++;
    printf("Student added successfully.\n");
}

void edit_student(Student *student) {
    char buffer[100];

    printf("Editing student (Registration Number: %s)\n", student->registration_number);

    printf("Enter new registration number (press enter to keep '%s'): ", student->registration_number);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(student->registration_number, buffer, sizeof(student->registration_number) - 1);
        student->registration_number[sizeof(student->registration_number) - 1] = '\0'; // ensure null-termination
    }

    printf("Enter new name (press enter to keep '%s'): ", student->name);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(student->name, buffer, sizeof(student->name) - 1);
        student->name[sizeof(student->name) - 1] = '\0';
    }

    printf("Enter new age (0 to keep %d): ", student->age);
    int age_input;
    if (scanf("%d", &age_input) == 1 && age_input > 0) {
        student->age = age_input;
    }
    clear_stdin_buffer();

    printf("Enter new course code (press enter to keep '%s'): ", student->course.course_code);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(student->course.course_code, buffer, sizeof(student->course.course_code) - 1);
        student->course.course_code[sizeof(student->course.course_code) - 1] = '\0';
    }

    printf("Enter new course name (press enter to keep '%s'): ", student->course.course_name);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(student->course.course_name, buffer, sizeof(student->course.course_name) - 1);
        student->course.course_name[sizeof(student->course.course_name) - 1] = '\0';
    }

    printf("Student details updated.\n");
}

void add_marks(Student *student) {
    if (student->grade.grade_locked) {
        printf("Grades already calculated and locked; cannot modify.\n");
        return;
    }

    int mark;
    printf("Enter the mark for student %s: ", student->name);
    while (scanf("%d", &mark) != 1 || mark < 0 || mark > 100) {
        printf("Invalid mark. Enter integer mark between 0 and 100: ");
        clear_stdin_buffer();
    }
    clear_stdin_buffer();

    student->grade.mark = mark;
    student->grade.the_grade = calculate_grade_from_mark(mark);
    student->grade.grade_locked = 1;

    printf("Grade calculated as '%c' and locked.\n", student->grade.the_grade);
}

char calculate_grade_from_mark(int mark) {
    if (mark > 69) {
        return 'A';
    } else if (mark > 59) {
        return 'B';
    } else if (mark > 49) {
        return 'C';
    } else if (mark > 39) {
        return 'D';
    } else {
        return 'E';
    }
}

void display_student(const Student *student) {
    printf(" Registration Number: %s\n", student->registration_number);
    printf(" Name: %s\n", student->name);
    printf(" Age: %d\n", student->age);
    printf(" Course Code: %s\n", student->course.course_code);
    printf(" Course Name: %s\n", student->course.course_name);
    if (student->grade.mark == -1) {
        printf(" Grade: Not assigned yet\n");
    } else {
        printf(" Mark: %d\n", student->grade.mark);
        printf(" Grade: %c\n", student->grade.the_grade);
    }
}
