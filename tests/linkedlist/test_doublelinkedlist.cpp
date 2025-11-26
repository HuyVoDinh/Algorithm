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

TEST_F(DoubleLinkedListTextFixture, CopyConstructor_NonEmptyList)
{
    DoubleLinkedList<int> list2(list);
    EXPECT_EQ(list2.getSize(), 7);
    EXPECT_EQ(list2.getHead()->value, 10);
    EXPECT_EQ(list2.getTail()->value, 30);
    EXPECT_EQ(list2.getHead(), list.getHead());
}

TEST(DoubleLinkedListTest, PushFront_EmptyList)
{
    DoubleLinkedList<int> list;
    list.push_front(10);

    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 1);

    list.clear();
}

TEST_F(DoubleLinkedListTextFixture, PUshFront_NonEmptyList)
{
    int curSize = list.getSize();
    list.push_front(5);
    curSize++;

    EXPECT_EQ(list.getHead()->value, 5);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST(DoubleLinkedListTest, PushFront_Multipelements)
{
    DoubleLinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);

    EXPECT_EQ(list.getHead()->value, 30);
    EXPECT_EQ(list.getSize(), 3);

    std::vector<int> v = list.toVector();
    EXPECT_EQ(v[0], 30);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 10);
}

TEST(DoubleLinkedListTest, PushBack_EmptyList)
{
    DoubleLinkedList<int> list;

    list.push_back(10);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 1);
    list.clear();
}

TEST_F(DoubleLinkedListTextFixture, PushBack_NonEmptyList)
{
    int curSize = list.getSize();
    list.push_back(40);
    curSize++;

    DoubleLinkedList<int>::DoubleNode *finalNode = list.getHead();

    while (finalNode->next != nullptr)
    {
        finalNode = finalNode->next;
    }
    EXPECT_EQ(finalNode->value, 40);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST(DoubleLinkedListTest, PopFront_EmptyList)
{
    DoubleLinkedList<int> list;
    EXPECT_THROW(list.pop_front(), EmptyListException);
}

TEST(DoubleLinkedListTest, PopFront_NonEmptyLIst_OneElement)
{
    DoubleLinkedList<int> list;
    list.push_front(10);

    int curSize = list.getSize();
    DoubleLinkedList<int>::DoubleNode *secondNode = list.getHead()->next;
    list.pop_front();
    curSize--;

    EXPECT_EQ(list.getHead(), secondNode);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST(DoubleLinkedListTest, PopBack_EmptyList_ThrowException)
{
    DoubleLinkedList<int> list;

    EXPECT_THROW(list.pop_back(), EmptyListException);
}

TEST(DoubleLinkedListTest, PopBack_OneElement_EmptyList)
{
    DoubleLinkedList<int> list;
    list.push_front(10);
    list.pop_back();
    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getSize(), 0);
}

TEST_F(DoubleLinkedListTextFixture, PopBack_ManyElement_RemoveEndElement)
{
    int curSize = list.getSize();
    list.pop_back();
    curSize--;

    DoubleLinkedList<int>::DoubleNode *finalNode = list.getHead();
    while (finalNode->next != nullptr)
    {
        finalNode = finalNode->next;
    }

    EXPECT_EQ(finalNode->value, 40);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST(DoubleLinkedListTest, Remove_OneElement_RemoveValidElement)
{
    DoubleLinkedList<int> list;
    list.push_back(10);

    EXPECT_EQ(list.remove(10), true);
    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getSize(), 0);
}

TEST_F(DoubleLinkedListTextFixture, Remove_ManyElement_RemoveValidElementAtFirst)
{
    bool result = list.remove(10);

    DoubleLinkedList<int>::DoubleNode *isLinked = list.getHead();
    while (isLinked != nullptr)
    {
        isLinked = isLinked->next;
    }

    EXPECT_EQ(result, true);
    EXPECT_EQ(isLinked, nullptr);
    EXPECT_EQ(list.getHead()->value, 20);
    EXPECT_EQ(list.getSize(), 6);
}

TEST_F(DoubleLinkedListTextFixture, Remove_ManyElement_RemoveValidElementAtMid)
{
    bool result = list.remove(20);

    DoubleLinkedList<int>::DoubleNode *isLinked = list.getHead();
    while (isLinked != nullptr)
    {
        isLinked = isLinked->next;
    }

    EXPECT_EQ(result, true);
    EXPECT_EQ(isLinked, nullptr);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 6);
}

TEST(DoubleLinkedListTest, Remove_EmptyList_ThrowException)
{
    DoubleLinkedList<int> list;
    EXPECT_THROW(list.remove(5), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, Remove_ManyElement_RemoveInvalidElement)
{
    bool result = list.remove(15);

    DoubleLinkedList<int>::DoubleNode *isLinked = list.getHead();
    while (isLinked != nullptr)
    {
        isLinked = isLinked->next;
    }

    EXPECT_EQ(result, false);
    EXPECT_EQ(isLinked, nullptr);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 7);
}

TEST(DoubleLinkedListTest, Contains_EmptyList_ThrowException)
{
    DoubleLinkedList<int> list;

    EXPECT_THROW(list.contains(5), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, Contains_ManyElement_ValidValue)
{
    EXPECT_EQ(list.contains(20), true);
}

TEST_F(DoubleLinkedListTextFixture, Contains_ManyElement_InvalidValue)
{
    EXPECT_EQ(list.contains(15), false);
}

TEST(DoubleLinkedListTest, Find_EmptyList_ThrowException)
{
    DoubleLinkedList<int> list;

    EXPECT_THROW(list.find(5), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, Find_ManyElement_ValidValue)
{
    EXPECT_EQ(list.find(20)->value, 20);
}

TEST_F(DoubleLinkedListTextFixture, Find_ManyElement_InvalidValue)
{
    EXPECT_EQ(list.find(15), nullptr);
}

TEST(DoubleLinkedListTest, Front_EmptyList_ThrowException)
{
    DoubleLinkedList<int> list;

    EXPECT_THROW(list.front(), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, Front_ManyElement_ReturnFirstElement)
{
    EXPECT_EQ(list.front(), 10);
}

TEST(DoubleLinkedListTest, Back_EmptyList_ThrowException)
{
    DoubleLinkedList<int> list;

    EXPECT_THROW(list.back(), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, Back_ManyElement_ReturnEndElement)
{
    EXPECT_EQ(list.back(), 30);
}

TEST_F(DoubleLinkedListTextFixture, Clear_ManyElement_ClearAllElement)
{
    list.clear();

    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getSize(), 0);
}

TEST(DoubleLinkedListTest, GetSize_EmptyList_ReturnSize)
{
    DoubleLinkedList<int> list;

    EXPECT_EQ(list.getSize(), 0);
}