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
    if(head != nullptr){
        Node* current = head;
        if(head->data == value){
            pop_front();
            return;
        }
        else{
            Node *previous = current;
            while(current->next != nullptr && current->data != value){
                previous = current;
                current = current->next;
            }
            if(current->data == value){
                previous->next = current->next;
                delete current;
                current = nullptr;
                --size;
            }
        }
    }
}

template <typename T>
bool SingleLinkedList<T>::contains(const T& value) const {
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
SingleLinkedList<T>::Node* SingleLinkedList<T>::find(const T& value) const {
    Node *current = head;
    while(current != nullptr){
        if(current-> data == value){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename T>
T SingleLinkedList<T>::front() const{
    if(head != nullptr){
        return head->data;
    }
    return T();
}

template <typename T>
T SingleLinkedList<T>::back() const{
    if(head == nullptr) return T();

    Node *current = head;
    while(current->next != nullptr){
        current = current->next;
    }
    return current->data;
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
    if(index < 0 || index >= size) return T();

    Node *current = head;
    while(current != nullptr && index > 0){
        current = current->next;
        --index;
    }
    
    return current != nullptr ? current->data : T();
}

template <typename T>
void SingleLinkedList<T>::indexOf(const T& value){
    int index = 0;
    Node *current = head;
    while(current != nullptr){
        if(current->data == value){
            return index;
        }
        current = current->next;
        ++index;
    }
    return -1;
}

template <typename T>
void SingleLinkedList<T>::insert(int index, const T& value){
    Node node = new Node(value);
    Node current = head;

    if(index > size) return;
    
    if(index == 0){
        node->next =head;
        head = node;
    } else{
        while(index >1){
            current = current->next;
            --index;
        }

        node->next = current->next;
        current->next = node;
    }
    ++size;
}

template <typename T>
void SingleLinkedList<T>::removeAt(const T& value){
    if (index > size) return;

    if(index == 0){
        pop_back();
        return;
    }
    else{
        Node current = head;
        Node previous = nullptr;
        while(index > 0){
            previous = current;
            current = current->next;
            --index;
        }
        previous->next = current->next;
        delete current;
        current = nullptr;
        --size;
    }
}

template <typename T>
void SingleLinkedList<T>::reverse(){
    Node current = head;
    Node previous = nullptr;
    Node nextPtr = head->next;
    previous->next = nullptr;
    while(nextPtr->next != nullptr){
        previous = current;
        current = nextPtr;
        nextPtr = nextPtr->next;
        current->next = previous;
    }
    nextPtr->next = current;
    head = nextPtr;
}

template <typename T>
void SingleLinkedList<T>::sort(){

}

template <typename T>
void SingleLinkedList<T>::unique(){

}

template <typename T>
std::vector<T> SingleLinkedList<T>::toVector() const{
    std::vector<T> vec;
    Node *current = head;
    while(current != nullptr){
        vec.push_back(current->data);
        current = current->next;
    }
    return vec;
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
    Node current = head;
    Node copiedPtr = other.getHead();

    while(copiedPtr != nullptr){
        if(current->next != nullptr){
            current.data = copiedPtr->data;
        } else {
            Node node = new Node(copiedPtr->data);
            current->next = node;
        }

        current = current->next;
        copiedPtr = copiedPtr->next;
    }
}

template <typename T>
LinkedList<T>* SingleLinkedList<T>::clone() const{
    Node current = head;
    Node headClone;
    bool firstNode = true;
    Node nodeClonePtr = nullptr;
    while(current != nullptr){
        Node node = new Node(current->data);
        if(firstNode){
            headClone = node;
            nodeClonePtr = headClone;
            firstNode = false;
        } else {
            nodeClonePtr->next = node;
            nodeClonePtr = nodeClonePtr->next;
        }
        current = current->next;
    }
    return new SingleLinkedList<T>(headClone);
}

template <typename T>
bool SingleLinkedList<T>::equals(const LinkedList<T>& other) const{
    if(size != other.getSize()) return false;

    Node *current = head;
    Node *compare_ptr = other.getHead();
    while(current->next != nullptr){
        if(current->data != compare_ptr->data)
            return false;
        
        current = current->next;
        compare_ptr = compare_ptr->next;
    }

    return true;
}

template <typename T>
void SingleLinkedList<T>::swap(LinkedList<T>& other){
    Node *current = head;
    Node *temp = other.getHead();
    head->next = temp;
    temp->next = current;
}

template <typename T>
T SingleLinkedList<T>::mid() const{
    if(head == nullptr) return T();

    int midPosition = size/2;
    Node *current = head;
    while(midPosition >= 0){
        current = current->next;
        --midPosition;
    }
    return current->value;
}

template <typename T>
SingleLinkedList<T>::Node* SingleLinkedList<T>::getHead() const{
    return head;
}