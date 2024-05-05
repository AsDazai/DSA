#include <iostream>
#include <string>
#define TABLE_SIZE 5
using namespace std;


struct Client {
    string name;
    string phoneNumber;
};

class HashTable {
public:
    Client table[TABLE_SIZE]; 
    bool occupied[TABLE_SIZE]; 

    int hashFunction(const string& key) {
        int hash = 0;
        for (int i = 0; i<key.size(); i++) {
            char ch = key[i];
            hash += ch;
        }
        return hash % TABLE_SIZE;
    }

    int linearProbe(int index) {
        while (occupied[index]) {
            index = (index + 1) % TABLE_SIZE; 
        }
        return index;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            occupied[i] = false; 
        }
    }

    void insert(const string& name, const string& phoneNumber) {
        int index = hashFunction(name);
        index = linearProbe(index); 
        table[index] = {name, phoneNumber}; 
        occupied[index] = true; 
    }

    void displayTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (occupied[i]) {
                cout << "Slot " << i << ": " << table[i].name << " - " << table[i].phoneNumber << endl;
            } else {
                cout << "Slot " << i << ": Empty" << endl;
            }
        }
    }
};

int main() {
    HashTable telephoneBook;
    string name, phoneNumber;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        cout << "Enter client name: ";
        cin >> name;
        cout << "Enter client phone number: ";
        cin >> phoneNumber;
        telephoneBook.insert(name, phoneNumber);
    }
    cout << "\nTelephone Book Hash Table:\n";
    telephoneBook.displayTable();
    return 0;
}
