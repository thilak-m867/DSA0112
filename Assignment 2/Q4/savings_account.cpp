#include <iostream>
#include <string>

class SavingsAccount {
private:
    static const int MAX_TXN = 10;
    std::string accountNo;
    double balance;
    double transactions[MAX_TXN];
    int count;

    void recordTransaction(double amount) {
        if (count < MAX_TXN) {
            transactions[count] = amount;
        } else {
            for (int i = 1; i < MAX_TXN; ++i) {
                transactions[i - 1] = transactions[i];
            }
            transactions[MAX_TXN - 1] = amount;
        }
        ++count;
    }

public:
    SavingsAccount(const std::string& acc, double initialBalance)
        : accountNo(acc), balance(initialBalance), count(0) {}

    void deposit(double amount);
    bool withdraw(double amount);
    void miniStatement() const;
};

void SavingsAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        recordTransaction(+amount);
    }
}

bool SavingsAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        recordTransaction(-amount);
        return true;
    }
    return false;
}

void SavingsAccount::miniStatement() const {
    std::cout << "=== Mini-Statement for Account: " << accountNo << " ===\n";
    int stored = (count < MAX_TXN) ? count : MAX_TXN;
    for (int i = 0; i < stored; ++i) {
        std::cout << (i + 1) << ". " << (transactions[i] >= 0 ? "+" : "")
                  << transactions[i] << '\n';
    }
    std::cout << "Current Balance: " << balance << "\n\n";
}

int main() {
    SavingsAccount acc("SB-10045", 5000.0);
    for (int i = 1; i <= 12; ++i) {
        if (i % 2 == 1) acc.deposit(i * 100.0);
        else acc.withdraw(i * 50.0);
    }
    acc.miniStatement();
    return 0;
}