#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T d) : data(d), next(nullptr) {} // Constructor using initializer list
};
template <typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    int count;

public:
    // Constructor
    Queue(): front(nullptr), rear(nullptr), count(0){}

    // Destructor to free up memory
    ~Queue() {
        while (front != nullptr) {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }

    // Enqueue operation (Same as pushback())
   
    void enQueue(T x) {
        Node<T>* newNode = new Node<T>(x);

        if(front == nullptr) {
            front = newNode;
            rear = newNode;
            count++;
        }
        else{
            rear->next = newNode;
            rear = newNode;
            count++;
        }
        
           }

    // Dequeue operation
    
    void deQueue() {
        if (front == nullptr) {
            cout << "Queue is empty";
            return;
        }
        else {
            Node<T>* temp = front;
            front = front->next;
            delete temp;
            count--;
        }
        if(front == nullptr) {
            rear = nullptr;
        }
        
          }

    // Utility function to print the entire queue
    
    void printQueue() const {
        Node<T>* node = front;
        while (node != nullptr) {
            cout << node->data << "-> " ;
            node = node->next;
        }
        cout << endl;
    }

    // Returns the front element
    
    T getFront() const {
        if(front == nullptr) {
            throw runtime_error("Queue is empty");
            }
            return front->data;
    }

    // Returns the rear element
    
    T getRear() const {
        if(rear == nullptr) {
            throw runtime_error("Queue is empty");
        }
        return rear->data;
    }
    // Returns the size of the queue
    int size() const {
        return count;
        }
    //Returns if the queue is empty or not
    
    bool isEmpty() const {
        return count == 0;
    }
       };