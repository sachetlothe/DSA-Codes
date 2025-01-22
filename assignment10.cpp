#include <iostream>
#include <string>
using namespace std;

class JobScheduler; // Forward declaration

class Job {
private:
    string jobName;
    int jobPriority;

public:
    Job* next; // Pointer to the next job
    Job* prev; // Pointer to the previous job

    Job() : next(NULL), prev(NULL) { } // Default constructor with pointer initialization

    void setJobName(string& name) {
        jobName = name;
    }

    void setJobPriority(int priority) {
        jobPriority = priority;
    }

    string getJobName() {
        return jobName;
    }

    int getJobPriority() {
        return jobPriority;
    }
};

class JobScheduler {
private:
    Job* front; // Front of the deque
    Job* back;  // Back of the deque

public:
    JobScheduler() : front(NULL), back(NULL) { } // Constructor

    ~JobScheduler() {
        while (front) {
            Job* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void addJob() {
        string name;
        int priority;
        cout << "Enter job name: ";
        cin >> name;
        cout << "Enter job priority: ";
        cin >> priority;

        Job* newJob = new Job(); // Create a new job
        newJob->setJobName(name);      // Setting jobName
        newJob->setJobPriority(priority); // Setting jobPriority

        if (!front) { // Empty deque
            front = back = newJob;
            cout << "Job added successfully.\n";
            return;
        }

        // Insertion based on priority
        Job* current = front;
        while (current && current->getJobPriority() > priority) {
            current = current->next;
        }
        if (current == front) { // Insert at the front
            newJob->next = front;
            front->prev = newJob;
            front = newJob;
        } else if (current == NULL) { // Insert at the back
            back->next = newJob;
            newJob->prev = back;
            back = newJob;
        } else { // Insert in the middle
            newJob->next = current;
            newJob->prev = current->prev;
            current->prev->next = newJob;
            current->prev = newJob;
        }
        cout << "Job added successfully.\n";
    }

    void removeJob() {
        if (!front) {
            cout << "No jobs to remove.\n";
            return;
        }
        Job* temp = front;
        front = front->next;
        if (front) front->prev = NULL;
        else back = NULL; // Deque is now empty
        delete temp;
        cout << "Job removed successfully.\n";
    }

    void displayJobs() {
        if (!front) {
            cout << "No jobs in the queue.\n";
            return;
        }
        cout << "Current jobs in the queue:\n";
        Job* current = front;
        while (current) {
            cout << "Job: " << current->getJobName() << ", Priority: " << current->getJobPriority() << endl;
            current = current->next;
        }
    }

    void searchJob() {
        string name;
        cout << "Enter job name to search: ";
        cin >> name;

        Job* current = front;
        while (current) {
            if (current->getJobName() == name) {
                cout << "Job found: Job: " << current->getJobName() << ", Priority: " << current->getJobPriority() << endl;
                return;
            }
            current = current->next;
        }
        cout << "Job not found.\n";
    }
};

int main() {
    JobScheduler scheduler;
    int choice;

    do {
        cout << "\nJob Scheduling System\n";
        cout << "1. Add Job\n";
        cout << "2. Remove Job\n";
        cout << "3. Display Jobs\n";
        cout << "4. Search Job\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                scheduler.addJob();
                break;
            case 2:
                scheduler.removeJob();
                break;
            case 3:
                scheduler.displayJobs();
                break;
            case 4:
                scheduler.searchJob();
                break;
            case 5:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
