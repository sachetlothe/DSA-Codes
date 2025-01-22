#include <iostream>
using namespace std;

class node{
    string Fooditem;
    public:
    node *next;
    node() {
        next = NULL;
    }
    
    void read(){
        cout<<"Please tell your food items: ";
        cin>>Fooditem;
    }
    void display(){
        cout<<"Order: "<<Fooditem;
        cout<<"\n";
    }
};

class Queue{
    node *front, *rear;
    public:
    Queue(){
        front=rear=NULL;
    }
    node *newNode(){
        return new node;
    }
    
    void orderfood(){
        node *nn=newNode();
        nn->read();
        if(front==NULL){
            front=rear=nn;
        }
        else{
            rear->next=nn;
            rear=nn;
        }
        cout<<"Order Placed"<<endl;
    }
    
    void Servefood(){
        if(front==NULL){
            cout<<"No orders to Serve"<<endl;
        }
        else{
            node *temp;
            temp=front;
            front=front->next;
            delete(temp);
            if(front==NULL){
                rear=NULL;
            }
            cout<<"Food Served"<<endl;
        }
    }
    
    void display(){
        if(front==NULL){
            cout<<"No orders pending!"<<endl;
        }
        else{
        for(node *cn=front;cn!=NULL;cn=cn->next){
            cn->display();
            }
        }
    }
};
int main() {
    int choice;
    Queue q;
    
    while(true){
        cout<<"--Queue--"<<endl;
        cout<<"1.Order Food"<<endl;
        cout<<"2.Serve Food"<<endl;
        cout<<"3.Display"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>choice;
        cout<<"\n";
        
        switch(choice){
            case 1:
            q.orderfood();
            break;
            
            case 2:
            q.Servefood();
            break;
            
            case 3:
            q.display();
            break;
            
            default:
            cout<<"Invalid Choice"<<endl;
        }
        cout<<endl;
    }
    return 0;
}