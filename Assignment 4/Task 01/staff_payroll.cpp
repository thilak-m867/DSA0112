#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Staff {
protected:
    std::string name;
    int id;

public:
    Staff(std::string n, int staffId) : name(std::move(n)), id(staffId) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;

    void printSlip() const {
        std::cout << "ID: " << id << " | Name: " << name
                  << " | Pay: Rs " << std::fixed << std::setprecision(2) << pay() << '\n';
    }
};

class RegularStaff : public Staff {
protected:
    double basic;
    static constexpr double DA_RATE = 0.42;

public:
    RegularStaff(std::string n, int staffId, double basicPay)
        : Staff(std::move(n), staffId), basic(basicPay) {}

    double pay() const override {
        return basic + (basic * DA_RATE);
    }
};

class Professor : public RegularStaff {
    double researchAllowance;

public:
    Professor(std::string n, int staffId, double basicPay, double research)
        : RegularStaff(std::move(n), staffId, basicPay), researchAllowance(research) {}

    double pay() const override {
        return RegularStaff::pay() + researchAllowance;
    }
};

class LabAssistant : public RegularStaff {
public:
    LabAssistant(std::string n, int staffId, double basicPay)
        : RegularStaff(std::move(n), staffId, basicPay) {}
};

class GuestFaculty : public Staff {
    double hours;
    double rate;

public:
    GuestFaculty(std::string n, int staffId, double hrs, double hourlyRate)
        : Staff(std::move(n), staffId), hours(hrs), rate(hourlyRate) {}

    double pay() const override {
        return hours * rate;
    }
};

int main() {
    std::vector<Staff*> payroll = {
        new Professor("Dr. Rao", 101, 80000.0, 15000.0),
        new LabAssistant("Meera", 102, 35000.0),
        new GuestFaculty("Karthik", 103, 40.0, 1200.0)
    };

    for (const Staff* s : payroll) s->printSlip();
    for (Staff* s : payroll) delete s;
    return 0;
}