#pragma once
#include <vector>
template <typename T>
class LinkedList {
   public:
        struct BaseNode {
                T value;
                BaseNode(const T& value) : value(value) {}
                virtual ~BaseNode() = default;
        };
        //Contructor/Destructor
        virtual ~LinkedList() = default;
        //Function
        virtual void push_front(const T& value) = 0;
        virtual void push_back(const T& value) = 0;
        virtual void pop_front() = 0;
        virtual void pop_back() = 0;
        virtual void remove(const T& value) = 0;
        virtual bool contains(const T& value) const = 0;
        virtual BaseNode* find(const T& value) const = 0;
        virtual T front() const = 0;
        virtual T back() const = 0;
        virtual void clear() = 0;
        virtual int getSize() const = 0;
        virtual bool isEmpty() const = 0;
        virtual T at(int index) const = 0;
        virtual int indexOf(const T& value) = 0;
        virtual void insert(int index, const T& value) = 0;
        virtual void removeAt(int index) = 0;
        virtual void reverse() = 0;
        virtual void sort() = 0;
        virtual void unique() = 0;
        virtual std::vector<T> toVector() const = 0;
        virtual void merge(LinkedList<T>& other) = 0;
        virtual void print() const = 0;
        virtual void copyFrom(const LinkedList<T>& other) = 0;
        virtual LinkedList<T>* clone() const = 0;
        virtual bool equals(const LinkedList<T>& other) const = 0;
        virtual void swap(LinkedList<T>& other) = 0;
        virtual T mid() const = 0;
        virtual BaseNode* getHead() const = 0;
};