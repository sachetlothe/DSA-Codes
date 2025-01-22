#include<iostream>
#include<string>
using namespace std;

class Student{
private:
    int rollno;         // Roll number of the student
    string name;        // Name of the student
    float sgpa;         // SGPA of the student
public:
    // Function to read student details
    void read(){
        cout << "Enter the Roll no: ";
        cin >> rollno;
        cout << "Enter the Name of the Student: ";
        cin >> name;
        cout << "Enter the SGPA: ";
        cin >> sgpa;
    }
    
    // Function to display student details
    void display(){
        cout << "\n";
        cout << "Roll no of Student: " << rollno << "\n";
        cout << "Name of Student: " << name << "\n";
        cout << "SGPA of Student: " << sgpa << "\n";
    }
    
    // Getter functions to access private members
    int getRollno(){
        return rollno;
    }
    float getSGPA(){
        return sgpa;
    }
    string getName(){
        return name;
    }

    // Friend functions to access private members for sorting purposes
    friend void insertionSort(Student s[], int n);
    friend void shellSort(Student s[], int n);
    friend void radixSort(Student s[], int n);
};

// Function to sort students by Roll number using Insertion Sort
void insertionSort(Student s[], int n){
    for (int i = 1; i < n; i++) {
        Student x = s[i];
        int j = i - 1;
        // Shift elements greater than x to one position ahead
        while (j >= 0 && s[j].getRollno() > x.getRollno()){
            s[j + 1] = s[j];
            j = j - 1;
        }
        s[j + 1] = x;
    }
}

// Function to sort students by Name using Shell Sort
void shellSort(Student s[], int n){
    for (int gap = n / 2; gap >= 1; gap = gap / 2) {
        for (int i = gap; i < n; i++) {
            Student tobesorted = s[i];
            int j = i - gap;
            // Shift elements if they are lexicographically larger
            while (j >= 0 && s[j].name > tobesorted.name){
                s[j + gap] = s[j];
                j = j - gap;
            }
            s[j + gap] = tobesorted;
        }
    }
}

// Function to find the maximum SGPA in the list
float getMaxSGPA(Student s[], int n){
    float max = s[0].getSGPA();
    for (int i = 1; i < n; i++){
        if (s[i].getSGPA() > max)
            max = s[i].getSGPA();
    }
    return max;
}

// Helper function to convert SGPA to integer by multiplying by 100
int convertSGPAtoInt(float sgpa){
    return (int)(sgpa * 100);  // Multiply by 100 to avoid precision issues
}

// Count sort for Radix Sort based on SGPA
void countSort(Student s[], int n, int exp){
    Student output[n];  // Output array to store sorted students
    int count[10] = {0};  // Count array for digits (0-9)

    // Store count of occurrences of each digit
    for (int i = 0; i < n; i++){
        int digit = (convertSGPAtoInt(s[i].getSGPA()) / exp) % 10;
        count[digit]++;
    }

    // Change count[i] so that it contains actual position of this digit in output
    for (int i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--){
        int digit = (convertSGPAtoInt(s[i].getSGPA()) / exp) % 10;
        output[count[digit] - 1] = s[i];
        count[digit]--;
    }

    // Copy the sorted output to the original array
    for (int i = 0; i < n; i++){
        s[i] = output[i];
    }
}

// Radix Sort function to sort students by SGPA
void radixSort(Student s[], int n){
    int max = convertSGPAtoInt(getMaxSGPA(s, n));

    // Sort based on each digit from least to most significant digit
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(s, n, exp);
    }
}

// Function to display menu options
void displayMenu(){
    cout << "\nMenu:\n";
    cout << "1. Display Original Student List\n";
    cout << "2. Sort by Roll No (Insertion Sort)\n";
    cout << "3. Sort by Name (Shell Sort)\n";
    cout << "4. Sort by SGPA (Radix Sort)\n";
    cout << "Enter your choice: ";
}

int main(){
    int n, choice;
    cout << "Enter the number of students: ";
    cin >> n;

    Student students[n];  // Array of Student objects
    for (int i = 0; i < n; i++){
        cout << "Enter details for student " << i + 1 << ":\n";
        students[i].read();
    }

    // Menu-driven program to sort students
    while (true){
        displayMenu();
        cin >> choice;

        switch (choice){
            case 1:
                // Display original student list
                cout << "\nOriginal Student List:\n";
                for (int i = 0; i < n; i++) {
                    students[i].display();
                }
                break;
            case 2:
                // Sort by Roll Number using Insertion Sort
                insertionSort(students, n);
                cout << "\nRoll Call List (sorted by Roll No in ascending order):\n";
                for (int i = 0; i < n; i++) {
                    students[i].display();
                }
                break;
            case 3:
                // Sort by Name using Shell Sort
                shellSort(students, n);
                cout << "\nAlphabetical List (sorted by Name in alphabetical order):\n";
                for (int i = 0; i < n; i++) {
                    students[i].display();
                }
                break;
            case 4:
                // Sort by SGPA using Radix Sort
                radixSort(students, n);
                cout << "\nTop 10 Toppers List (sorted by SGPA in descending order):\n";
                for (int i = 0; i < min(10, n); i++) {
                    students[i].display();
                }
                break;
            default:
                // Handle invalid input
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
