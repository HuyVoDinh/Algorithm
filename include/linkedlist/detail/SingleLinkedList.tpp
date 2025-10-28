#pragma once
#include "../../../include/linkedlist/SingleLinkedList.h"
#include <iostream>

template <typename T>
void SingleLinkedList<T>::push_front(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    ++size;
}

template <typename T>
void SingleLinkedList<T>::push_back(const T& value){
    Node *node = new Node(value);

    if(head == nullptr){
        head = node;
    }
    else {
        Node *current = head;
        while(current->next != nullptr){
            current = current->next;
        }
        current->next = node;
    }
    ++size;
}

template <typename T>
void SingleLinkedList<T>::pop_front(){
    if(head == nullptr) return;

    Node *temp = head;
    head = head->next;
    delete temp;
    --size;
}

template <typename T>
void SingleLinkedList<T>::pop_back(){
    if(head == nullptr) return;

    if(head->next == nullptr){
        delete head;
        head = nullptr;
    }
    else {
        Node *current = head;
        while(current->next->next != nullptr){
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    --size;
}

template <typename T>
void SingleLinkedList<T>::remove(const T& value){

}

template <typename T>
bool SingleLinkedList<T>::contains(const T& value) const {

}

template <typename T>
bool SingleLinkedList<T>::find(const T& value) const {
    Node *current = head;
    while(current != nullptr){
        if(current->data == value){
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
T SingleLinkedList<T>::front() const{

    return T();
}

template <typename T>
T SingleLinkedList<T>::back() const{

}

template <typename T>
void SingleLinkedList<T>::clear(){
    while(head != nullptr){
        Node *current = head;
        head = head->next;
        delete current;
        --size;
    }
}

template <typename T>
int SingleLinkedList<T>::getSize() const{
    return size;
}

template <typename T>
bool SingleLinkedList<T>::isEmpty() const{
    return size == 0;
}

template <typename T>
T SingleLinkedList<T>::at(int index) const{

}

template <typename T>
void SingleLinkedList<T>::indexOf(const T& value){

}

template <typename T>
void SingleLinkedList<T>::insert(int index, const T& value){

}

template <typename T>
void SingleLinkedList<T>::removeAt(const T& value){

}

template <typename T>
void SingleLinkedList<T>::reverse(){

}

template <typename T>
void SingleLinkedList<T>::sort(){

}

template <typename T>
void SingleLinkedList<T>::unique(){

}

template <typename T>
std::vector<T> SingleLinkedList<T>::toVector() const{

}

template <typename T>
void SingleLinkedList<T>::merge(LinkedList<T>& other){

}

template <typename T>
void SingleLinkedList<T>::print() const{
    Node *current = head;
    while(current != nullptr){
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
    std::cout << "Size: " << size << std::endl;
}

template <typename T>
void SingleLinkedList<T>::copyFrom(const LinkedList<T>& other){

}

template <typename T>
LinkedList<T>* SingleLinkedList<T>::clone() const{

}

template <typename T>
bool SingleLinkedList<T>::equals(const LinkedList<T>& other) const{

}

template <typename T>
void SingleLinkedList<T>::swap(LinkedList<T>& other){

}

template <typename T>
T SingleLinkedList<T>::mid() const{

}