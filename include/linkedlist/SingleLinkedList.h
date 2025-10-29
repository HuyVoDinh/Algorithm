#pragma once
#include "../linkedlist/LinkedList.h"

template <typename T>
class SingleLinkedList : public LinkedList<T> {
    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& value) : data(value), next(nullptr) {}
        };
        Node* head;
        int size;
   public:
        //Contructor/Destructor
        SingleLinkedList() : head(nullptr), size(0) {}
        ~SingleLinkedList() override {
            clear();
        }
        //Function
        void push_front(const T& value) override;
        void push_back(const T& value) override;
        void pop_front() override;
        void pop_back() override;
        void remove(const T& value) override;
        bool contains(const T& value) const override;
        Node* find(const T& value) const override;
        T front() const override;
        T back() const override;
        void clear() override;
        int getSize() const override;
        bool isEmpty() const override;
        T at(int index) const override;
        void indexOf(const T& value) override;
        void insert(int index, const T& value) override;
        void removeAt(const T& value) override;
        void reverse() override;
        void sort() override;
        void unique() override;
        std::vector<T> toVector() const override;
        void merge(LinkedList<T>& other) override;
        void print() const override;
        void copyFrom(const LinkedList<T>& other) override;
        LinkedList<T>* clone() const override;
        bool equals(const LinkedList<T>& other) const override;
        void swap(LinkedList<T>& other) override;
        T mid() const override;
        Node* getHead() const override;
};

#include "detail/SingleLinkedList.tpp"