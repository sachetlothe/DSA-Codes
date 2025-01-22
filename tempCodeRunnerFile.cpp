#include <iostream>
using namespace std;

class route{
    string source, dest;
    int distance;
    route *next;

public:
    route(){
        next = NULL;
    }

    void read(){
        cout << "Enter Source: ";
        cin >> source;
        cout << "Enter Destination: ";
        cin >> dest;
        cout << "Enter Distance(in kms): ";
        cin >> distance;
    }

    void display(){
        cout << "Source: " << source << "  ";
        cout << "Destination: " << dest << "  ";
        cout << "Distance(in kms): " << distance << endl;
    }

    friend class route_nav;
};

class route_nav{
public:
    route *tail;
    route_nav(){
        tail = NULL;
    }

    void addRoute(){
        route *newRoute = new route;
        newRoute->read();
        if(tail == NULL){
            tail = newRoute;
            tail->next = newRoute;
        } else {
            newRoute->next = tail->next;
            tail->next = newRoute;
            tail = newRoute;
        }
    }

    void deleteRoute(){
        if(tail == NULL){
            cout << "No routes to delete.\n";
            return;
        }

        route *p = tail;
        route *t = tail->next;
        string src, desti;
        cout << "Enter source: ";
        cin >> src;
        cout << "Enter destination: ";
        cin >> desti;

        do {
            if(t->source == src && t->dest == desti){
                if(t == tail){
                    if(tail == tail->next){
                        delete t;
                        tail = nullptr;
                        return;
                    } else {
                        p->next = t->next;
                        tail = p;
                        delete t;
                        return;
                    }
                } else {
                    p->next = t->next;
                    delete t;
                    return;
                }
            } else {
                p = t;
                t = t->next;
            }
        } while(t != tail->next);
        cout << "Route does not exist.\n";
    }

    void displayRoutes(){
        if(!tail){
            cout << "No routes to display.\n";
            return;
        }
        route *temp = tail->next;
        do {
            temp->display();
            temp = temp->next;
        } while(temp != tail->next);
    }
};

int main(){
    route_nav nav;
    int choice;

    while(true){
        cout << "\nMenu:\n";
        cout << "1. Add Route\n";
        cout << "2. Remove Route\n";
        cout << "3. Display All Routes\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                nav.addRoute();
                break;
            case 2:
                nav.deleteRoute();
                break;
            case 3:
                nav.displayRoutes();
                break;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    }

    return 0;
}
