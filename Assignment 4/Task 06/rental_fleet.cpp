#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct ServiceDate {
    int day, month, year;
};

class Vehicle {
protected:
    std::string regNo;
    double dailyRate;
    bool rented = false;

public:
    Vehicle(std::string reg, double rate) : regNo(std::move(reg)), dailyRate(rate) {}
    virtual ~Vehicle() = default;

    virtual std::string type() const = 0;
    virtual double calculateCharge(int days, double usage) const = 0;

    bool rent() {
        if (rented) return false;
        rented = true;
        return true;
    }

    double returnVehicle(int days, double usage, int lateDays) {
        rented = false;
        double base = calculateCharge(days, usage);
        double latePenalty = lateDays * (dailyRate * 0.25);
        return base + latePenalty;
    }

    std::string getRegNo() const { return regNo; }
};

class Bicycle : public Vehicle {
public:
    Bicycle(std::string reg, double rate) : Vehicle(std::move(reg), rate) {}
    std::string type() const override { return "Bicycle"; }
    double calculateCharge(int days, double) const override { return days * dailyRate; }
};

class MotorVehicle : public Vehicle {
protected:
    double level;
    ServiceDate nextService;

public:
    MotorVehicle(std::string reg, double rate, double lvl, ServiceDate srv)
        : Vehicle(std::move(reg), rate), level(lvl), nextService(srv) {}
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(std::string reg, double rate, double lvl, ServiceDate srv)
        : MotorVehicle(std::move(reg), rate, lvl, srv) {}
    std::string type() const override { return "TwoWheeler"; }
    double calculateCharge(int days, double litresUsed) const override {
        return (days * dailyRate) + (litresUsed * 102.0);
    }
};

class Car : public MotorVehicle {
    int seats;

public:
    Car(std::string reg, double rate, double lvl, ServiceDate srv, int seatCap)
        : MotorVehicle(std::move(reg), rate, lvl, srv), seats(seatCap) {}
    std::string type() const override { return "Car(" + std::to_string(seats) + "-seater)"; }
    double calculateCharge(int days, double litresUsed) const override {
        return (days * dailyRate) + (litresUsed * 105.0);
    }
};

class ElectricCar : public MotorVehicle {
    int seats;
    double batteryKWh;

public:
    ElectricCar(std::string reg, double rate, double lvl, ServiceDate srv, int seatCap, double kwh)
        : MotorVehicle(std::move(reg), rate, lvl, srv), seats(seatCap), batteryKWh(kwh) {}
    std::string type() const override { return "ElectricCar(" + std::to_string((int)batteryKWh) + "kWh)"; }
    double calculateCharge(int days, double kwhUsed) const override {
        return (days * dailyRate) + (kwhUsed * 14.0);
    }
};

class ElectricBus : public MotorVehicle {
    int passengerCap;

public:
    ElectricBus(std::string reg, double rate, double lvl, ServiceDate srv, int cap)
        : MotorVehicle(std::move(reg), rate, lvl, srv), passengerCap(cap) {}
    std::string type() const override { return "ElectricBus(" + std::to_string(passengerCap) + "-pax)"; }
    double calculateCharge(int days, double kwhUsed) const override {
        return (days * dailyRate) + (kwhUsed * 12.5);
    }
};

int main() {
    std::vector<Vehicle*> fleet = {
        new Bicycle("CYC-01", 200.0),
        new TwoWheeler("TN01-AB1234", 600.0, 85.0, {15, 12, 2026}),
        new Car("TN01-CD5678", 2200.0, 90.0, {20, 1, 2027}, 5),
        new ElectricCar("TN01-EV9999", 2800.0, 95.0, {10, 2, 2027}, 5, 60.0),
        new ElectricBus("TN01-EB7777", 7500.0, 100.0, {1, 3, 2027}, 40)
    };

    std::cout << std::fixed << std::setprecision(2);
    for (Vehicle* v : fleet) {
        v->rent();
        std::cout << v->type() << " [" << v->getRegNo() << "] -> Bill: Rs "
                  << v->returnVehicle(3, 25.0, 1) << '\n';
    }

    for (Vehicle* v : fleet) delete v;
    return 0;
}