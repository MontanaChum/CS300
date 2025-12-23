#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Course structure
struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

// Load courses from CSV file
void loadCourses(const string& fileName, map<string, Course>& courses) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Could not open file.\n";
        return;
    }

    courses.clear();

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string item;

        Course course;

        // Course ID
        getline(ss, course.courseId, ',');

        // Course title
        getline(ss, course.title, ',');

        // Prerequisites
        while (getline(ss, item, ',')) {
            course.prerequisites.push_back(item);
        }

        courses[course.courseId] = course;
    }

    file.close();
    cout << "Courses loaded successfully.\n";
}

// Print one course
void printCourse(const map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "Please load the data first.\n";
        return;
    }

    string courseId;
    cout << "Enter course ID: ";
    cin >> courseId;

    auto it = courses.find(courseId);
    if (it == courses.end()) {
        cout << "Course not found.\n";
        return;
    }

    const Course& course = it->second;
    cout << course.courseId << ": " << course.title << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None\n";
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Print all courses (sorted automatically by map)
void printAllCourses(const map<string, Course>& courses) {
    if (courses.empty()) {
        cout << "Please load the data first.\n";
        return;
    }

    for (const auto& pair : courses) {
        cout << pair.second.courseId << ": "
             << pair.second.title << endl;
    }
}

// Main menu
int main() {
    map<string, Course> courses;
    int choice = 0;

    cout << "Welcome to the course planner.\n";

    while (choice != 9) {
        cout << "\nMenu:\n";
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course\n";
        cout << "9. Exit\n";
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string fileName;
            cout << "Enter the file name: ";
            cin >> fileName;
            loadCourses(fileName, courses);
            break;
        }
        case 2:
            printAllCourses(courses);
            break;
        case 3:
            printCourse(courses);
            break;
        case 9:
            cout << "Goodbye.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
