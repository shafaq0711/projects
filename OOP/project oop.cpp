#include <iostream>
#include <cmath>
using namespace std;

// Function to print UML Diagram with values
void printUMLDiagram(int id, string name, double gpa, int total) {
    cout << "\n+-----------------------------+\n";
    cout << "|        StudentRecord       |\n";
    cout << "+-----------------------------+\n";
    cout << "| - studentID: int           |\n";
    cout << "| - name: string             |\n";
    cout << "| - GPA: double              |\n";
    cout << "| - totalStudents: static int|\n";
    cout << "+-----------------------------+\n";
    cout << "| + StudentRecord(id: int, n: string, gpa: double) |\n";
    cout << "| + setGPA(gpa: double): void  |\n";
    cout << "| + display(): void            |\n";
    cout << "| + showTotalStudents(): static void |\n";
    cout << "+-----------------------------+\n";
    cout << "| ID: " << id << " | Name: " << name << " | GPA: " << gpa << " | Total Students: " << total << " |\n";
    cout << "+-----------------------------+\n\n";
}

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

    void deposit(double amount) { balance += amount; }
    void withdraw(double amount) {
        if (amount > balance)
            cout << "Insufficient balance!\n";
        else
            balance -= amount;
    }
    void display() const { cout << "Account No: " << accountNumber << ", Name: " << name << ", Balance: $" << balance << endl; }
    static void showTotalAccounts() { cout << "Total accounts created: " << totalAccounts << endl; }
};
int BankAccount::totalAccounts = 0;

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
    int getID() const { return studentID; }
    string getName() const { return name; }
    double getGPA() const { return GPA; }
    static int getTotalStudents() { return totalStudents; }
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
            int accNo;
            string accName;
            double accBalance;
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Account Holder Name: ";
            cin >> accName;
            cout << "Enter Initial Balance: ";
            cin >> accBalance;

            BankAccount acc(accNo, accName, accBalance);
            double depositAmount, withdrawAmount;
            cout << "Enter amount to deposit: ";
            cin >> depositAmount;
            acc.deposit(depositAmount);

            cout << "Enter amount to withdraw: ";
            cin >> withdrawAmount;
            acc.withdraw(withdrawAmount);

            acc.display();
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
            StudentRecord students[4] = { {1, "Dawood", 3.5}, {2, "Emman", 3.8}, {2, "Esha", 2.5}, {2, "Aman", 3.0} };

            for (const auto& s : students) {
                printUMLDiagram(s.getID(), s.getName(), s.getGPA(), StudentRecord::getTotalStudents());
            }

            char updateChoice;
            do {
                cout << "Do you want to update a student's GPA? (y/n): ";
                cin >> updateChoice;

                if (updateChoice == 'y' || updateChoice == 'Y') {
                    int updateID;
                    double newGPA;
                    cout << "Enter Student ID to update GPA: ";
                    cin >> updateID;
                    cout << "Enter new GPA: ";
                    cin >> newGPA;

                    bool found = false;
                    for (auto& s : students) {
                        if (s.getID() == updateID) {
                            s.setGPA(newGPA);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Student ID not found.\n";
                    }

                    for (const auto& s : students) {
                        printUMLDiagram(s.getID(), s.getName(), s.getGPA(), StudentRecord::getTotalStudents());
                    }
                }
            } while (updateChoice == 'y' || updateChoice == 'Y');

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