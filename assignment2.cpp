#include<iostream>
#include<string>
using namespace std;

class Employee{
private:
    int id;            // Employee ID
    string name;       // Employee name
    int salary;        // Employee salary
public:
    // Function to input employee details
    void read(){
        cout << "Enter the Employee Id: ";
        cin >> id;
        cout << "Enter the Employee Name: ";
        cin >> name;
        cout << "Enter the Employee's salary: ";
        cin >> salary;
    }
    
    // Function to display employee details
    void display(){
        cout << "Employee Id: " << id << "\n";
        cout << "Employee Name: " << name << "\n";
        cout << "Employee Salary: " << salary << "\n";
    }
    
    // Getter function to return Employee ID
    int getId() {
        return id;
    }
    
    // Getter function to return Employee Name
    string getName(){
        return name;
    }
};

// Partition function for Quick Sort (based on Employee ID)
int partition(Employee arr[], int low, int high){
    int pivot = arr[high].getId();  // Choose the last element as the pivot
    int i = low - 1;

    // Rearrange elements so that those less than or equal to the pivot are on the left
    for (int j = low; j < high; j++) {
        if (arr[j].getId() <= pivot){
            i++;
            swap(arr[i], arr[j]);  // Swap elements if condition satisfies
        }
    }
    swap(arr[i + 1], arr[high]);  // Place the pivot in the correct position
    return i + 1;
}

// Quick Sort function to sort by Employee ID
void quickSort(Employee arr[], int low, int high){
    if (low < high) {
        int pi = partition(arr, low, high);  // Get pivot index after partitioning

        quickSort(arr, low, pi - 1);  // Recursively sort the left subarray
        quickSort(arr, pi + 1, high); // Recursively sort the right subarray
    }
}

// Merge function for Merge Sort (based on Employee Name)
void merge(Employee arr[], int left, int mid, int right){
    int n1 = mid - left + 1;  // Size of the left subarray
    int n2 = right - mid;     // Size of the right subarray

    Employee leftArr[n1], rightArr[n2];  // Temporary arrays for merging

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge the arrays by comparing Employee Names
    while (i < n1 && j < n2){
        if (leftArr[i].getName() <= rightArr[j].getName()){
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr (if any)
    while (i < n1){
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr (if any)
    while (j < n2){
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Merge Sort function to sort by Employee Name
void mergeSort(Employee arr[], int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2;  // Calculate the mid-point

        mergeSort(arr, left, mid);            // Recursively sort the left subarray
        mergeSort(arr, mid + 1, right);       // Recursively sort the right subarray

        merge(arr, left, mid, right);         // Merge the sorted subarrays
    }
}

// Function to display menu options
void displayMenu(){
    cout << "\nMenu:\n";
    cout << "1. Display Employees\n";
    cout << "2. Sort by Employee ID (Quick Sort)\n";
    cout << "3. Sort by Employee Name (Merge Sort)\n";
    cout << "Enter your choice: ";
}

int main(){
    int n, choice;
    cout << "Enter the number of employees: ";
    cin >> n;
    Employee employees[n];  // Array of Employee objects

    // Read employee details
    for (int i = 0; i < n; i++){
        employees[i].read();
    }

    // Menu-driven program
    while (true){
        displayMenu();
        cin >> choice;

        switch (choice){
        case 1:
            // Display all employees
            cout << "\nEmployee List:\n";
            for (int i = 0; i < n; i++){
                employees[i].display();
                cout << "\n";
            }
            break;
        case 2:
            // Sort by Employee ID using Quick Sort
            quickSort(employees, 0, n - 1);
            cout << "\nEmployees sorted by ID (Quick Sort):\n";
            for (int i = 0; i < n; i++){
                employees[i].display();
                cout << "\n";
            }
            break;
        case 3:
            // Sort by Employee Name using Merge Sort
            mergeSort(employees, 0, n - 1);
            cout << "\nEmployees sorted by Name (Merge Sort):\n";
            for (int i = 0; i < n; i++){
                employees[i].display();
                cout << "\n";
            }
            break;
        default:
            // Handle invalid input
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
