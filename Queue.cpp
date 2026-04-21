#include <iostream>
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
    T count;

public:
    // Constructor
    Queue() : front(nullptr), rear(nullptr) {}

    // Destructor to free up memory
    ~Queue() {
        while (front != nullptr) {
            deQueue();
        }
    }

    // Enqueue operation (Same as pushback())
   
    void enQueue(T x) {
        Node<T>* newNode = new Node<T>(x);
        if(front == nullptr) {
            front == newNode;
            rear == newNode;
            count++;
            return;
        }
        else{
            rear->next = newNode;
            rear = newNode;
            count++;
            return;
        }
        
           }

    // Dequeue operation
    
    void deQueue() {
        if (front == nullptr) {
            cout << "Queue is empty";
            return;
        }
        else {
            Node<T>* newNode = front;
            front = front->next;
            count--;
            delete front;
        }
        if(front == nullptr) {
            rear = nullptr;
        }
        
          }

    // Utility function to print the entire queue
    
    void printQueue() const {
        Node<T>* node = front;
        while (node != nullptr) {
            cout << node->data << "->" << endl;
            node = node->next;
        }
        cout <<"NULL\n";
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
    int size() {
        return count;
        }
    //Returns if the queue is empty or not
    
    T isEmpty() {
        return count == 0;
    }
       };