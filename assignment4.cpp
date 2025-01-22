#include <iostream>
#include <string>
using namespace std;

// Node class representing each character in the text
class Node {
public:
    char data;  // Stores the character
    Node* prev; // Pointer to the previous node
    Node* next; // Pointer to the next node

    // Constructor to initialize the node with a character
    Node(char c) : data(c), prev(NULL), next(NULL) {}
};

// TextEditor class for managing the doubly linked list of characters
class TextEditor {
private:
    Node* head;   // Pointer to the start of the text (first node)
    Node* tail;   // Pointer to the end of the text (last node)
    Node* cursor; // Pointer to the current position of the cursor

public:
    // Constructor to initialize an empty text editor
    TextEditor() : head(NULL), tail(NULL), cursor(NULL) {}

    // Function to insert text into the editor at the current cursor position
    void insertText(string& text) {
        for (char c : text) {
            Node* newNode = new Node(c); // Create a new node for each character
            if (!head) {  // If the text editor is empty, initialize it with the new node
                head = tail = cursor = newNode;
            } else {
                // If text already exists, insert the new node at the cursor position
                if (cursor) {
                    newNode->prev = cursor;
                    newNode->next = cursor->next;
                    if (cursor->next) {
                        cursor->next->prev = newNode; // Adjust the next node's previous pointer
                    }
                    cursor->next = newNode; // Insert new node after the cursor
                    cursor = newNode;       // Move the cursor to the new node
                } else {
                    // If the cursor is at the end, append the new node to the tail
                    newNode->prev = tail;
                    tail->next = newNode;
                    tail = newNode;
                }
            }
        }
    }

    // Function to delete 'numChars' characters before the cursor
    void deleteText(int numChars) {
        while (numChars > 0 && cursor) {
            Node* toDelete = cursor; // Pointer to the node to be deleted
            if (cursor->prev) {
                cursor->prev->next = cursor->next; // Adjust the previous node's next pointer
            } else {
                head = cursor->next; // If deleting the head node, move the head pointer
            }
            if (cursor->next) {
                cursor->next->prev = cursor->prev; // Adjust the next node's previous pointer
            } else {
                tail = cursor->prev; // If deleting the tail node, move the tail pointer
            }
            cursor = cursor->prev; // Move the cursor to the previous node
            delete toDelete;       // Delete the node
            numChars--;            // Decrease the number of characters to delete
        }
    }

    // Function to display the current text
    void displayText() {
        Node* current = head; // Start from the head node
        while (current) {
            cout << current->data; // Print each character
            current = current->next; // Move to the next node
        }
        cout << endl;
    }

    // Function to search for a substring in the text
    void searchText(string& substring) {
        Node* current = head; // Start from the head node
        int index = 0;        // Index to track the position in the text
        bool found = false;

        // Traverse through the text
        while (current) {
            Node* temp = current; // Temporary pointer to check for matching substring
            int matchIndex = 0;

            // Check if the substring matches starting from the current node
            while (temp && matchIndex < substring.length() && temp->data == substring[matchIndex]) {
                temp = temp->next; // Move to the next node if characters match
                matchIndex++;
            }

            // If the entire substring is found
            if (matchIndex == substring.length()) {
                cout << "Found at index: " << index << endl;
                found = true;
            }

            current = current->next; // Move to the next node in the text
            index++; // Increment the index
        }

        // If the substring is not found
        if (!found) {
            cout << "Not found" << endl;
        }
    }

    // Function to print the text in reverse order
    void printReverse() {
        Node* current = tail; // Start from the tail node
        while (current) {
            cout << current->data; // Print each character
            current = current->prev; // Move to the previous node
        }
        cout << endl;
    }

    // Destructor to clean up memory
    ~TextEditor() {
        while (head) {
            Node* temp = head;
            head = head->next; // Move the head pointer to the next node
            delete temp;       // Delete the current node
        }
    }
};

int main() {
    TextEditor editor; // Create a TextEditor object
    int choice;        // Variable to store user menu choice
    string text;       // Variable to store input text
    int numChars;      // Variable to store the number of characters to delete

    do {
        // Display menu options
        cout << "\nMenu:\n";
        cout << "1. Insert Text\n";
        cout << "2. Delete Text\n";
        cout << "3. Display Text\n";
        cout << "4. Search Text\n";
        cout << "5. Print Text in Reverse\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore the newline left in the input buffer after taking choice

        // Switch case to handle user choices
        switch (choice) {
            case 1:
                // Insert text into the editor
                cout << "Enter text to insert: ";
                getline(cin, text);
                editor.insertText(text);
                break;

            case 2:
                // Delete a specified number of characters from the editor
                cout << "Enter the number of characters to delete: ";
                cin >> numChars;
                editor.deleteText(numChars);
                break;

            case 3:
                // Display the current text in the editor
                cout << "Current text: ";
                editor.displayText();
                break;

            case 4:
                // Search for a substring in the text
                cout << "Enter text to search: ";
                getline(cin, text);
                editor.searchText(text);
                break;

            case 5:
                // Print the text in reverse order
                cout << "Text in reverse: ";
                editor.printReverse();
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5); // Exit the loop after option 5 is selected

    return 0;
}
