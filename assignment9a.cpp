#include<iostream>
using namespace std;

// Class to represent a party (customer)
class party {
    string name;   // Variable to store the name of the customer
    int phone;     // Variable to store the phone number of the customer
public:
    party *next;   // Pointer to the next party in the queue

    // Constructor to initialize next to NULL
    party(){
		next = NULL;
	}

    // Function to read customer details
    void read() {
        cout << "Enter the name of the customer: ";
        cin >> name;  // Input customer name
        cout << "Enter the Phone number: ";
        cin >> phone; // Input customer phone number
    }

    // Function to display customer details
    void display() {
        cout << "Name of customer is: " << name << endl; // Display name
        cout << "Phone number: " << phone;               // Display phone number
        cout << "\n";
    }
};

// Class to represent the queue of parties
class Queue {
    party *front, *rear; // Pointers to the front and rear of the queue
public:
    // Constructor to initialize the queue
    Queue() {
        front = rear = NULL; // Initially, both front and rear are NULL
    }

    // Function to create a new party node
    party* newNode() {
        return new party; // Allocate memory for a new party node
    }

    // Function to add a party to the queue
    void addParty() {
        party *nn = newNode(); // Create a new party node
        nn->read();            // Read customer details
        if (front == NULL) {   // If the queue is empty
            front = rear = nn;  // Set both front and rear to the new node
        } else {
            rear->next = nn;    // Link the new node at the end of the queue
            rear = nn;          // Update the rear pointer to the new node
        }
    }

    // Function to seat a party (remove from the queue)
    void SeatParty() {
        if (front == NULL) {  // If the queue is empty
            cout << "Queue is Empty";
        } else {
            party *temp;      // Temporary pointer to hold the front party
            temp = front;     // Store the current front
            front = front->next; // Move front to the next party
            delete(temp);     // Delete the old front
            if (front == NULL) { // If the queue is now empty
                rear = NULL;    // Set rear to NULL
            }
        }
    }

    // Function to display all parties in the queue
    void Display() {
        for (party *cn = front; cn != NULL; cn = cn->next) { // Traverse the queue
            cn->display(); // Display each party's details
        }
    }
};

// Main function to run the program
int main() {
    int choice; // Variable to store user choice
    Queue q;    // Create an instance of Queue

    while (true) { // Infinite loop for user interaction
        cout << "--Party Queue--" << endl; // Display menu header
        cout << "1. Add Customer to Waitlist" << endl; // Option to add customer
        cout << "2. Seat Party" << endl; // Option to seat party
        cout << "3. Display" << endl; // Option to display parties
        cout << "Enter your choice: ";
        cin >> choice; // Get user choice
        cout << "\n";

        switch (choice) {
            case 1: // If user chooses to add a customer
                q.addParty();
                break;
            case 2: // If user chooses to seat a party
                q.SeatParty();
                break;
            case 3: // If user chooses to display the queue
                q.Display();
                break;
            default: // If the user enters an invalid choice
                cout << "Invalid Choice" << endl;
        }
        cout << endl; // Print a new line for better formatting
    }
    return 0; 
}
