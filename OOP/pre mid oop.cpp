#include <iostream>
#include <cmath>
using namespace std;

// Question 1: Bank Account Management System 
class BankAccount {
private:
    int accountNumber;
    string name;
    double balance;
    static int totalAccounts;

public:
    BankAccount(int accNo, string accName, double accBalance) {
        accountNumber = accNo;
        name = accName;
        balance = accBalance;
        totalAccounts++;
    }

    ~BankAccount() {
        cout << "Account " << accountNumber << " is being closed.\n";
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount > balance)
            cout << "Insufficient balance!\n";
        else
            balance -= amount;
    }

    void display() const {
        cout << "Account No: " << accountNumber << ", Name: " << name << ", Balance: $" << balance << endl;
    }

    friend void transfer(BankAccount& from, BankAccount& to, double amount);

    static void showTotalAccounts() {
        cout << "Total accounts created: " << totalAccounts << endl;
    }
};

int BankAccount::totalAccounts = 0;

void transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount > from.balance)
        cout << "Insufficient funds for transfer!\n";
    else {
        from.balance -= amount;
        to.balance += amount;
        cout << "Transfer Successful!\n";
    }
}

//Question 2: Complex Number Calculator 
class Complex {
private:
    double real, imag;

public:
    Complex(double r = 0, double i = 0) {
        real = r;
        imag = i;
    }

    // Overload arithmetic operators
    Complex operator+(const Complex& c) { return Complex(real + c.real, imag + c.imag); }
    Complex operator-(const Complex& c) { return Complex(real - c.real, imag - c.imag); }
    Complex operator*(const Complex& c) { return Complex(real * c.real - imag * c.imag, real * c.imag + imag * c.real); }
    Complex operator/(const Complex& c) {
        return Complex(
            (real * c.real + imag * c.imag) / (c.real * c.real + c.imag * c.imag),
            (imag * c.real - real * c.imag) / (c.real * c.real + c.imag * c.imag)
        );
    }


    double magnitude() const { return sqrt(real * real + imag * imag); }

    // Overload relational operators
    bool operator==(const Complex& c) { return (real == c.real && imag == c.imag); }
    bool operator!=(const Complex& c) { return !(*this == c); }
    bool operator<(const Complex& c) { return magnitude() < c.magnitude(); }
    bool operator>(const Complex& c) { return magnitude() > c.magnitude(); }
    bool operator<=(const Complex& c) { return magnitude() <= c.magnitude(); }
    bool operator>=(const Complex& c) { return magnitude() >= c.magnitude(); }

    // Overload subscript operator
    double operator[](int index) const {
        if (index == 0)
            return real;
        else if (index == 1)
            return imag;
        else {
            cout << "Error: Invalid index. Use 0 for real, 1 for imaginary.\n";
            return 0;
        }
    }


    double operator()() const { return magnitude(); }

    // Overload stream operators
    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << c.real;
        if (c.imag >= 0) out << " + " << c.imag << "i";
        else out << " - " << -c.imag << "i";
        return out;
    }

    friend istream& operator>>(istream& in, Complex& c) {
        cout << "Enter real and imaginary parts: ";
        in >> c.real >> c.imag;
        return in;
    }
};

// Question 3: Student Record System 
class StudentRecord {
private:
    int studentID;
    string name;
    double GPA;
    static int totalStudents;

public:
    StudentRecord(int id = 0, string n = "", double gpa = 0.0) {
        studentID = id;
        name = n;
        GPA = gpa;
        totalStudents++;
    }

    void setGPA(double gpa) { GPA = gpa; }
    void display() const { cout << "ID: " << studentID << ", Name: " << name << ", GPA: " << GPA << endl; }
    static void showTotalStudents() { cout << "Total students: " << totalStudents << endl; }
};

int StudentRecord::totalStudents = 0;

// Main Function with Menu 
int main() {
    int choice;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Bank Account Management\n";
        cout << "2. Complex Number Calculator\n";
        cout << "3. Student Record System\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            BankAccount acc1(101, "Alice", 5000), acc2(102, "Bob", 3000);
            acc1.deposit(2000);
            acc1.withdraw(1000);
            transfer(acc1, acc2, 1500);
            acc1.display();
            acc2.display();
            BankAccount::showTotalAccounts();
            break;
        }
        case 2: {
            Complex c1, c2;
            cin >> c1 >> c2;
            cout << "Sum: " << c1 + c2 << endl;
            cout << "Difference: " << c1 - c2 << endl;
            cout << "Product: " << c1 * c2 << endl;
            cout << "Quotient: " << c1 / c2 << endl;
            cout << "Real part of c1: " << c1[0] << endl;
            cout << "Imaginary part of c1: " << c1[1] << endl;
            cout << "Magnitude of c1: " << c1() << endl;
            cout << "Are c1 and c2 equal? " << (c1 == c2 ? "Yes" : "No") << endl;
            cout << "Is c1 greater than c2? " << (c1 > c2 ? "Yes" : "No") << endl;
            break;
        }
        case 3: {
            StudentRecord students[2] = { {1, "David", 3.5}, {2, "Emma", 3.8} };
            students[1].setGPA(4.0);
            for (const auto& s : students) s.display();
            StudentRecord::showTotalStudents();
            break;
        }
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}