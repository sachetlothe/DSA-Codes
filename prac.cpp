#include <iostream>

using namespace std;

// Hash functions
int hash1(int key, int table_size) {
    return key % table_size; // Ensure index is within bounds
}

int hash2(int key) {
    return 2 + (key % 5); // Step size for collision resolution
}

// Hash table implementation
class HashTable {
public:
    int* table; // Pointer for dynamic array
    int table_size;

    HashTable(int size) {
        table_size = size;
        table = new int[table_size]; // Allocate memory for the table
        for (int i = 0; i < table_size; i++) {
            table[i] = -1; // Initialize with empty value
        }
    }

    ~HashTable() {
        delete[] table; // Free allocated memory
    }

    void insert(int key) {
        int index = hash1(key, table_size);
        int i = 0;

        while (table[index] != -1 && table[index] != key) {
            index = (hash1(key, table_size) + i * hash2(key)) % table_size;
            i++;
        }

        if (table[index] == -1) {
            table[index] = key;
            cout << "Key " << key << " inserted at index " << index << endl;
        } else {
            cout << "Key " << key << " already exists." << endl;
        }
    }

    void search(int key) {
        int index = hash1(key, table_size);
        int i = 0;

        while (table[index] != -1) {
            if (table[index] == key) {
                cout << "Key " << key << " found at index " << index << endl;
                return;
            }
            index = (hash1(key, table_size) + i * hash2(key)) % table_size;
            i++;
        }

        cout << "Key " << key << " not found." << endl;
    }

    void display() {
        cout << "Hash Table Contents:\n";
        for (int i = 0; i < table_size; i++) {
            cout << "Index " << i << ": " << (table[i] == -1 ? "EMPTY" : to_string(table[i])) << endl;
        }
    }
};

int main() {
    int table_size = 7; // Specify the table size
    HashTable ht(table_size);
    int choice, key;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                ht.insert(key);
                break;
            case 2:
                cout << "Enter key to search: ";
                cin >> key;
                ht.search(key);
                break;
            case 3:
                ht.display();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
