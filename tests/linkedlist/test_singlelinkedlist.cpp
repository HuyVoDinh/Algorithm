#include <gtest/gtest.h>
#include "linkedlist/singlelinkedlist.h"
#include "../../../include/linkedlist/exception/LinkedListException.h"

#include <iostream>
TEST(SingleLinkedListTest, Constructor1_P) {
    SingleLinkedList<int> list;

    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SingleLinkedListTest, Constructor2_P){
    SingleLinkedList<int>::SingleNode* node1 = new SingleLinkedList<int>::SingleNode(10);
    SingleLinkedList<int>::SingleNode* node2 = new SingleLinkedList<int>::SingleNode(20);
    SingleLinkedList<int>::SingleNode* node3 = new SingleLinkedList<int>::SingleNode(10);

    node1->next = node2;
    node2->next = node3;

    SingleLinkedList<int> list(node1,3);
    EXPECT_EQ(list.getHead(), node1);
    EXPECT_EQ(list.getSize(), 3);
}

class SingleLinkedListTextFixture : public ::testing::Test{
    protected: 
        SingleLinkedList<int> list;

        void SetUp() override{
            list.push_back(10);
            list.push_back(20);
            list.push_back(30);
        }

        void TearDown() override{
            list.clear();
        }
};

TEST(SingleLinkedListTest, PushFront_EmptyList){
    SingleLinkedList<int> list;
    list.push_back(10);

    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 1);

    list.clear();
}

TEST_F(SingleLinkedListTextFixture,PushFront_NonEmptyList) {
    int curSize = list.getSize();
    list.push_back(5);
    curSize++;

    EXPECT_EQ(list.getHead()->value,5);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST(SingleLinkedListTest, PushBack_EmptyList) {
    SingleLinkedList<int> list;

    list.push_back(10);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 1);
    list.clear();
}

TEST_F(SingleLinkedListTextFixture, PushBack_NonEmptyList) {
    int curSize = list.getSize();
    list.push_back(40);
    curSize++;

    SingleLinkedList<int>::SingleNode *finalNode = list.getHead();

    while(finalNode->next != nullptr) {
        finalNode = finalNode->next;
    }

    EXPECT_EQ(finalNode->value, 40);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST(SingleLinkedListTest, PopFront_EmptyList) {
    SingleLinkedList<int> list;
    
    EXPECT_THROW(list.pop_front(), EmptyListException);
}

TEST(SingleLinkedListTest, PopFront_NonEmptyList_OneElement)
{
    SingleLinkedList<int> list;
    list.push_front(10);

    int curSize = list.getSize();
    SingleLinkedList<int>::SingleNode *secondNode = list.getHead()->next;
    list.pop_front();
    curSize--;
    
    EXPECT_EQ(list.getHead(), secondNode);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST_F(SingleLinkedListTextFixture, PopFront_NonEmptyList_ManyElements) {
    int curSize = list.getSize();
    SingleLinkedList<int>::SingleNode *secondNode = list.getHead()->next;
    list.pop_front();
    curSize--;
    
    EXPECT_EQ(list.getHead(), secondNode);
    EXPECT_EQ(list.getSize(), curSize);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}