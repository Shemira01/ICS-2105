#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Course {
private:
    string course_code;
    string course_name;

public:
    Course() : course_code(""), course_name("") {}

    void set_course_code(const string& code) { course_code = code; }
    void set_course_name(const string& name) { course_name = name; }

    string get_course_code() const { return course_code; }
    string get_course_name() const { return course_name; }

    void input_course_info() {
        cout << "Enter course code (max 19 chars): ";
        getline(cin, course_code);
        cout << "Enter course name (max 49 chars): ";
        getline(cin, course_name);
    }

    void display() const {
        cout << " Course Code: " << course_code << "\n";
        cout << " Course Name: " << course_name << "\n";
    }
};

class Grade {
private:
    int marks;
    char the_grade;
    bool grade_locked;

public:
    Grade() : marks(-1), the_grade('\0'), grade_locked(false) {}

    void set_mark(int m) {
        if (!grade_locked) {
            marks = m;
            the_grade = calculate_grade_from_marks(marks);
            grade_locked = true;
        } else {
            cout << "Grade is locked and cannot be changed.\n";
        }
    }

    int get_marks() const { return marks; }
    char get_the_grade() const { return the_grade; }
    bool is_locked() const { return grade_locked; }

    static char calculate_grade_from_marks(int marks) {
        if (marks > 69) return 'A';
        else if (marks > 59) return 'B';
        else if (marks > 49) return 'C';
        else if (marks > 39) return 'D';
        else return 'E';
    }

    void display() const {
        if (marks == -1)
            cout << " Grade: Not assigned yet\n";
        else
            cout << " Marks: " << marks << "\n"
                 << " Grade: " << the_grade << "\n";
    }
};

class Student {
private:
    string registration_number;
    string name;
    int age;
    Course course;
    Grade grade;

public:
    Student() : registration_number(""), name(""), age(0) {}

    void input_student_info() {
        cout << "Enter registration number (max 19 chars): ";
        getline(cin, registration_number);

        cout << "Enter name (max 49 chars): ";
        getline(cin, name);

        cout << "Enter age: ";
        while (!(cin >> age)) {
            cout << "Invalid input. Enter a valid age: ";
            clear_stdin_buffer();
        }
        clear_stdin_buffer();

        course.input_course_info();
    }

    void edit_student_info() {
        cout << "Editing student (Registration Number: " << registration_number << ")\n";

        cout << "Enter new registration number (press enter to keep '" << registration_number << "'): ";
        string input;
        getline(cin, input);
        if (!input.empty())
            registration_number = input;

        cout << "Enter new name (press enter to keep '" << name << "'): ";
        getline(cin, input);
        if (!input.empty())
            name = input;

        cout << "Enter new age (0 to keep " << age << "): ";
        int age_input;
        if ((cin >> age_input) && age_input > 0)
            age = age_input;
        else
            cout << "Keeping existing age.\n";
        clear_stdin_buffer();

        cout << "Edit course details:\n";
        cout << "Current course code: " << course.get_course_code() << "\n";
        cout << "Enter new course code (press enter to keep): ";
        getline(cin, input);
        if (!input.empty())
            course.set_course_code(input);

        cout << "Current course name: " << course.get_course_name() << "\n";
        cout << "Enter new course name (press enter to keep): ";
        getline(cin, input);
        if (!input.empty())
            course.set_course_name(input);

        cout << "Student details updated.\n";
    }

    string get_registration_number() const { return registration_number; }
    string get_name() const { return name; }

    bool match(const string& key) const {
        return registration_number == key || name == key;
    }

    void add_marks() {
        if (grade.is_locked()) {
            cout << "Grades already calculated and locked; cannot modify.\n";
            return;
        }

        int mark;
        cout << "Enter the mark for student " << name << ": ";
        while (!(cin >> mark) || mark < 0 || mark > 100) {
            cout << "Invalid mark. Enter integer mark between 0 and 100: ";
            clear_stdin_buffer();
        }
        clear_stdin_buffer();

        grade.set_mark(mark);
        cout << "Grade calculated as '" << grade.get_the_grade() << "' and locked.\n";
    }

    void display() const {
        cout << " Registration Number: " << registration_number << "\n"
             << " Name: " << name << "\n"
             << " Age: " << age << "\n";
        course.display();
        grade.display();
    }

    static void clear_stdin_buffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
};

// Utility function to find student by reg no or name
Student* find_student(vector<Student>& students, const string& key) {
    for (auto& student : students) {
        if (student.match(key))
            return &student;
    }
    return nullptr;
}

int main() {
    vector<Student> students;
    int choice;

    while (true) {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Edit Student\n";
        cout << "3. Add Marks and Calculate Grades\n";
        cout << "4. Display Students\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            Student::clear_stdin_buffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        Student::clear_stdin_buffer();

        if (choice == 5) {
            cout << "Exiting program.\n";
            break;
        }

        switch (choice) {
        case 1: {
            if (students.size() >= 40) {
                cout << "Maximum student limit reached (40).\n";
                break;
            }
            Student s;
            s.input_student_info();
            students.push_back(s);
            cout << "Student added successfully.\n";
            break;
        }
        case 2: {
            if (students.empty()) {
                cout << "No students to edit.\n";
                break;
            }
            cout << "Enter registration number or name of the student to edit: ";
            string key;
            getline(cin, key);
            Student* s = find_student(students, key);
            if (s) {
                s->edit_student_info();
            }
            else {
                cout << "Student not found with registration number or name '" << key << "'.\n";
            }
            break;
        }
        case 3: {
            if (students.empty()) {
                cout << "No students to add marks.\n";
                break;
            }
            cout << "Enter registration number or name of the student to add marks: ";
            string key;
            getline(cin, key);
            Student* s = find_student(students, key);
            if (s) {
                s->add_marks();
            }
            else {
                cout << "Student not found with registration number or name '" << key << "'.\n";
            }
            break;
        }
        case 4: {
            if (students.empty()) {
                cout << "No students to display.\n";
                break;
            }
            for (const auto& s : students) {
                s.display();
                cout << "-------------------------------\n";
            }
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
