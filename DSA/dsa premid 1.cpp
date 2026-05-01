#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int MAX_ITEMS = 100;
class ItemType {
private:
    string name;
    string phone;
    string address;

public:
    ItemType() {
        name = "";
        phone = "";
        address = "";
    }

    void Initialize(string n, string p, string a) {
        name = n;
        phone = p;
        address = a;
    }

    string GetName() const { return name; }
    string GetPhone() const { return phone; }
    string GetAddress() const { return address; }

    void Print() const {
        cout << "Name: " << name << "\nPhone: " << phone << "\nAddress: " << address << "\n\n";
    }
    bool operator<(const ItemType& other) const {
        return name < other.name;
    }

    bool operator==(const ItemType& other) const {
        return name == other.name;
    }
};


class SortedType {
private:
    ItemType contacts[MAX_ITEMS];
    int length;

public:
    SortedType() {
        length = 0;
    }

    bool IsFull() const {
        return length == MAX_ITEMS;
    }

    bool IsEmpty() const {
        return length == 0;
    }

    int LengthIs() const {
        return length;
    }
    void InsertItem(ItemType item) {
        if (IsFull()) {
            cout << "Contact list is full!\n";
            return;
        }

        int pos = 0;
        while (pos < length && contacts[pos] < item) {
            pos++;
        }

        for (int i = length; i > pos; i--) {
            contacts[i] = contacts[i - 1];
        }

        contacts[pos] = item;
        length++;
        cout << "Contact added successfully!\n";
    }


    int SearchItem(string name) {
        for (int i = 0; i < length; i++) {
            if (contacts[i].GetName() == name) {
                return i;
            }
        }
        return -1;
    }


    void DeleteItem(string name) {
        int pos = SearchItem(name);
        if (pos == -1) {
            cout << "Contact not found!\n";
            return;
        }

        for (int i = pos; i < length - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        length--;
        cout << "Contact deleted successfully!\n";
    }


    void DisplayItems() {
        if (IsEmpty()) {
            cout << "No contacts to display.\n";
            return;
        }
        cout << "\n--- Contact List ---\n";
        for (int i = 0; i < length; i++) {
            contacts[i].Print();
        }
    }
};


bool isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return !name.empty();
}

bool isValidPhone(const string& phone) {
    if (phone.length() != 11) return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isValidAddress(const string& address) {
    return !address.empty();
}


int main() {
    SortedType contactList;
    int choice;

    do {
        cout << "\n--- Contact Manager ---\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Display All Contacts\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string name, phone, address;
            cout << "Enter Name: ";
            getline(cin, name);
            if (!isValidName(name)) {
                cout << "Invalid name! Only alphabets allowed.\n";
                continue;
            }
            cout << "Enter Phone (11 digits): ";
            getline(cin, phone);
            if (!isValidPhone(phone)) {
                cout << "Invalid phone! Must be 11 digits.\n";
                continue;
            }
            cout << "Enter Address: ";
            getline(cin, address);
            if (!isValidAddress(address)) {
                cout << "Invalid address! Cannot be empty.\n";
                continue;
            }

            ItemType newContact;
            newContact.Initialize(name, phone, address);
            contactList.InsertItem(newContact);

        }
        else if (choice == 2) {
            string name;
            cout << "Enter name to search: ";
            getline(cin, name);
            int index = contactList.SearchItem(name);
            if (index == -1)
                cout << "Contact not found.\n";
            else
                contactList.DisplayItems();

        }
        else if (choice == 3) {
            string name;
            cout << "Enter name to delete: ";
            getline(cin, name);
            contactList.DeleteItem(name);

        }
        else if (choice == 4) {
            contactList.DisplayItems();

        }
        else if (choice == 5) {
            cout << "Exiting program.\n";
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}