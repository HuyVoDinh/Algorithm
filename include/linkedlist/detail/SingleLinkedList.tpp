#pragma once
#include "../../../include/linkedlist/SingleLinkedList.h"
#include "../../../include/linkedlist/exception/LinkedListException.h"
#include <iostream>
#include <map>
#include <vector>

template <typename T>
void SingleLinkedList<T>::push_front(const T &value)
{
    SingleNode *newNode = new SingleNode(value);
    newNode->next = head;
    head = newNode;
    ++size;
}

template <typename T>
void SingleLinkedList<T>::push_back(const T &value)
{
    SingleNode *node = new SingleNode(value);

    if (head == nullptr)
    {
        head = node;
    }
    else
    {
        SingleNode *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = node;
    }
    ++size;
}

template <typename T>
void SingleLinkedList<T>::pop_front()
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }

    SingleNode *temp = head;
    head = head->next;
    delete temp;
    --size;
}

template <typename T>
void SingleLinkedList<T>::pop_back()
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        SingleNode *current = head;
        while (current->next->next != nullptr)
        {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    --size;
}

template <typename T>
bool SingleLinkedList<T>::remove(const T &value)
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    SingleNode *current = head;
    if (head->value == value)
    {
        pop_front();
        return true;
    }
    else
    {
        SingleNode *previous = current;
        while (current->next != nullptr && current->value != value)
        {
            previous = current;
            current = current->next;
        }
        if (current->value == value)
        {
            previous->next = current->next;
            delete current;
            current = nullptr;
            --size;
            return true;
        }
    }

    return false;
}

template <typename T>
bool SingleLinkedList<T>::contains(const T &value) const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");
    SingleNode *current = head;
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
typename SingleLinkedList<T>::SingleNode *SingleLinkedList<T>::find(const T &value) const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    SingleNode *current = head;
    while (current != nullptr)
    {
        if (current->value == value)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename T>
T SingleLinkedList<T>::front() const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    return head->value;
}

template <typename T>
T SingleLinkedList<T>::back() const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    SingleNode *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    return current->value;
}

template <typename T>
void SingleLinkedList<T>::clear()
{
    while (head != nullptr)
    {
        SingleNode *current = head;
        head = head->next;
        delete current;
        --size;
    }
}

template <typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
T SingleLinkedList<T>::at(int index) const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    if (index < 0 || index >= size)
        throw IndexOutOfRangeException("Index out of range");

    SingleNode *current = head;
    while (current != nullptr && index > 0)
    {
        current = current->next;
        --index;
    }

    return current != nullptr ? current->value : T();
}

template <typename T>
int SingleLinkedList<T>::indexOf(const T &value)
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    int index = 0;
    SingleNode *current = head;
    while (current != nullptr)
    {
        if (current->value == value)
        {
            return index;
        }
        current = current->next;
        ++index;
    }
    return -1;
}

template <typename T>
void SingleLinkedList<T>::insert(int index, const T &value)
{
    if (index < 0 || index > size)
        throw IndexOutOfRangeException("Index out of range");

    SingleNode *node = new SingleNode(value);
    SingleNode *current = head;

    if (index > size)
        return;

    if (index == 0)
    {
        node->next = head;
        head = node;
    }
    else
    {
        while (index > 1)
        {
            current = current->next;
            --index;
        }

        node->next = current->next;
        current->next = node;
    }
    ++size;
}

template <typename T>
void SingleLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index > size)
        throw IndexOutOfRangeException("Index out of range");

    if (index == 0)
    {
        pop_front();
        return;
    }
    else
    {
        SingleNode *current = head;
        SingleNode *previous = nullptr;
        while (index > 0)
        {
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
void SingleLinkedList<T>::reverse()
{
    if (head == nullptr)
        throw EmptyListException("Empty list exception");

    std::vector<T> v;
    SingleLinkedList<T>::SingleNode *current = head;
    while(current != nullptr) {
        v.push_back(current->value);
        current = current->next;
    }

    current = head;
    for(int i = v.size()-1; i >= 0; i--){
        current->value = v[i];
        current = current->next;
    }
}

template <typename T>
void SingleLinkedList<T>::sort(bool isDesc)
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    std::vector<T> v;
    SingleNode *node = head;
    while(node != nullptr){
        v.push_back(node->value);
        node = node->next;
    }

    if(isDesc){
        std::sort(v.begin(), v.end(), std::greater<T>());
    } else {
        std::sort(v.begin(),v.end());
    }

    node = head;
    for(T val : v){
        node->value = val;
        node = node->next;
    }
}

template <typename T>
void SingleLinkedList<T>::unique()
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    std::map<int,bool> map;

    SingleNode *current = head;
    SingleNode *previous = head;
    while(current != nullptr) {
        if(map.find(current->value) != map.end()) {
            previous->next = current->next;
            --size;
            delete current;
            current = previous;
        }
        else {
            map[current->value] = true;
        }
        previous = current;
        current = current->next;
    }
}

template <typename T>
std::vector<T> SingleLinkedList<T>::toVector() const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    std::vector<T> vec;
    SingleNode *current = head;
    while (current != nullptr)
    {
        vec.push_back(current->value);
        current = current->next;
    }

    return vec;
}

template <typename T>
void SingleLinkedList<T>::merge(LinkedList<T> &other)
{
    if (head == nullptr || other.getHead() == nullptr)
        throw EmptyListException("List is empty");

    SingleNode *current = head;
    SingleLinkedList<T> *otherSLL = dynamic_cast<SingleLinkedList<T> *>(&other);

    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = otherSLL->getHead();
    size += other.getSize();

    otherSLL->head = nullptr;
    otherSLL->size = 0;
}

template <typename T>
void SingleLinkedList<T>::print() const
{
    SingleNode *current = head;
    while (current != nullptr)
    {
        std::cout << current->value << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
    std::cout << "Size: " << size << std::endl;
}

template <typename T>
void SingleLinkedList<T>::copyFrom(const LinkedList<T> &other)
{
    if (other.getHead() == nullptr)
        throw EmptyListException("List is empty");
    
    SingleNode *current = head;
    const SingleLinkedList<T> *otherSLL = dynamic_cast<const SingleLinkedList<T> *>(&other);
    SingleNode *copiedPtr = otherSLL->getHead();

    clear();
    
    while (copiedPtr != nullptr)
    {
        push_back(copiedPtr->value);
        copiedPtr = copiedPtr->next;
    }
}

template <typename T>
SingleLinkedList<T> *SingleLinkedList<T>::clone() const
{
    if (head == nullptr) throw EmptyListException("List is empty");

    return new SingleLinkedList<T>(*this);
}

template <typename T>
bool SingleLinkedList<T>::equals(const LinkedList<T> &other) const
{
    if (size != other.getSize())
        return false;

    SingleNode *current = head;
    const SingleLinkedList<T> *otherSLL = dynamic_cast<const SingleLinkedList<T> *>(&other);
    SingleNode *compare_ptr = otherSLL->getHead();
    while (current != nullptr)
    {
        if (current->value != compare_ptr->value)
            return false;

        current = current->next;
        compare_ptr = compare_ptr->next;
    }

    return true;
}

template <typename T>
void SingleLinkedList<T>::swap(LinkedList<T> &other)
{
    SingleNode *current = head;
    SingleLinkedList<T> *otherSLL = dynamic_cast< SingleLinkedList<T> *>(&other);
    
    std::swap(this->head, otherSLL->head);
    std::swap(this->size, otherSLL->size);
}

template <typename T>
T SingleLinkedList<T>::mid() const
{
    return at(size/2);
}

template <typename T>
typename SingleLinkedList<T>::SingleNode *SingleLinkedList<T>::getHead() const
{
    return head;
}