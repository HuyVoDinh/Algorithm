#pragma once
#include "linkedlist/LinkedList.h"

template <typename T>
class DoubleLinkedList : public LinkedList<T> {
    public:
        struct DoubleNode : public LinkedList<T>::BaseNode {
            DoubleNode* next;
            DoubleNode* previous;
            DoubleNode(const T& value) : LinkedList<T>::BaseNode(value), next(nullptr) {}
        };
    private:
        DoubleNode* head;
        DoubleNode* tail;
        int size;
   public:
        //Contructor/Destructor
        DoubleLinkedList() : head(nullptr), size(0) {}
        DoubleLinkedList(DoubleNode *head, int size) : head(head), size(size) {}
        DoubleLinkedList(const DoubleLinkedList<T>& other)
            : head(nullptr), tail(nullptr), size(0)
        {
        }
        ~DoubleLinkedList() override {
            clear();
        }
        //Function
        void push_front(const T& value) override;
        void push_back(const T& value) override;
        void pop_front() override;
        void pop_back() override;
        bool remove(const T& value) override;
        bool contains(const T& value) const override;
        DoubleNode* find(const T& value) const override;
        T front() const override;
        T back() const override;
        void clear() override;
        int getSize() const override;
        bool isEmpty() const override;
        T at(int index) const override;
        int indexOf(const T& value) override;
        void insert(int index, const T& value) override;
        void removeAt(int index) override;
        void reverse() override;
        void sort(bool isDesc = false) override;
        void unique() override;
        std::vector<T> toVector() const override;
        void merge(LinkedList<T>& other) override;
        void print() const override;
        void copyFrom(const LinkedList<T>& other) override;
        DoubleLinkedList<T>* clone() const override;
        bool equals(const LinkedList<T>& other) const override;
        void swap(LinkedList<T>& other) override;
        T mid() const override;
        DoubleNode* getHead() const override;
};

#include "detail/DoubleLinkedList.tpp"