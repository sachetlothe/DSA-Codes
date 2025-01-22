#include <iostream>
using namespace std;

// Class to represent a route between two locations
class route {
    string source, dest;  // Variables to store the source and destination locations
    int distance;         // Variable to store the distance between source and destination
    route *next;          // Pointer to the next route (for circular linked list)

public:
    // Constructor to initialize the 'next' pointer as NULL
    route() {
        next = NULL;
    }

    // Function to read route details (source, destination, and distance)
    void read() {
        cout << "Enter Source: ";
        cin >> source;
        cout << "Enter Destination: ";
        cin >> dest;
        cout << "Enter Distance (in kms): ";
        cin >> distance;
    }

    // Function to display route details (source, destination, and distance)
    void display() {
        cout << "Source: " << source << "  ";
        cout << "Destination: " << dest << "  ";
        cout << "Distance (in kms): " << distance << endl;
    }

    // Declaring the 'route_nav' class as a friend so that it can access private members
    friend class route_nav;
};

// Class to manage a circular linked list of routes
class route_nav {
public:
    route *tail;  // Pointer to the last node (tail) in the circular linked list

    // Constructor to initialize the 'tail' pointer as NULL
    route_nav() {
        tail = NULL;
    }

    // Function to add a new route to the circular linked list
    void addRoute() {
        route *newRoute = new route;  // Create a new route node
        newRoute->read();             // Read route details from the user

        // If the list is empty, point the tail and the new node to itself (circular list)
        if (tail == NULL) {
            tail = newRoute;
            tail->next = newRoute;
        } else {
            // Insert the new route at the beginning of the circular list
            newRoute->next = tail->next;
            tail->next = newRoute;
            tail = newRoute;  // Move the tail to the new node (new last route)
        }
    }

    // Function to delete a route based on source and destination
    void deleteRoute() {
        if (tail == NULL) {  // If no routes exist
            cout << "No routes to delete.\n";
            return;
        }

        route *p = tail;       // Pointer to the current route
        route *t = tail->next; // Pointer to the route we want to delete
        string src, desti;     // Variables to store source and destination input

        // Prompt user for the source and destination of the route to delete
        cout << "Enter source: ";
        cin >> src;
        cout << "Enter destination: ";
        cin >> desti;

        // Traverse the circular list to find and delete the route
        do {
            if (t->source == src && t->dest == desti) {
                // If the route to be deleted is the only one in the list
                if (t == tail) {
                    if (tail == tail->next) {
                        delete t;
                        tail = nullptr;  // Empty the list after deleting
                        return;
                    } else {
                        p->next = t->next;
                        tail = p;  // Update tail and delete the current node
                        delete t;
                        return;
                    }
                } else {
                    // Delete a non-tail route
                    p->next = t->next;
                    delete t;
                    return;
                }
            } else {
                // Move to the next node
                p = t;
                t = t->next;
            }
        } while (t != tail->next);  // Loop until we complete one full cycle of the circular list

        // If the specified route does not exist
        cout << "Route does not exist.\n";
    }

    // Function to display all routes in the circular linked list
    void displayRoutes() {
        if (!tail) {  // If no routes are available to display
            cout << "No routes to display.\n";
            return;
        }

        route *temp = tail->next;  // Start from the route next to the tail
        do {
            temp->display();       // Display the current route's details
            temp = temp->next;     // Move to the next route
        } while (temp != tail->next);  // Continue until we reach the starting point
    }
};

int main() {
    route_nav nav;  // Create a route_nav object to manage routes
    int choice;     // Variable to store user menu choice

    // Infinite loop to keep displaying the menu until the program is manually stopped
    while (true) {
        // Display the menu options
        cout << "\nMenu:\n";
        cout << "1. Add Route\n";
        cout << "2. Remove Route\n";
        cout << "3. Display All Routes\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Switch case to handle the user's menu choice
        switch (choice) {
            case 1:
                // Add a new route
                nav.addRoute();
                break;
            case 2:
                // Delete an existing route
                nav.deleteRoute();
                break;
            case 3:
                // Display all routes
                nav.displayRoutes();
                break;
            default:
                // If the user enters an invalid option
                cout << "Invalid choice. Try again.\n";
                break;
        }
    }

    return 0;
}
