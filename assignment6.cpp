#include<iostream>
using namespace std;

// Node class to represent each term in the polynomial
class Node {
    public:
    int coefficient;  // Coefficient of the term
    int exponent;     // Exponent of the term
    Node *next;       // Pointer to the next node (term)

    // Constructor to initialize the next pointer as NULL
    Node() {
        next = NULL;
    }
};

// Polynomial class to represent and manipulate polynomials
class Polynomial {
    public:
    Node *head;  // Pointer to the head node (first term) of the polynomial

    // Constructor to initialize head pointer as NULL
    Polynomial() {
        head = NULL;
    }

    // Function to insert a term into the polynomial in sorted order by exponent
    void insertTerm(int coef, int exp) {
        Node* newNode = new Node();  // Create a new node for the term
        newNode->coefficient = coef; // Set the coefficient
        newNode->exponent = exp;     // Set the exponent

        // If the polynomial is empty or the exponent of the new term is greater than the head term
        if (head == NULL || head->exponent < exp) {
            newNode->next = head;  // Insert the new term at the beginning
            head = newNode;        // Update the head to point to the new node
        }
        // Insert the term in the correct position (sorted by exponent)
        else {
            Node* temp = head;
            // Traverse the polynomial until the correct position is found
            while (temp->next != NULL && temp->next->exponent > exp) {
                temp = temp->next;
            }

            // If the term with the same exponent exists, add the coefficients
            if (temp->next != NULL && temp->next->exponent == exp) {
                temp->next->coefficient += coef;  // Combine the coefficients
                delete newNode;                   // Delete the newly created node as it is not needed
            }
            // Otherwise, insert the new term in the correct position
            else {
                newNode->next = temp->next;
                temp->next = newNode;
            }
        }
    }

    // Function to display the polynomial
    void display() {
        if (head == NULL) {
            cout << "0" << endl;  // If the polynomial is empty, print 0
            return;
        }

        Node* temp = head;
        // Traverse the polynomial and print each term
        while (temp != NULL) {
            if (temp->coefficient > 0 && temp != head) {
                cout << "+";  // Print "+" sign for positive coefficients (except the first term)
            }
            cout << temp->coefficient << "X^" << temp->exponent;  // Print term in the form coef * X^exp
            temp = temp->next;  // Move to the next term
        }
        cout << endl;
    }

    // Function to add two polynomials and return the resulting polynomial
    Polynomial add(Polynomial& p2) {
        Polynomial result;  // Create a new polynomial to store the result
        Node* p1Node = this->head;  // Pointer to traverse the first polynomial
        Node* p2Node = p2.head;     // Pointer to traverse the second polynomial

        // Traverse both polynomials and add terms with the same exponent
        while (p1Node != NULL && p2Node != NULL) {
            if (p1Node->exponent > p2Node->exponent) {
                // Add the term from the first polynomial if its exponent is greater
                result.insertTerm(p1Node->coefficient, p1Node->exponent);
                p1Node = p1Node->next;  // Move to the next term in the first polynomial
            }
            else if (p1Node->exponent < p2Node->exponent) {
                // Add the term from the second polynomial if its exponent is greater
                result.insertTerm(p2Node->coefficient, p2Node->exponent);
                p2Node = p2Node->next;  // Move to the next term in the second polynomial
            }
            else {
                // Add the terms with the same exponent by summing their coefficients
                result.insertTerm(p1Node->coefficient + p2Node->coefficient, p1Node->exponent);
                p1Node = p1Node->next;  // Move to the next term in the first polynomial
                p2Node = p2Node->next;  // Move to the next term in the second polynomial
            }
        }

        // If there are any remaining terms in the first polynomial, add them to the result
        while (p1Node != NULL) {
            result.insertTerm(p1Node->coefficient, p1Node->exponent);
            p1Node = p1Node->next;
        }

        // If there are any remaining terms in the second polynomial, add them to the result
        while (p2Node != NULL) {
            result.insertTerm(p2Node->coefficient, p2Node->exponent);
            p2Node = p2Node->next;
        }

        return result;  // Return the resulting polynomial after addition
    }
};

int main() {
    Polynomial p1, p2, result;  // Create two polynomials and a result polynomial
    int numTerms1, numTerms2;   // Number of terms in each polynomial

    // Input for the first polynomial
    cout << "Enter the Number of Terms for Polynomial 1: ";
    cin >> numTerms1;
    for (int i = 0; i < numTerms1; i++) {
        int coef, exp;
        cout << "Enter coefficient and exponent for the term: ";
        cin >> coef >> exp;
        p1.insertTerm(coef, exp);  // Insert each term into polynomial 1
    }

    // Input for the second polynomial
    cout << "Enter the number of Terms for Polynomial 2: ";
    cin >> numTerms2;
    for (int i = 0; i < numTerms2; i++) {
        int coef, exp;
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        cin >> coef >> exp;
        p2.insertTerm(coef, exp);  // Insert each term into polynomial 2
    }

    // Display the first polynomial
    cout << "Polynomial 1: ";
    p1.display();

    // Display the second polynomial
    cout << "Polynomial 2: ";
    p2.display();

    // Add the two polynomials and store the result
    result = p1.add(p2);

    // Display the result of the addition
    cout << "The Sum of Polynomials: ";
    result.display();

    return 0;
}
