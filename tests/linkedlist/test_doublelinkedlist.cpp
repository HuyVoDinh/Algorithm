#include <gtest/gtest.h>
#include "linkedlist/DoubleLinkedList.h"
#include "linkedlist/exception/LinkedListException.h"
#include <vector>
#include <iostream>

TEST(DoubleLinkedListTest, Constructor1_P)
{
    DoubleLinkedList<int> list;

    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getSize(), 0);
}

TEST(DoubleLinkedListTest, Constructor2_P)
{
    DoubleLinkedList<int>::DoubleNode *node1 = new DoubleLinkedList<int>::DoubleNode(10);
    DoubleLinkedList<int>::DoubleNode *node2 = new DoubleLinkedList<int>::DoubleNode(10);
    DoubleLinkedList<int>::DoubleNode *node3 = new DoubleLinkedList<int>::DoubleNode(10);

    node1->next = node2;
    node2->next = node3;
    node2->previous = node1;
    node3->previous = node2;

    DoubleLinkedList<int> list(node1, 3);
    EXPECT_EQ(list.getHead(), node1);
    EXPECT_EQ(list.getSize(), 3);
}

TEST(DoubleLinkedListTest, CopyConstructor_EmptyList)
{
    DoubleLinkedList<int> list1;
    DoubleLinkedList<int> list2(list1);

    EXPECT_EQ(list2.getSize(), 0);
    EXPECT_EQ(list2.getHead(), nullptr);
}

class DoubleLinkedListTextFixture : public ::testing::Test
{
protected:
    DoubleLinkedList<int> list;

    void SetUp() override
    {
        list.push_back(10);
        list.push_back(20);
        list.push_back(60);
        list.push_back(20);
        list.push_back(40);
        list.push_back(40);
        list.push_back(30);
    }

    void TearDown() override
    {
        list.clear();
    }
};
