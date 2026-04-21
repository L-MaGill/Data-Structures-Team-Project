#include <iostream>
using namespace std;

template<typename T>
struct NodeS {
    T data;
    NodeS<T>* next;

    // Constructor
    NodeS(T d) {
        data = d;
        next = nullptr; 
    } 
};

template <typename T> 
class Stack{
    private:
    NodeS<T>* top;
    int count;
    
    public: 
    Stack() {
        top = nullptr; 
        count = 0;
    }

    ~Stack() {
        while (!isEmpty()){
            pop();
        }
    }
    // insert value at top
    void push(T val){
        NodeS<T>* newNode = new NodeS<T>(val);
        newNode->next = top;
        top = newNode;
        count++;
    }

    // remove value from top
    void pop(){
        if(isEmpty()){
            throw runtime_error("Stack is empty");
        }
        NodeS<T>* temp = top;
        T value = temp->data;

        top = top->next;
        delete temp;
        count --;
        
    }

     // check if empty 
    bool isEmpty(){
        return top == nullptr;
    }

    //get size
    int size (){
        return count;
    }

    void printList() {
        if (isEmpty()) {
            cout << "\nStack is empty";
            return;
        }
        NodeS<T>* temp = top;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }

};