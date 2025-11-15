#pragma once
#include "linkedlist/SingleLinkedList.h"
#include "linkedlist/exception/LinkedListException.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

/**
 * @brief Add an element to the front of the list
 * @param value The value to be added to the front of the list
 * @throws bad_alloc if memory allocations fails
 * 
 * This functions creates a new node with the given value and pplaces it at the beginning of the list. 
 * It updates the head pointer and increaments the size of the list. If the list was empty, it also updates the tail pointer.
 */
template <typename T>
void SingleLinkedList<T>::push_front(const T &value)
{
    SingleNode *newNode = new SingleNode(value);
    newNode->next = head;
    head = newNode;
    ++size;

    if (head->next == nullptr)
        tail = head;
}

/**
 * @brief Add an element to the end of the list
 * @param value The value to be added to the end of the list
 * @throws bac_alloc if memory allocation fails
 * 
 * This function creates a new node with the given value and places it at the end of the list.
 * It updates the tail pointer and increments the size of the list.
 * If the list was empty, it also updates the head pointer.
 */
template <typename T>
void SingleLinkedList<T>::push_back(const T &value)
{
    SingleNode *node = new SingleNode(value);

    if (head == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
    ++size;
}

/**
 * @brief Remove the first element from the list
 * @throws EmptyListException if the list is empty
 * 
 * This function removes the first element from the list and updates the head pointer.
 * If the list becomes empty after removal, it also updates the tail pointer to nullptr.
 * The size of the list is decreamented by one.
 */
template <typename T>
void SingleLinkedList<T>::pop_front()
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }

    SingleNode *temp = head;
    head = head->next;
    if (head == nullptr)
        tail = nullptr;
    delete temp;
    --size;
}

/**
 * @brief Remove the last element from the list
 * @throws EmptyListException if the list is empty
 * 
 * This function removes the last element from the list and updates the tail pointer.
 * If the list becomes empty after removal, it also updates the head pointer to nullptr.
 * The size of the list is decremented by one.
 */
template <typename T>
void SingleLinkedList<T>::pop_back()
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    if (tail->next == nullptr)
    {
        delete tail;
        tail = nullptr;
        head = nullptr;
        size = 0;
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
        tail = current;
    }
    --size;
}

/**
 * @brief Remove the first occurrence of a value from the list
 * @param value The value to be removed from the list
 * @return true if the value was found and removed, false otherwise
 * @throw EmptyListException if the list is empty
 * 
 * This function searches for the first occurrence of the specified value in the list and removes it.
 * If the value is found at the head, it calls pop_front(), Otherwise, it traverses the list to find value and removes the corresponding node.
 * The size of the list is decremented by one if a node is removed.
 */
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
            if (current == tail)
                tail = previous;

            delete current;
            current = nullptr;
            --size;
            return true;
        }
    }

    return false;
}

/**
 * @brief Check if the list contains a specific value
 * @param value The value to search for in the list
 * @return true if the value is found in the list, false otherwise
 * @throws EmptyListException if the list is empty
 * 
 * This function traverses the list to check if it contains the specified value.
 * It returns true as soon as the value is found, or false if the end of the list is reached without finding the value.
 */
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

/**
 * @brief Find a node containing a specific value
 * @param value The value to search for in the list
 * @return Pointer to the node containing the value, or nullptr if not found
 * @throws EmptyListException if the list is empty
 * 
 * This function traverses the list to find a node containing the specified value.
 * It returns a pointer to the first node that contains the value, or nullptr if the value is not found in the list.
 */
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

/**
 * @brief Get the value of the first element in the list
 * @return The value of the first element in the list
 * @throws EmptyListException if the list is empty
 * 
 * This function returns the value of the first element in the list without removing it.
 * It accesses the head node and returns its value.
 */
template <typename T>
T SingleLinkedList<T>::front() const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    return head->value;
}

/**
 * @brief Get the value of the last element in the list
 * @return The value of the last element in the list
 * @throws EmptyListException if the list is empty
 * 
 * This function returns the value of the last element in the list without removing it.
 * It accesses the tail node the returns its value.
 */
template <typename T>
T SingleLinkedList<T>::back() const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    return tail->value;
}

/**
 * @brief Remove all elements from the list
 * 
 * This function removes all elements from the list by traversing the list and deleting eacho node.
 * After this operation, the list becomes empty with head and tail pointers set to nullptr, and size set to zero.
 */
template <typename T>
void SingleLinkedList<T>::clear()
{
    while (head != nullptr)
    {
        SingleNode *current = head;
        head = head->next;
        delete current;
    }
    size = 0;
    tail = nullptr;
}

/**
 * @brief Get the number of elements in the list
 * @return The number of elements in the list
 * 
 * This function returns the current size of the list, which is the number of elements currently stored in the list.
 */
template <typename T>
int SingleLinkedList<T>::getSize() const
{
    return size;
}

/**
 * @brief Check if the list is empty
 * @return true if the list is empty, false otherwise
 * 
 * This function checks if the list is empty by comparing the size to zero.
 * It returns true if the list contains no elements, false otherwise.
 */
template <typename T>
bool SingleLinkedList<T>::isEmpty() const
{
    return size == 0;
}

/**
 * @brief Get the value at a specific index in the list
 * @param index The index of the element to retrieve
 * @return The value at the specified index
 * @throws EmptyListException if the list is empty
 * @throws IndexOutOfRangeException if the index is out of range
 * 
 * This function returns the value of the element at the specified index in the list.
 * It traverses the list from the head to the specified index and return the value of the node at that position.
 */
template <typename T>
T SingleLinkedList<T>::at(int index) const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    if (index < 0 || index >= size)
        throw IndexOutOfRangeException("Index out of range");

    SingleNode *current = head->next;
    for (int i = 0; i != index ; i++)
    {
        current = current->next;
    }

    return current != nullptr ? current->value : T();
}

/**
 * @brief Find the index of the first occurrence of a value in the list
 * @param value The value to search for in the list
 * @return The index of the first occurrence of the value, or -1 if not found
 * @throws EmptyListException if the list is empty
 * 
 * This function traverses the list to find the first occurrence of the specified value and retuns its index.
 * If the value is not found, it returns -1.
 */
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

/**
 * @brief Insert an element at a specific index in the list
 * @param index The index at which to insert the element
 * @param value The value to insert
 * @throws IndexOutOfRangeException if the index is out of range
 * @throws bad_alloc if memory allocation fails
 * 
 * This function inserts a new element with the specified value at the given index in the list.
 * If the index is 0, it calls push_front().
 * if the index is equal to the size, it calls push_back(). 
 * Otherwise, it traverses the list to the position before the specified index and inserts the new node there.
 */
template <typename T>
void SingleLinkedList<T>::insert(int index, const T &value)
{
    if (index < 0 || index > size)
        throw IndexOutOfRangeException("Index out of range");

    SingleNode *node = new SingleNode(value);
    SingleNode *current = head;

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

/**
 * @brief Remove the element at a specific index from the list
 * @param index The index of the element to remove
 * @throws IndexOutOfRangeException if the index is out of range
 * @throws EmptyListException if the list is empty.
 * 
 * This function removes the element at the specified index from the list.
 * If the index is 0, it calls pop_front(). 
 * If the index is equal to the size minus one, it calls pop_back().
 * Otherwise, it traverses the list to the position before the specified index and removes the node at that position
 */
template <typename T>
void SingleLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index > size)
        throw IndexOutOfRangeException("Index out of range");

    if (index == 0)
    {
        pop_front();
    }
    else if (index == size)
    {
        pop_back();
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

/**
 * @brief Reverse the order of elements in the list
 * @throws EmptyListException if the list is empty
 * 
 * This function reverses the order of elements in the list by changing the direction of the next pointers in each node. 
 * After reversal, the head becomes the tail and the tail becomes the head.
 */
template <typename T>
void SingleLinkedList<T>::reverse()
{
    if (head == nullptr)
        throw EmptyListException("Empty list exception");

    if (head->next == nullptr) return;

    SingleLinkedList<T>::SingleNode *prev = head;
    SingleLinkedList<T>::SingleNode *current = head;
    SingleLinkedList<T>::SingleNode *next = head;
    tail = head;

    while(current != nullptr){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

/**
 * @brief Sort the elemets in the list
 * @param isDesc If true, sort in descending order; otherwise, sort in ascending order
 * @throws EmptyListException if the list is empty
 * 
 * This function sorts the elements in the list in either ascending or descending order based on the isDesc parameter.
 * It uses std::sort to sort the nodes by their values and then reconnects them in the sorted order.
 * 
 * @todo Apply merge sort to redfuce space complexity
 */
template <typename T>
void SingleLinkedList<T>::sort(bool isDesc)
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    if(head->next == nullptr) return;

    std::vector<SingleLinkedList<T>::SingleNode *> listNode;
    SingleLinkedList<T>::SingleNode *node = head;
    while(node != nullptr){
        listNode.push_back(node);
        node = node->next;
    }

    if(isDesc){
        std::sort(listNode.begin(), listNode.end(), [](SingleLinkedList<T>::SingleNode *a, SingleLinkedList<T>::SingleNode *b){
            return a->value > b->value;
        })
    } else {
        std::sort(listNode.begin(), listNode.end(), [](SingleLinkedList<T>::SingleNode *a, SingleLinkedList<T>::SingleNode *b){
            return a->value < b->value;
        })
    }

    for(int i = 0; i <listNode.size(); i++) {
        listNode[i]->next = listNode[i+1];
    }
    listNode.back()->next = nullptr;

    head = listNode.front();
    tail = listNode.back();
}

/**
 * @brief Remove duplicate elements from the list
 * @throws EmptyListException if the list is empty
 * 
 * This function removes duplicate elements from the list, keeping only the first occurrence of each value. 
 * It uses a map to track which values have already been seen and removes sub occurrence
 */
template <typename T>
void SingleLinkedList<T>::unique()
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    std::map<T, bool> map;

    SingleNode *current = head;
    SingleNode *previous = head;
    while (current != nullptr)
    {
        if (map.find(current->value) != map.end())
        {
            previous->next = current->next;
            --size;
            if (current == tail)
            {
                tail = previous;
            }
            delete current;
            current = previous;
        }
        else
        {
            map[current->value] = true;
        }
        previous = current;
        current = current->next;
    }
}

/**
 * @brief Convert the list to a vector
 * @return A vector containing all element of the list in order
 * @throws EmptyListException if the list is empty
 * 
 * This function creates a vector containing all elements of the list in the same order as they appear in the list.
 * It traverses the list from head to tail and adds each element's value to the vector.
 */
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

/**
 * @brief Merge this list with another list
 * @param other The list to mergge with this list
 * @throws LinkedListException if the other list is not a SingleLinkedList
 * 
 * This function merges this list with another list by connecting the tail of this list to the head of the other list.
 * After merging, the other list becomes empty.
 * The size of this list is updated to reflect the combined size of both lists.
 */
template <typename T>
void SingleLinkedList<T>::merge(LinkedList<T> &other)
{
    if (other.getHead() == nullptr)
        return;

    try
    {
        SingleLinkedList<T> *otherSLL = dynamic_cast<SingleLinkedList<T> *>(&other);
        tail->next = otherSLL->getHead();
        tail = otherSLL->getTail();
        size += other.getSize();

        otherSLL->head = nullptr;
        otherSLL->tail = nullptr;
        otherSLL->size = 0;
    }
    catch (const std::bad_cast &e)
    {
        throw LinkedListException("Can't cast to SingleLinkedList");
    }
}

/**
 * @brief Print the element of the list to stdout
 * 
 * This function prints all elements of the list to stdout in order, with each element followed by " -> " expect for the last element wich is followed by "nullptr".
 * It also prints the size of the list
 */
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

/**
 * @brief Copy elements from another list to this list
 * @param other Thie list to copy elements from
 * @throws EmptyListException if the other list is empty
 * @throws LinkedListException if the other list is not a SingleLinkedList
 * 
 * This function copies all elements from another list to this list. 
 * It first clears this list and then adds all elements from the oterh list in the same order.
 */
template <typename T>
void SingleLinkedList<T>::copyFrom(const LinkedList<T> &other)
{
    if (other.getHead() == nullptr)
        throw EmptyListException("List is empty");

    SingleNode *current = head;
    try
    {
        const SingleLinkedList<T> *otherSLL = dynamic_cast<const SingleLinkedList<T> *>(&other);
        SingleNode *copiedPtr = otherSLL->getHead();

        clear();

        while (copiedPtr != nullptr)
        {
            push_back(copiedPtr->value);
            copiedPtr = copiedPtr->next;
        }
    }
    catch (const std::bad_cast &e)
    {
        throw LinkedListException("Can't cast to SingleLinkedList");
    }
}

/**
 * @brief Create a lone of this list
 * @return A pointer to a new SingleLinkedList that is a copy of this list
 * @throws EmptyListException if this list is empty
 * 
 * This function creates a new SingleLinkedList that is a copy of this list.It uses the copy constructor to create the clone
 */
template <typename T>
SingleLinkedList<T> *SingleLinkedList<T>::clone() const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

    return new SingleLinkedList<T>(*this);
}

/**
 * @brief Check if this list is equal to another list
 * @param other The list to compare with this list
 * @return true if the lists are equal, false otherwise
 * @throws LinkedListException if the other list is not a SingleLinkedList
 * 
 * This function compares this list with another list for equality. 
 * Two list considered equal if they have the same size and all corresponding elements are equal.
 */
template <typename T>
bool SingleLinkedList<T>::equals(const LinkedList<T> &other) const
{
    if (size != other.getSize())
        return false;

    SingleNode *current = head;
    try
    {
        const SingleLinkedList<T> *otherSLL = dynamic_cast<const SingleLinkedList<T> *>(&other);
        SingleNode *compare_ptr = otherSLL->getHead();

        while (current != nullptr)
        {
            if (current->value != compare_ptr->value)
                return false;

            current = current->next;
            compare_ptr = compare_ptr->next;
        }
    }
    catch (const std::bad_cast &e)
    {
        throw LinkedListException("Can't cast to SingleLinkedList");
    }

    return true;
}

/** 
 * @brief Swap the contents of this list with another list
 * @param other The list to swap contents with
 * @throws LinkedListException if the other list is not a SingleLinkedList
 * 
 * This function swaps the contents of this list with another list by exchanging their head pointers, tali pointers, and sizes.
*/
template <typename T>
void SingleLinkedList<T>::swap(LinkedList<T> &other)
{
    SingleNode *current = head;
    try
    {
        SingleLinkedList<T> *otherSLL = dynamic_cast<SingleLinkedList<T> *>(&other);

        std::swap(this->head, otherSLL->head);
        std::swap(this->size, otherSLL->size);
        std::swap(this->tail, otherSLL->tail);
    }
    catch (const std::bad_cast &e)
    {
        throw LinkedListException("Can't cast to SingleLinkedList");
    }
}

/**
 * @brief Get the middle element of the list
 * @return The value of the middle element in the list
 * @throws EmptyListException if the list is empty
 * 
 * This function returns the value of the middle element in the list.
 * If the list has an even number of elements, it returns the element at index size/2.
 * If the list has odd number of elements, it also returns the element at index size/2.
 * (using integer division)
 */
template <typename T>
T SingleLinkedList<T>::mid() const
{
    return at(size / 2);
}

/**
 * @brief Get the head node of the list
 * @return Pointer to the head node of the list, or nullptr if the list is empty
 * 
 * This function returns a pointer to the head node of the list.
 * If the list is empty, it returns nullptr.
 */
template <typename T>
typename SingleLinkedList<T>::SingleNode *SingleLinkedList<T>::getHead() const
{
    return head;
}

/**
 * @brief Get the tail node of the list
 * @return Pointer to the tail node of the list, or nullptr if the list is empty
 * 
 * This function returns a pointer to the tail node of the list.
 * If the list is empty, it returns nullptr.
 */
template <typename T>
typename SingleLinkedList<T>::SingleNode *SingleLinkedList<T>::getTail() const
{
    return tail;
}