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
    newNode->previous = nullptr;
    head = newNode;
    if (head->next == nullptr)
    {
        tail = head;
    }

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
            return true;
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
typename DoubleLinkedList<T>::DoubleNode *DoubleLinkedList<T>::find(const T &value) const
{
    DoubleLinkedList<T>::DoubleNode *current = head;
    while (current != nullptr)
    {
        if (current->value == value)
        {
            break;
        }
        current = current->next;
    }

    return current != nullptr ? current : nullptr;
}

template <typename T>
T DoubleLinkedList<T>::front() const
{
    return head->value;
}

template <typename T>
T DoubleLinkedList<T>::back() const
{
    return tail->value;
}

template <typename T>
void DoubleLinkedList<T>::clear()
{
    DoubleLinkedList<T>::DoubleNode *current = head;

    while (head != nullptr)
    {
        head = head->next;
        delete current;
        current = nullptr;
        current = head;
    }

    size = 0;
    tail = nullptr;
    head = nullptr;
}

template <typename T>
int DoubleLinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
bool DoubleLinkedList<T>::isEmpty() const
{
    if (head == nullptr && tail == nullptr)
        return true;
    return false;
}

template <typename T>
T DoubleLinkedList<T>::at(int index) const
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }
    if (index < 0 || index >= size)
    {
        throw IndexOutOfRangeException("Index out of range");
    }

    DoubleLinkedList<T>::DoubleNode *current = head;
    for (int i = 1; i < index; i++)
    {
        current = current->next;
    }
    return current->value;
}

template <typename T>
int DoubleLinkedList<T>::indexOf(const T &value)
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }

    DoubleLinkedList<T>::DoubleNode *current = head;
    int index = 0;

    while (current != nullptr)
    {
        if (current->value == value)
            return index;
        index++;
    }
    current = current->next;
    return -1;
}

template <typename T>
void DoubleLinkedList<T>::insert(int index, const T &value)
{
    if (index < 0 || index > size)
    {
        throw IndexOutOfRangeException("Index out of range");
    }

    if (index == 0)
    {
        push_front(value);
    }
    else if (index == size)
    {
        push_back(value);
    }
    else
    {
        DoubleLinkedList<T>::DoubleNode *newNode = new DoubleLinkedList<T>::DoubleNode(value);
        DoubleLinkedList<T>::DoubleNode *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        DoubleLinkedList<T>::DoubleNode *nextNode = current->next;

        newNode->next = newNode;
        nextNode->previous = newNode;
        current->next = newNode;
        newNode->previous = current;
        ++size;
    }
}

template <typename T>
void DoubleLinkedList<T>::removeAt(int index)
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }

    if (index < 0 || index >= size)
    {
        throw IndexOutOfRangeException("Index out of range");
    }

    if (index == 0)
    {
        pop_front();
    }
    else if (index == size - 1)
    {
        pop_back();
    }
    else
    {
        DoubleLinkedList<T>::DoubleNode *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        DoubleLinkedList<T>::DoubleNode *previousNode = current->previous;
        DoubleLinkedList<T>::DoubleNode *nextNode = current->next;

        previousNode->next = nextNode;
        nextNode->previous = previousNode;
        delete current;
        current = nullptr;
        --size;
    }
}

template <typename T>
void DoubleLinkedList<T>::reverse()
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }

    DoubleLinkedList<T>::DoubleNode *current = head;
    head = tail;
    tail = current;
    head->previous = nullptr;
    tail->next = nullptr;
}

template <typename T>
void DoubleLinkedList<T>::sort(bool isDesc)
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }

    if (head->next == nullptr)
    {
        return;
    }

    std::vector<DoubleLinkedList<T>::DoubleNode *> listNode;
    DoubleLinkedList<T>::DoubleNode *current = head;
    while (current != nullptr)
    {
        listNode.push_back(current);
        current = current->next;
    }

    if (isDesc)
    {
        std::sort(listNode.begin(), listNode.end(), [](DoubleLinkedList<T>::DoubleNode *a, DoubleLinkedList<T>::DoubleNode *b)
                  { return a->value > b->value; });
    }
    else
    {
        std::sort(listNode.begin(), listNode.end(), [](DoubleLinkedList<T>::DoubleNode *a, DoubleLinkedList<T>::DoubleNode *b)
                  { return a->value <= b->value; });
    }

    for (int i = 0; i < listNode.size(); i++)
    {
        listNode[i]->previous = listNode[i - 1];
        listNode[i - 1]->next = listNode[i];
    }
    listNode.front()->previous = nullptr;
    listNode.back()->next = nullptr;

    head = listNode.front();
    tail = listNode.back();
}

template <typename T>
void DoubleLinkedList<T>::unique()
{
}

template <typename T>
std::vector<T> DoubleLinkedList<T>::toVector() const
{
    DoubleLinkedList<T>::DoubleNode *current = head;

    std::vector<T> list;
    while (current != nullptr)
    {
        list.push_back(current->value);
        current = current->next;
    }

    return list;
}

template <typename T>
void DoubleLinkedList<T>::merge(LinkedList<T> &other)
{
    if (other.getHead() == nullptr)
    {
        return;
    }

    try
    {
        DoubleLinkedList<T> *otherDLL = dynamic_cast<DoubleLinkedList<T> *>(&other);
        tail->next = otherDLL->getHead();
        tail = otherDLL->getTail();
        size += otherDLL->getSize();

        otherDLL->clear();
    }
    catch (std::bad_cast &e)
    {
        throw LinkedListException("Can't cast to Double Linked List");
    }
}

template <typename T>
void DoubleLinkedList<T>::print() const
{
    DoubleLinkedList<T>::DoubleNode *current = head;
    while (current != nullptr)
    {
        std::cout << current->value << " -> ";
        current = current->next;
    }
    std::cout << "nullptr\n";
    std::cout << "Size: " << size << std::endl;
}

template <typename T>
void DoubleLinkedList<T>::copyFrom(const LinkedList<T> &other)
{
}

template <typename T>
DoubleLinkedList<T> *DoubleLinkedList<T>::clone() const
{
    return new DoubleLinkedList<T>(*this);
}

template <typename T>
bool DoubleLinkedList<T>::equals(const LinkedList<T> &other) const{
    DoubleLinkedList<T>::DoubleNode *current = head;
    const DoubleLinkedList<T> *otherDLL = dynamic_cast<const DoubleLinkedList<T>* >( &other);
    DoubleLinkedList<T>::DoubleNode *currentOther = otherDLL->getHead();

    if(size != otherDLL->getSize()){
        return false;
    }

    while(current != nullptr){
        if(current->value != currentOther->value){
            return false;
        }
        current = current->next;
        currentOther = currentOther->next;
    }
    return true;
}

template <typename T>
void DoubleLinkedList<T>::swap(LinkedList<T> &other){
    try{
        DoubleLinkedList<T> *otherDLL = dynamic_cast<DoubleLinkedList<T>*>(&other);
        std::swap(head, otherDLL->head);
        std::swap(tail, otherDLL->tail);
        std::swap(size, otherDLL->size);
    } catch (std::bad_cast &e){
        throw LinkedListException("Can't cast to Double Linked List");
    }
}

template <typename T>
T DoubleLinkedList<T>::mid() const{
    return at(size/2);
}

template <typename T>
typename DoubleLinkedList<T>::DoubleNode *DoubleLinkedList<T>::getHead() const{
    return head;
}

template <typename T>
typename DoubleLinkedList<T>::DoubleNode *DoubleLinkedList<T>::getTail() const{
    return tail;
}