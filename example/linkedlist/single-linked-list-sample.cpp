#include "linkedlist/SingleLinkedList.h"
#include <iostream>

int main()
{
    SingleLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.print(); // Expected output: 5 10 20

    list.pop_front();
    list.print(); // Expected output: 10 20

    list.pop_back();
    list.print(); // Expected output: 10

    std::cout << "Front: " << list.front() << std::endl; // Expected output: Front: 10
    std::cout << "Back: " << list.back() << std::endl;   // Expected output: Back: 10

    list.clear();
    std::cout << "Is Empty: " << (list.isEmpty() ? "Yes" : "No") << std::endl; // Expected output: Is Empty: Yes

    return 0;
}
