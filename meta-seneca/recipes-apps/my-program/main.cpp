#include "simple-library.h"
#include <iostream>
#include <vector>
#include <algorithm>

struct Student {
    int id;
    std::string name;
};

nlohmann::json to_json(const std::vector<Student>& students) {
    nlohmann::json j = {{"students", nlohmann::json::array()}};
    for (const auto& s : students) {
        j["students"].push_back({{"id", s.id}, {"name", s.name}});
    }
    return j;
}

void list_students(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No students.\n";
        return;
    }
    for (const auto& s : students) {
        std::cout << "ID: " << s.id << ", Name: " << s.name << "\n";
    }
}

int main() {
    std::string path;
    std::cout << "Enter file path: ";
    std::getline(std::cin, path);

    std::vector<Student> students;
    try {
        auto j = read_file(path);
        for (const auto& s : j["students"]) {
            students.push_back({s["id"], s["name"]});
        }
    } catch (const std::exception& e) {
        std::cout << "File not found or invalid, starting with empty list: " << e.what() << "\n";
    }

    while (true) {
        std::cout << "\n1. List students\n2. Add student\n3. Modify student\n4. Delete student\n5. Save and exit\nChoice: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            list_students(students);
        } else if (choice == 2) {
            int id;
            std::string name;
            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cin.ignore();
            if (std::find_if(students.begin(), students.end(), [id](const auto& s) { return s.id == id; }) != students.end()) {
                std::cout << "ID already exists.\n";
                continue;
            }
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            students.push_back({id, name});
        } else if (choice == 3) {
            int id;
            std::cout << "Enter ID to modify: ";
            std::cin >> id;
            std::cin.ignore();
            auto it = std::find_if(students.begin(), students.end(), [id](const auto& s) { return s.id == id; });
            if (it != students.end()) {
                std::cout << "Enter new name: ";
                std::getline(std::cin, it->name);
            } else {
                std::cout << "Student not found.\n";
            }
        } else if (choice == 4) {
            int id;
            std::cout << "Enter ID to delete: ";
            std::cin >> id;
            std::cin.ignore();
            auto it = std::remove_if(students.begin(), students.end(), [id](const auto& s) { return s.id == id; });
            if (it != students.end()) {
                students.erase(it, students.end());
                std::cout << "Student deleted.\n";
            } else {
                std::cout << "Student not found.\n";
            }
        } else if (choice == 5) {
            create_file(to_json(students), path);
            std::cout << "Saved to " << path << "\n";
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
    return 0;
}
