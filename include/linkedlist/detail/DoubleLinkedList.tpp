#pragma once
#include "../../linkedlist/DoubleLinkedList.h"
#include "../../linkedlist/exception/LinkedListException.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

template <typename T>
void DoubleLinkedList<T>::push_front(const T &value)
{
    DoubleLinkedList<T>::DoubleNode *newNode = new DoubleLinkedList<T>::DoubleNode(value);

    newNode->next = head;
    if (head->next == nullptr)
        tail = head;

    ++size;
}

template <typename T>
void DoubleLinkedList<T>::push_back(const T &value)
{

    if (head == nullptr)
        push_front(value);
    else
    {
        DoubleLinkedList<T>::DoubleNode *newNode = new DoubleLinkedList<T>::DoubleNode(value);

        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
        ++size;
    }
}

template <typename T>
void DoubleLinkedList<T>::pop_front()
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }
    
    if (head == tail)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        DoubleLinkedList<T>::DoubleNode *current = head;
        head = head->next;
        delete current;
        current = nullptr;
    }
    --size;
}

template <typename T>
void DoubleLinkedList<T>::pop_back()
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }
    
    if (head == tail)
    {
        pop_front();
    }
    else
    {
        DoubleLinkedList<T>::DoubleNode *current = tail;
        tail = tail->previous;
        delete current;
        current = nullptr;
        --size;
    }
}

template <typename T>
bool DoubleLinkedList<T>::remove(const T &value)
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }

    DoubleLinkedList<T>::DoubleNode *current = head;

    while (current != nullptr)
    {
        if (current->value == value)
        {
            if (current == head)
            {
                pop_front();
            }
            else if (current == tail)
            {
                pop_back();
            }
            else
            {
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

template <typename T>
bool DoubleLinkedList<T>::contains(const T &value) const
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }

    DoubleLinkedList<T>::DoubleNode *current = head;
    while (current != nullptr)
    {
        if (current->value == value)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
DoubleLinkedList<T>::DoubleNode* DoubleLinkedList<T>::find(const T& value) const{
    DoubleLinkedList<T>::DoubleNode *current = head;
    while(current != nullptr){
        if(current-> value == value){
            break;
        }
        current = current->next;
    }

    return current != nullptr ? current : T();
}

template <typename T>
T DoubleLinkedList<T>::front() const {
    return head->value;
}

template <typename T>
T DoubleLinkedList<T>::back() const {
    return tail->value;
}

template <typename T>
void DoubleLinkedList<T>::clear() {
    DoubleLinkedList<T>::DoubleNode *current = head;

    while(head != nullptr){
        head = head->next;
        delete current;
        current = nullptr;
        current = head;
    }

    size = 0;
    tail = nullptr;
    head = nullptr;
}


template<typename T>
int DoubleLinkedList<T>::getSize() const{
    return size;
}

template<typename T>
bool DoubleLinkedList<T>::isEmpty() const {
    if(head == nullptr && tail == nullptr)
        return true;
    return false;
}

template<typename T>
T DoubleLinkedList<T>::at(int index) const {
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }
    if(index < 0 || index >= size){
        throw IndexOutOfRangeException("Index out of range");
    }

    DoubleLinkedList<T>::DoubleNode *current = head;
    for(int i = 1; i < index; i++)
    {
        current = current->next;
    }
    return current->value;
}

template<typename T>
int DoubleLinkedList<T>::indexOf(const T& value) {
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }
    
    DoubleLinkedList<T>::DoubleNode *current = head;
    uint index = 0;

    while(current != nullptr){
        if(current->value == value)
            return index;
    }
    index++;
    current = current->next;
    return -1;
}