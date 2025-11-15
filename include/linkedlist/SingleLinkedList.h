#pragma once
#include "linkedlist/LinkedList.h"

template <typename T>
class SingleLinkedList : public LinkedList<T> {
    public:
        struct SingleNode : public LinkedList<T>::BaseNode {
            SingleNode* next;
            SingleNode(const T& value) : LinkedList<T>::BaseNode(value), next(nullptr) {}
        };
    private:
        
        SingleNode* head;
        SingleNode* tail;
        int size;
   public:
        //Constructor/Destructor
        SingleLinkedList() : head(nullptr), size(0) {}
        SingleLinkedList(SingleNode *head, int size) : head(head), size(size) {}
        SingleLinkedList(const SingleLinkedList<T>& other)
            : head(nullptr), tail(nullptr), size(0)
        {
            if (other.head == nullptr)
                return;

            SingleNode* current = other.getHead();
            while (current != nullptr)
            {
                this->push_back(current->value);
                current = current->next;
            }
        }
        ~SingleLinkedList() override {
            clear();
        }
        //Function
        void push_front(const T& value) override;
        void push_back(const T& value) override;
        void pop_front() override;
        void pop_back() override;
        bool remove(const T& value) override;
        bool contains(const T& value) const override;
        SingleNode* find(const T& value) const override;
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
        SingleLinkedList<T>* clone() const override;
        bool equals(const LinkedList<T>& other) const override;
        void swap(LinkedList<T>& other) override;
        T mid() const override;
        SingleNode* getHead() const override;
        SingleNode* getTail() const override;
};

#include "detail/SingleLinkedList.tpp"