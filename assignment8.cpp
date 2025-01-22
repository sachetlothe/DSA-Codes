#include <iostream>
using namespace std;

// Function to define precedence of operators
int precedence(char c) {
	if (c == '^') return 3;
	if (c == '%' || c == '*') return 2;
	if (c == '+' || c == '-') return 1;
	return -1;
}

// Function to convert infix expression to postfix
void InfixToPostfix(const char* infix, char* postfix) {
	char stack[100];
	int top = -1;
	int j = 0;

	for (int i = 0; infix[i] != '\0'; i++) {
    	char c = infix[i];

    	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        	postfix[j++] = c; // Add operands to postfix
    	} else if (c == '(') {
        	stack[++top] = c; // Push '(' onto stack
    	} else if (c == ')') {
        	while (top != -1 && stack[top] != '(') {
            	postfix[j++] = stack[top--]; // Pop from stack to postfix
        	}
        	top--; // Remove '('
    	} else { // Operator
        	while (top != -1 && (precedence(c) <= precedence(stack[top]))) {
            	postfix[j++] = stack[top--]; // Pop operators from stack to postfix
        	}
        	stack[++top] = c; // Push current operator onto stack
    	}
	}

	while (top != -1) {
    	postfix[j++] = stack[top--]; // Pop remaining operators
	}
	postfix[j] = '\0'; // Null-terminate postfix string
}

// Function to convert infix expression to prefix
void InfixToPrefix(const char* infix, char* prefix) {
	char reversed[100];
	char postfix[100];
	int len = 0;

	// Reverse the infix expression
	for (int i = 0; infix[i] != '\0'; i++) {
    	len++;
	}

	for (int i = 0; i < len; i++) {
    	if (infix[len - 1 - i] == '(') {
        	reversed[i] = ')';
    	} else if (infix[len - 1 - i] == ')') {
        	reversed[i] = '(';
    	} else {
        	reversed[i] = infix[len - 1 - i];
    	}
	}
	reversed[len] = '\0'; // Null-terminate reversed string

	// Convert reversed infix to postfix
	InfixToPostfix(reversed, postfix);

	// Reverse the postfix to get prefix
	len = 0;
	while (postfix[len] != '\0') {
    	len++;
	}

	for (int i = 0; i < len; i++) {
    	prefix[i] = postfix[len - 1 - i];
	}
	prefix[len] = '\0'; // Null-terminate prefix string
}

// Function to evaluate postfix expression
double evaluatePostfix(const char* postfix) {
	double stack[100];
	int top = -1;

	for (int i = 0; postfix[i] != '\0'; i++) {
    	char c = postfix[i];

    	if (c >= '0' && c <= '9') {
        	stack[++top] = c - '0'; // Convert char to int and push onto stack
    	} else { // Operator
        	double operand2 = stack[top--];
        	double operand1 = stack[top--];

        	switch (c) {
            	case '+': stack[++top] = operand1 + operand2; break;
            	case '-': stack[++top] = operand1 - operand2; break;
            	case '*': stack[++top] = operand1 * operand2; break;
            	case '/': stack[++top] = operand1 / operand2; break;
            	case '^': {
                	double result = 1;
                	for (int j = 0; j < operand2; j++) {
                    	result *= operand1;
                	}
                	stack[++top] = result;
                	break;
            	}
        	}
    	}
	}
	return stack[top]; // Result is on top of the stack
}

// Function to evaluate prefix expression
double evaluatePrefix(const char* prefix) {
	double stack[100];
	int top = -1;
	int len = 0;

	while (prefix[len] != '\0') {
    	len++;
	}

	for (int i = len - 1; i >= 0; i--) {
    	char c = prefix[i];

    	if (c >= '0' && c <= '9') {
        	stack[++top] = c - '0'; // Convert char to int and push onto stack
    	} else { // Operator
        	double operand1 = stack[top--];
        	double operand2 = stack[top--];

        	switch (c) {
            	case '+': stack[++top] = operand1 + operand2; break;
            	case '-': stack[++top] = operand1 - operand2; break;
            	case '*': stack[++top] = operand1 * operand2; break;
            	case '/': stack[++top] = operand1 / operand2; break;
            	case '^': {
                	double result = 1;
                	for (int j = 0; j < operand2; j++) {
                    	result *= operand1;
                	}
                	stack[++top] = result;
                	break;
            	}
        	}
    	}
	}
	return stack[top]; // Result is on top of the stack
}

int main() {
	char exp[100], postfix[100], prefix[100];
	int choice;
	double postfixResult, prefixResult;

	do {
    	cout << "\nMenu:\n";
    	cout << "1. Convert Infix to Postfix\n";
    	cout << "2. Convert Infix to Prefix\n";
    	cout << "3. Evaluate Postfix Expression\n";
    	cout << "4. Evaluate Prefix Expression\n";
    	cout << "5. Exit\n";
    	cout << "Enter your choice: ";
    	cin >> choice;

    	switch (choice) {
        	case 1:
            	cout << "Enter the Infix Expression: ";
            	cin >> exp;
            	InfixToPostfix(exp, postfix);
            	cout << "The Postfix expression is: " << postfix << endl;
            	break;

        	case 2:
            	cout << "Enter the Infix Expression: ";
            	cin >> exp;
            	InfixToPrefix(exp, prefix);
            	cout << "The Prefix expression is: " << prefix << endl;
            	break;

        	case 3:
            	cout << "Enter the Postfix Expression: ";
            	cin >> postfix;
            	postfixResult = evaluatePostfix(postfix);
            	cout << "Evaluation of Postfix expression: " << postfixResult << endl;
            	break;

        	case 4:
            	cout << "Enter the Prefix Expression: ";
            	cin >> prefix;
            	prefixResult = evaluatePrefix(prefix);
            	cout << "Evaluation of Prefix expression: " << prefixResult << endl;
            	break;

        	case 5:
            	cout << "Exiting" << endl;
            	break;

        	default:
            	cout << "Invalid choice! Please try again." << endl;
    	}
	} while (choice != 5);

	return 0;
}


