#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T d) : data(d), next(nullptr) {} // Constructor
};

template <typename T> 
class Stack{
    private:
    Node<T>* top;
    int count;
    
    public: 
    Stack() : top (nullptr), count(0) {}

    ~Stack() {
        while (!isEmpty()){
            pop();
        }
    }
    // insert value at top
    template <typename T>
    void push(T val){
        Node<T>* newNode = new Node<T>(val);
        newNode->next = top;
        top = newNode;
        count++;
    }
    // remove value from top
    template<template T>
    void pop(T val){
        if(isEmpty()){
            throw runtime_error("Stack is empty");
        }
        return top->data;
    }
     // check if empty 
    bool isEmpty(){
        return top == nullptr;
    }
    //get size
    int size (){
        return count;
    }

};