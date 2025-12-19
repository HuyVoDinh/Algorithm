#pragma once
#include "../../linkedlist/DoubleLinkedList.h"
#include "../../linkedlist/exception/LinkedListException.h"
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
 * It updates the head pointer and increments the size of the list. If the list was empty, it also updates the tail pointer.
 */
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

/**
 * @brief Add an element to the end of the list
 * @param value The value to be added to the end of the list
 * @throws bad_alloc if memory allocation fails
 *
 * This function creates a new node with the given value and places it at the end of the list.
 * It updates the tail pointer and increments the size of the list.
 * If the list was empty, it also updates the head pointer.
 */
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

/**
 * @brief Remove the first element from the list
 * @throws EmptyListException if the list is empty
 *
 * This function removes the first element from the list and updates the head pointer.
 * If the list becomes empty after removal, it also updates the tail pointer to nullptr.
 * The size of the list is decremented by one.
 */
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

/**
 * @brief Remove the last element from the list
 * @throws EmptyListException if the list is empty
 *
 * This function removes the last element from the list and updates the tail pointer.
 * If the list becomes empty after removal, it also updates the head pointer to nullptr.
 * The size of the list is decremented by one.
 */
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
        tail->next = nullptr;
        delete current;
        current = nullptr;
        --size;
    }
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
        current = current->next;
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
typename DoubleLinkedList<T>::DoubleNode *DoubleLinkedList<T>::find(const T &value) const
{
    if (head == nullptr)
        throw EmptyListException("List is empty");

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

/**
 * @brief Get the value of the first element in the list
 * @return The value of the first element in the list
 * @throws EmptyListException if the list is empty
 *
 * This function returns the value of the first element in the list without removing it.
 * It accesses the head node and returns its value.
 */
template <typename T>
T DoubleLinkedList<T>::front() const
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }
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
T DoubleLinkedList<T>::back() const
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }
    return tail->value;
}

/**
 * @brief Remove all elements from the list
 *
 * This function removes all elements from the list by traversing the list and deleting eacho node.
 * After this operation, the list becomes empty with head and tail pointers set to nullptr, and size set to zero.
 */
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

/**
 * @brief Get the number of elements in the list
 * @return The number of elements in the list
 *
 * This function returns the current size of the list, which is the number of elements currently stored in the list.
 */
template <typename T>
int DoubleLinkedList<T>::getSize() const
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
bool DoubleLinkedList<T>::isEmpty() const
{
    if (head == nullptr && tail == nullptr)
        return true;
    return false;
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
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }
    return current->value;
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
        current = current->next;
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
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        DoubleLinkedList<T>::DoubleNode *nextNode = current->next;

        newNode->next = nextNode;
        nextNode->previous = newNode;
        current->next = newNode;
        newNode->previous = current;
        ++size;
    }
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

/**
 * @brief Reverse the order of elements in the list
 * @throws EmptyListException if the list is empty
 *
 * This function reverses the order of elements in the list by changing the direction of the next pointers in each node.
 * After reversal, the head becomes the tail and the tail becomes the head.
 */
template <typename T>
void DoubleLinkedList<T>::reverse()
{
    if (head == nullptr)
        throw EmptyListException("Empty list exception");

    if (head->next == nullptr)
        return;

    DoubleLinkedList<T>::DoubleNode *prev = nullptr;
    DoubleLinkedList<T>::DoubleNode *current = head;
    DoubleLinkedList<T>::DoubleNode *next = nullptr;
    tail = head;

    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        current->previous = prev;
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
 * @todo Apply merge sort to reduce space complexity
 */
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

    for (int i = 1; i < listNode.size(); i++)
    {
        listNode[i]->previous = listNode[i - 1];
        listNode[i - 1]->next = listNode[i];
    }
    listNode.front()->previous = nullptr;
    listNode.back()->next = nullptr;
    head = listNode.front();
    tail = listNode.back();
}

/**
 * @brief Remove duplicate elements from the list
 * @throws EmptyListException if the list is empty
 *
 * This function removes duplicate elements from the list, keeping only the first occurrence of each value.
 * It uses a map to track which values have already been seen and removes subsequence occurrence
 */
template <typename T>
void DoubleLinkedList<T>::unique()
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }

    std::map<T, bool> map;

    DoubleLinkedList<T>::DoubleNode *current = head;
    DoubleLinkedList<T>::DoubleNode *previous = head;
    DoubleLinkedList<T>::DoubleNode *next = current->next;
    while (current != nullptr)
    {
        next = current->next;
        if (map.find(current->value) != map.end())
        {
            next->previous = previous;
            previous->next = next;
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
        current = next;
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
std::vector<T> DoubleLinkedList<T>::toVector() const
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }
    DoubleLinkedList<T>::DoubleNode *current = head;

    std::vector<T> list;
    while (current != nullptr)
    {
        list.push_back(current->value);
        current = current->next;
    }

    return list;
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

/**
 * @brief Print the element of the list to stdout
 *
 * This function prints all elements of the list to stdout in order, with each element followed by " -> " expect for the last element wich is followed by "nullptr".
 * It also prints the size of the list
 */
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
void DoubleLinkedList<T>::copyFrom(const LinkedList<T> &other)
{
    if (other.getHead() == nullptr)
    {
        throw EmptyListException("List is empty");
    }
    DoubleLinkedList<T>::DoubleNode *current = head;
    try
    {
        const DoubleLinkedList<T> *otherDLL = dynamic_cast<const DoubleLinkedList<T> *>(&other);
        DoubleLinkedList<T>::DoubleNode *copiedPtr = otherDLL->getHead();

        clear();

        while (copiedPtr != nullptr)
        {
            push_back(copiedPtr->value);
            copiedPtr = copiedPtr->next;
        }
    }
    catch (const std::bad_cast &e)
    {
        throw LinkedListException("Can't cast to Double Linked List");
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
DoubleLinkedList<T> *DoubleLinkedList<T>::clone() const
{
    if (head == nullptr)
    {
        throw EmptyListException("List is empty");
    }
    return new DoubleLinkedList<T>(*this);
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
bool DoubleLinkedList<T>::equals(const LinkedList<T> &other) const
{
    DoubleLinkedList<T>::DoubleNode *current = head;
    const DoubleLinkedList<T> *otherDLL = dynamic_cast<const DoubleLinkedList<T> *>(&other);
    DoubleLinkedList<T>::DoubleNode *currentOther = otherDLL->getHead();

    if (size != otherDLL->getSize())
    {
        return false;
    }

    while (current != nullptr)
    {
        if (current->value != currentOther->value)
        {
            return false;
        }
        current = current->next;
        currentOther = currentOther->next;
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
void DoubleLinkedList<T>::swap(LinkedList<T> &other)
{
    try
    {
        DoubleLinkedList<T> *otherDLL = dynamic_cast<DoubleLinkedList<T> *>(&other);
        std::swap(head, otherDLL->head);
        std::swap(tail, otherDLL->tail);
        std::swap(size, otherDLL->size);
    }
    catch (std::bad_cast &e)
    {
        throw LinkedListException("Can't cast to Double Linked List");
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
T DoubleLinkedList<T>::mid() const
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
typename DoubleLinkedList<T>::DoubleNode *DoubleLinkedList<T>::getHead() const
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
typename DoubleLinkedList<T>::DoubleNode *DoubleLinkedList<T>::getTail() const
{
    return tail;
}