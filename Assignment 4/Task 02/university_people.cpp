#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;

public:
    Person(std::string n = "", int pid = 0, std::string ph = "")
        : name(std::move(n)), id(pid), phone(std::move(ph)) {}
    virtual ~Person() = default;
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;

public:
    Student(std::string n, int pid, std::string ph, std::string prog, double g)
        : Person(std::move(n), pid, std::move(ph)), programme(std::move(prog)), cgpa(g) {}
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;

public:
    Staff(std::string n, int pid, std::string ph, std::string dept, double sal)
        : Person(std::move(n), pid, std::move(ph)), department(std::move(dept)), salary(sal) {}
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(std::string n, int pid, std::string ph,
                      std::string prog, double g, std::string dept, double sal)
        : Person(std::move(n), pid, std::move(ph)),
          Student("", 0, "", std::move(prog), g),
          Staff("", 0, "", std::move(dept), sal) {}

    void display() const {
        std::cout << "TA: " << name << " (ID: " << id << ", Phone: " << phone
                  << ") | Prog: " << programme << ", CGPA: " << cgpa
                  << " | Dept: " << department << ", Salary: " << salary << '\n';
    }
};

int main() {
    TeachingAssistant ta("Ananya", 2046, "9876543210", "M.Tech CSE", 9.4, "CSE", 25000.0);
    ta.display();
    return 0;
}