#include <iostream>
using namespace std;

class Node {
public:
	int coefficient;
	int exponent;
	Node *next;
	Node() {
    	next = NULL;
	}
};

class Polynomial {
public:
	Node *head;
	Polynomial() {
    	head = NULL;
	}
	void insertTerm(int coef, int exp) {
    	Node *newNode = new Node();
    	newNode->coefficient = coef;
    	newNode->exponent = exp;
    	if (head == NULL || head->exponent < exp) {
        	newNode->next = head;
        	head = newNode;
    	} else {
        	Node *temp = head;
        	while (temp->next != NULL && temp->next->exponent > exp) {
            	temp = temp->next;
        	}
        	if (temp->next != NULL && temp->next->exponent == exp) {
            	temp->next->coefficient += coef;
            	delete newNode;
        	} else {
            	newNode->next = temp->next;
            	temp->next = newNode;
        	}
    	}
	}
	void display() {
    	if (head == NULL) {
        	cout << "0" << endl;
        	return;
    	}
    	Node *temp = head;
    	while (temp != NULL) {
        	if (temp->coefficient > 0 && temp != head) {
            	cout << "+";
        	}
        	cout << temp->coefficient << "X^" << temp->exponent;
        	temp = temp->next;
    	}
    	cout << endl;
	}
	Polynomial multiply(Polynomial &p2) {
    	Polynomial result;
    	Node *p1Node = this->head;
    	while (p1Node != NULL) {
        	Node *p2Node = p2.head;
        	while (p2Node != NULL) {
            	int coef = p1Node->coefficient * p2Node->coefficient;
            	int exp = p1Node->exponent + p2Node->exponent;
            	result.insertTerm(coef, exp);
            	p2Node = p2Node->next;
        	}
        	p1Node = p1Node->next;
    	}
    	return result;
	}
};


int main() {
	Polynomial p1, p2, result;
	int numTerms1, numTerms2;
	cout << "Enter the Number of Terms for Polynomial 1: ";
	cin >> numTerms1;
	for (int i = 0; i < numTerms1; i++) {
    	int coef, exp;
    	cout << "Enter coefficient and exponent for the term: ";
    	cin >> coef >> exp;
    	p1.insertTerm(coef, exp);
	}
	cout << "Enter the number of Terms for Polynomial 2: ";
	cin >> numTerms2;
	for (int i = 0; i < numTerms2; i++) {
    	int coef, exp;
    	cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
    	cin >> coef >> exp;
    	p2.insertTerm(coef, exp);
	}

	cout << "Polynomial 1: ";
	p1.display();
    
	cout << "Polynomial 2: ";
	p2.display();
    
	result = p1.multiply(p2);
    
	cout << "The Product of Polynomials: ";
	result.display();
    
	return 0;
}


