#include<iostream>
using namespace std;
#define size 10

class Employee
{
	public:
	int EmpId;
	string name;
	int salary;

	int get_id(){
    	return EmpId;
	}
	void read(){
    	cout<<"Enter Employee ID: ";
    	cin>>EmpId;
    	cout<<"Enter Name: ";
    	cin>>name;
    	cout << "Enter Salary: ";
    	cin >> salary;
	}
	void display(){
    	cout << "Employee ID: " << EmpId << " | Name: " << name << " | Salary: " << salary << endl;
	}
};

class Hashtable{
	public:
	Employee e[size];
	int flag[size];

	Hashtable(){
    	for (int i = 0; i < size; i++) {
        	flag[i] = 0;
    	}
	}

	void insert(){
    	Employee newR;
    	newR.read();
    	int empId=newR.get_id();
    	int pos=empId%size;

    	if(flag[pos]==0){
        	e[pos]=newR;
        	flag[pos]=1;
    	} else {
        	for(int i=0; i<size; i++){
            	pos=(pos+1)%size;
            	if(flag[pos]==0){
                	e[pos]=newR;
                	flag[pos]=1;
                	return;
            	}
        	}
    	}
	}

	void deleteEmp(){
    	int id;
    	cout<<"Enter Emp ID: ";
    	cin>>id;

    	for(int i=0; i<size; i++){
        	if(flag[i] == 1 && id == e[i].get_id()){
            	flag[i] = 0;
            	cout << "Employee deleted." << endl;
            	return;
        	}
    	}
    	cout << "User not found." << endl;  	 
	}

	void displaydata(){
    	for(int i=0; i<size; i++){
        	if (flag[i] == 0) {
            	cout << "Index " << i << ": -- " << endl;
        	} else {
            	cout << "Index " << i << ": ";
            	e[i].display();
        	}
    	}
	}

	void searchEmp(){
    	int id;
    	cout << "Enter Emp ID to search: ";
    	cin >> id;

    	for(int i=0; i<size; i++){
        	if(flag[i] == 1 && id == e[i].get_id()){
            	cout << "Employee found: ";
            	e[i].display();
            	return;
        	}
    	}
    	cout << "Employee not found." << endl;
	}
};

int main(){
	Hashtable obj;
	int choice;

	do {
    	cout << "\nMenu:\n";
    	cout << "1. Add Employee\n";
    	cout << "2. Display Employees\n";
    	cout << "3. Delete Employee\n";
    	cout << "4. Search Employee\n";
    	cout << "5. Exit\n";
    	cout << "Enter your choice: ";
    	cin >> choice;

    	switch (choice) {
        	case 1:
            	obj.insert();
            	break;
        	case 2:
            	obj.displaydata();
            	break;
        	case 3:
            	obj.deleteEmp();
            	break;
        	case 4:
            	obj.searchEmp();
            	break;
        	case 5:
            	cout << "Exiting..." << endl;
            	break;
        	default:
            	cout << "Invalid choice. Please try again." << endl;
    	}
	} while (choice != 5);

	return 0;
}
