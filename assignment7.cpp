#include <iostream>
using namespace std;

// Node class represents each web page in the browser history
class Node {
    string addr;   // Stores the address (URL) of the page
public:
    Node* next;    // Pointer to the next node (page) in the stack

    // Constructor to initialize the next pointer to NULL
    Node() : next(NULL) {}

    // Function to read the address (URL) of the page from user input
    void readAddr() {
        cout << "Enter address: ";
        cin >> addr;
    }

    // Function to display the address (URL) of the page
    void displayAddr() {
        cout << addr << endl;
    }
};

// Browser History Stack (BHS) class, simulating the browser history using a stack
class BHS {
    Node* top;  // Pointer to the top of the stack (most recently visited page)
public:
    // Constructor to initialize the top pointer to NULL
    BHS() : top(NULL) {}

    // Function to visit a new page (push operation in stack)
    void VisitNewPage() {
        Node* nn = new Node;     // Create a new node for the new page
        nn->readAddr();          // Read the address of the new page from the user
        nn->next = top;          // Set the new node's next pointer to the current top
        top = nn;                // Update the top to point to the new node
        cout << "New page visited.\n";
    }

    // Function to navigate back to the previous page (pop operation in stack)
    void NavigateBack() {
        if (top != NULL) {       // Check if there are pages in the history
            Node* temp = top;    // Temporary pointer to hold the current top
            cout << "Navigating back to: ";
            temp->displayAddr(); // Display the address of the current top page
            top = top->next;     // Move the top to the next node (previous page)
            delete temp;         // Delete the old top node
        } else {
            cout << "Stack is Empty. Cannot navigate back.\n"; // If stack is empty
        }
    }

    // Function to display the current page (peek operation in stack)
    void ShowCurrentPage() {
        if (top != NULL) {       // Check if there is a current page
            cout << "Current page is: ";
            top->displayAddr();  // Display the address of the current page
        } else {
            cout << "No current page. History is empty.\n"; // If stack is empty
        }
    }

    // Function to check if the history is empty (isEmpty function)
    bool Empty() {
        return top == NULL;      // Returns true if the top is NULL (stack is empty)
    }
};

int main() {
    BHS his;  // Create a Browser History Stack object
    int choice;

    // Menu-driven program to simulate browser history functionality
    do {
        cout << "\n--- Browser History Menu ---\n";
        cout << "1. Visit New Page\n";
        cout << "2. Navigate Back\n";
        cout << "3. Show Current Page\n";
        cout << "4. Check if History is Empty\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Execute the selected operation based on user input
        switch (choice) {
            case 1:
                his.VisitNewPage();  // Visit a new page (push to stack)
                break;
            case 2:
                his.NavigateBack();  // Navigate back to the previous page (pop from stack)
                break;
            case 3:
                his.ShowCurrentPage();  // Show the current page (peek at the top of the stack)
                break;
            case 4:
                // Check if the browser history stack is empty
                if (his.Empty()) {
                    cout << "History is Empty.\n";
                } else {
                    cout << "History is Not Empty.\n";
                }
                break;
            default:
                cout << "Invalid choice. Please try again.\n";  // Handle invalid menu choices
        }
    } while (choice != 4);  // Exit the program when choice 4 is selected

    return 0;
}
