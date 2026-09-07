#include <iostream>
#include <string>
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;

public:
    explicit UpiPayment(const string& upiId) : upiId(upiId) {}

    bool pay(double amount) override {
        cout << "Processing UPI payment of Rs. " << amount << "...\n";
        cout << "UPI ID: " << upiId << '\n';
        cout << "Enter 1 for successful payment, 2 for failed payment: ";

        int choice;
        cin >> choice;

        return choice == 1;
    }

    string getMethodName() const override {
        return "UPI";
    }
};

class CardPayment : public Payment {
private:
    string cardNumber;

public:
    explicit CardPayment(const string& cardNumber)
        : cardNumber(cardNumber) {}

    bool pay(double amount) override {
        cout << "Processing Card payment of Rs. " << amount << "...\n";
        cout << "Enter 1 for successful payment, 2 for failed payment: ";

        int choice;
        cin >> choice;

        return choice == 1;
    }

    string getMethodName() const override {
        return "CARD";
    }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Cash payment amount: Rs. " << amount << '\n';
        cout << "Enter 1 if cash received, 2 if payment failed: ";

        int choice;
        cin >> choice;

        return choice == 1;
    }

    string getMethodName() const override {
        return "CASH";
    }
};
