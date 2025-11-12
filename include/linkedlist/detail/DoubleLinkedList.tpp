#pragma once
#include "../../linkedlist/DoubleLinkedList.h"
#include "../../linkedlist/exception/LinkedListException.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template <typename T>
void DoubleLinkedList<T>::push_front(const T& value) {
    DoubleLinkedList<T>::DoubleNode *newNode = new DoubleLinkedList<T>::DoubleNode(value);

    newNode->next = head;
    if(head->next == nullptr)
        tail = head;

    ++size;
}

template <typename T>
void DoubleLinkedList<T>::push_back(const T& value){
    
    if (head==nullptr)
        push_front(value);
    else {
        DoubleLinkedList<T>::DoubleNode *newNode = new DoubleLinkedList<T>::DoubleNode(value);

        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
        ++size;
    }
}

template <typename T>
void DoubleLinkedList<T>::pop_front() {
    if(head == nullptr){
        throw EmptyListException("List is empty");
    } else if (head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        DoubleLinkedList<T>::DoubleNode *current = head;
        head = head->next;
        delete current;
        current = nullptr;
    }
    --size;
}

template <typename T>
void DoubleLinkedList<T>::pop_back() {
    if(head == tail) {
        pop_front();
    } else {
        DoubleLinkedList<T>::DoubleNode *current = tail;
        tail = tail->previous;
        delete current;
        current = nullptr;
        --size;
    }
}

template <typename T>
bool DoubleLinkedList<T>::remove(const T& value){
    DoubleLinkedList<T>::DoubleNode *current = head;

    while(current != nullptr){
        if(current->value == value){
            if(current == head){
                pop_front();
            } else if(current == tail) {
                pop_back();
            } else {
                DoubleLinkedList<T>::DoubleNode *preNode = current->previous;
                DoubleLinkedList<T>::DoubleNode *nextNode = current->next;
                preNode->next = nextNode;
                nextNode->previous = preNode;
                delete current;
                current = nullptr;
                --size;
            }
        }
    }

    return false;
}