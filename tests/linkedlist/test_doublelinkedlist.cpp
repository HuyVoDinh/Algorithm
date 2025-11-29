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
    EXPECT_EQ(list2.getHead()->value, list.getHead()->value);
    EXPECT_EQ(list2.getTail()->value, list.getTail()->value);
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

TEST_F(DoubleLinkedListTextFixture, GetSize_ManyElement_ReturnSize){
    EXPECT_EQ(list.getSize(), 7);
}

TEST(DoubleLinkedListTest, IsEmpty_EmptyList_ReturnEmpty){
    DoubleLinkedList<int> list;

    EXPECT_EQ(list.isEmpty(), true);
}

TEST_F(DoubleLinkedListTextFixture, IsEmpty_ManyElement_IsNotEmpty){
    EXPECT_EQ(list.isEmpty(), false);
}

TEST(DoubleLinkedListTest, At_EmptyList_ThrowException){
    DoubleLinkedList<int> list;
    EXPECT_THROW(list.at(0), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, At_NonEmpty_InvalidIndex_ThrowException1){
    EXPECT_THROW(list.at(-1), IndexOutOfRangeException);
}

TEST_F(DoubleLinkedListTextFixture, At_NonEmpty_InvalidIndex_ThrowException2){
    EXPECT_THROW(list.at(list.getSize()), IndexOutOfRangeException);
}

TEST_F(DoubleLinkedListTextFixture, At_NonEmptyList_ValidIndex_ReturnValue){
    EXPECT_EQ(list.at(1),20);
}

TEST_F(DoubleLinkedListTextFixture, IndexOf_NonEmptyList_ValidValue_ReturnIndex){
    EXPECT_EQ(list.indexOf(20),1);
}

TEST_F(DoubleLinkedListTextFixture, IndexOf_NonEmptyList_InvalidValue_ReturnNonIndex){
    EXPECT_EQ(list.indexOf(25), -1);
}

TEST(DoubleLinkedListTest, IndexOf_EmptyList_ThrowException){
    DoubleLinkedList<int> list;

    EXPECT_THROW(list.indexOf(1), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, Insert_NonEmpty_InvalidIndex_ThrowException1){
    EXPECT_THROW(list.insert(-1,40), IndexOutOfRangeException);
}

TEST_F(DoubleLinkedListTextFixture, Insert_NonEmpty_InvalidIndex_ThrowException2){
    EXPECT_THROW(list.insert(list.getSize() +1,40), IndexOutOfRangeException);
}

TEST_F(DoubleLinkedListTextFixture, Insert_NonEmpty_ValidIndex_FirstIndex){
    int curSize = list.getSize();
    list.insert(0, 40);
    curSize++;

    DoubleLinkedList<int>::DoubleNode *current = list.getHead();
    while(current != nullptr){
        current = current->next;
    }

    EXPECT_EQ(current, nullptr);
    EXPECT_EQ(list.getSize(), curSize);
    EXPECT_EQ(list.getHead()->value, 40);
}

TEST_F(DoubleLinkedListTextFixture, Insert_NonEmpty_ValidIndex_FinalIndex){
    int curSize = list.getSize();
    list.insert(list.getSize(), 40);
    curSize++;

    DoubleLinkedList<int>::DoubleNode *current = list.getHead();
    while(current->next != nullptr){
        current = current->next;
    }

    EXPECT_EQ(current->next, nullptr);
    EXPECT_EQ(current->value, 40);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST_F(DoubleLinkedListTextFixture, Insert_NonEmpty_ValidIndex_RandomIndex){
    int curSize = list.getSize();
    list.insert(1, 40);
    curSize++;

    DoubleLinkedList<int>::DoubleNode *current = list.getHead();
    while(current->next != nullptr){
        current = current->next;
    }

    EXPECT_EQ(current->next, nullptr);
    EXPECT_EQ(list.indexOf(40), 1);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST_F(DoubleLinkedListTextFixture, RemoveAt_NonEmpty_InvalidIndex){
    EXPECT_THROW(list.removeAt(-1), IndexOutOfRangeException);
    EXPECT_THROW(list.removeAt(list.getSize()), IndexOutOfRangeException);
}

TEST(DoubleLinkedListTest, RemoveAt_OneElement){
    DoubleLinkedList<int> list;
    list.push_back(10);

    EXPECT_NO_THROW(list.removeAt(0));
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_EQ(list.getHead(), nullptr);
}

TEST_F(DoubleLinkedListTextFixture, RemoveAt_NonEmpty_RemoveFirstIndex)
{
    DoubleLinkedList<int>::DoubleNode *secondNode = list.getHead()->next;

    EXPECT_NO_THROW(list.removeAt(0));
    EXPECT_EQ(list.getSize(), 6);
    EXPECT_EQ(list.getHead(), secondNode);
}

TEST_F(DoubleLinkedListTextFixture, RemoveAt_NonEmpty_RemoveLastIndex)
{
    
    int curSize = list.getSize();
    EXPECT_NO_THROW(list.removeAt(curSize-1));
    curSize--;
    EXPECT_EQ(curSize, list.getSize());
    DoubleLinkedList<int>::DoubleNode *current = list.getHead();
    while(current != nullptr){
        current = current->next;
    }
    EXPECT_EQ(current, nullptr);
}

TEST_F(DoubleLinkedListTextFixture, RemoveAt_NonEmpty_RemoveRandomIndex)
{
    
    int curSize = list.getSize();
    EXPECT_NO_THROW(list.removeAt(3));
    curSize--;
    EXPECT_EQ(curSize, list.getSize());
    DoubleLinkedList<int>::DoubleNode *current = list.getHead();
    while(current != nullptr){
        current = current->next;
    }
    EXPECT_EQ(current, nullptr);
}

TEST(DoubleLinkedListTest, Reverse_EmptyList_ThrowException){
    DoubleLinkedList<int> list;
    EXPECT_THROW(list.reverse(), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, Reverse_NonEmpty){
    EXPECT_NO_THROW(list.reverse());
    std::vector<int> v = list.toVector();

    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[0], 30);
    EXPECT_EQ(v[1], 40);
    EXPECT_EQ(v[2], 40);
    EXPECT_EQ(v[3], 20);
    EXPECT_EQ(v[4], 60);
    EXPECT_EQ(v[5], 20);
    EXPECT_EQ(v[6], 10);
}

TEST(DoubleLinkedListTest, Sort_EmptyList_ThrowException){
    DoubleLinkedList<int> list;
    EXPECT_THROW(list.sort(), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, Sort_NonEmptyList_Desc){
    EXPECT_NO_THROW(list.sort(true));

    EXPECT_EQ(list.getHead()->value, 60);
    EXPECT_EQ(list.getTail()->value, 10);
    EXPECT_EQ(list.getSize(), 7);
    std::vector<int> v = list.toVector();

    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[0], 60);
    EXPECT_EQ(v[1], 40);
    EXPECT_EQ(v[2], 40);
    EXPECT_EQ(v[3], 30);
    EXPECT_EQ(v[4], 20);
    EXPECT_EQ(v[5], 20);
    EXPECT_EQ(v[6], 10);
}

TEST_F(DoubleLinkedListTextFixture, Sort_NonEmptyList_Incr){
    EXPECT_NO_THROW(list.sort());

    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getTail()->value, 60);
    EXPECT_EQ(list.getSize(), 7);
    std::vector<int> v = list.toVector();

    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 20);
    EXPECT_EQ(v[3], 30);
    EXPECT_EQ(v[4], 40);
    EXPECT_EQ(v[5], 40);
    EXPECT_EQ(v[6], 60);
}

TEST(DoubleLinkedListTest, Unique_EmptyList_ThrowException){
    DoubleLinkedList<int> list;
    EXPECT_THROW(list.unique(), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, Unique_NonEmptyList_UniqueElement){
    EXPECT_NO_THROW(list.unique());
    EXPECT_EQ(list.getSize(), 5);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getTail()->value, 30);

    std::vector<int> v = list.toVector();
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 60);
    EXPECT_EQ(v[3], 40);
    EXPECT_EQ(v[4], 30);
}

TEST(DoubleLinkedListTest, Unique_NonEmptyList_KeepOne){
    DoubleLinkedList<int> list;
    list.push_front(10);
    list.push_front(10);
    list.push_front(10);
    list.push_front(10);
    
    EXPECT_NO_THROW(list.unique());
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);
}

TEST(DoubleLinkedListTest, ToVector_EmptyList_ThrowException){
    DoubleLinkedList<int> list;
    EXPECT_THROW(list.toVector(), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, ToVector_NonEmptyList_ConverToVector){
    std::vector<int> v = list.toVector();

    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 60);
    EXPECT_EQ(v[3], 20);
    EXPECT_EQ(v[4], 40);
    EXPECT_EQ(v[5], 40);
    EXPECT_EQ(v[6], 30);
}

TEST_F(DoubleLinkedListTextFixture, Merge_NonEmpty_MergeTwoLinkedList)
{
    DoubleLinkedList<int> list2;
    list2.push_front(30);
    list2.push_front(20);
    list2.push_front(10);
    int size = list.getSize() + list2.getSize();
    EXPECT_NO_THROW(list.merge(list2));

    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list2.getHead(), nullptr);

    std::vector<int> v = list.toVector();
    // list.print();
    EXPECT_EQ(list.getSize(), size);

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 60);
    EXPECT_EQ(v[3], 20);
    EXPECT_EQ(v[4], 40);
    EXPECT_EQ(v[5], 40);
    EXPECT_EQ(v[6], 30);
    EXPECT_EQ(v[7], 10);
    EXPECT_EQ(v[8], 20);
    EXPECT_EQ(v[9], 30);
}

TEST_F(DoubleLinkedListTextFixture, Print_NonEmpty)
{
    EXPECT_NO_THROW(list.print());
}

TEST_F(DoubleLinkedListTextFixture, CopyFrom_NonEmpty_CopyFromEmpty_ThrowException)
{
    DoubleLinkedList<int> list2;
    EXPECT_THROW(list.copyFrom(list2), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, CopyFrom_NonEmpty_CopyFromOtherLinkedList1)
{
    DoubleLinkedList<int> list2;
    list2.push_front(50);
    list2.push_front(60);
    list2.push_front(70);
    list2.push_front(80);

    EXPECT_NO_THROW(list.copyFrom(list2));
    EXPECT_EQ(list.getSize(), 4);
    EXPECT_EQ(list.getHead()->value, 80);
    std::vector<int> v = list2.toVector();
    EXPECT_EQ(v[0], 80);
    EXPECT_EQ(v[1], 70);
    EXPECT_EQ(v[2], 60);
    EXPECT_EQ(v[3], 50);
    EXPECT_NE(list.getHead(), list2.getHead());
}

TEST_F(DoubleLinkedListTextFixture, CopyFrom_NonEmpty_CopyFromOtherLinkedList2)
{
    DoubleLinkedList<int> list2;
    list2.push_front(50);
    list2.push_front(60);

    EXPECT_NO_THROW(list.copyFrom(list2));
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.getHead()->value, 60);
    std::vector<int> v = list2.toVector();
    EXPECT_EQ(v[0], 60);
    EXPECT_EQ(v[1], 50);
    EXPECT_NE(list.getHead(), list2.getHead());
}

TEST_F(DoubleLinkedListTextFixture, CopyFrom_NonEmpty_CopyFromOtherLinkedList3)
{
    DoubleLinkedList<int> list2;
    list2.push_front(50);
    list2.push_front(60);
    list2.push_front(70);

    EXPECT_NO_THROW(list.copyFrom(list2));
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getHead()->value, 70);
    std::vector<int> v = list2.toVector();
    EXPECT_EQ(v[0], 70);
    EXPECT_EQ(v[1], 60);
    EXPECT_EQ(v[2], 50);
    EXPECT_NE(list.getHead(), list2.getHead());
}

TEST(DoubleLinkedListTest, CopyFrom_NonEmpty_CopyFromOtherLinkedList4)
{
    DoubleLinkedList<int> list;
    DoubleLinkedList<int> list2;
    list2.push_front(50);
    list2.push_front(60);
    list2.push_front(70);

    EXPECT_NO_THROW(list.copyFrom(list2));
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.getHead()->value, 70);
    std::vector<int> v = list2.toVector();
    EXPECT_EQ(v[0], 70);
    EXPECT_EQ(v[1], 60);
    EXPECT_EQ(v[2], 50);
    EXPECT_NE(list.getHead(), list2.getHead());
}

TEST(DoubleLinkedListTest, Clone_EmptyList_ThrowException)
{
    DoubleLinkedList<int> list;
    EXPECT_THROW(list.clone(), EmptyListException);
}

TEST_F(DoubleLinkedListTextFixture, Clone_NonEmpty_CloneList)
{
    // LinkedList<int> *clone = new DoubleLinkedList<int>();
    DoubleLinkedList<int> *clone;
    clone = list.clone();
    EXPECT_NE(clone->getHead(), list.getHead());
    EXPECT_EQ(clone->getSize(), list.getSize());
}

TEST_F(DoubleLinkedListTextFixture, Equals_CompareEqual)
{
    DoubleLinkedList<int> list2;
    list2.push_back(10);
    list2.push_back(20);
    list2.push_back(60);
    list2.push_back(20);
    list2.push_back(40);
    list2.push_back(40);
    list2.push_back(30);

    EXPECT_EQ(list.equals(list2), true);
}

TEST_F(DoubleLinkedListTextFixture, Equals_CompareNotEqual)
{
    DoubleLinkedList<int> list2;
    list2.push_back(10);
    list2.push_back(20);
    list2.push_back(60);
    list2.push_back(20);
    list2.push_back(40);
    list2.push_back(40);
    list2.push_back(35);

    EXPECT_EQ(list.equals(list2), false);
}

TEST_F(DoubleLinkedListTextFixture, Swap_SwapTwoLinkedList)
{
    DoubleLinkedList<int> list2;
    list2.push_back(5);
    list2.push_back(15);

    DoubleLinkedList<int>::DoubleNode *node = list.getHead();
    DoubleLinkedList<int>::DoubleNode *node2 = list2.getHead();
    int size = list.getSize();
    int size2 = list2.getSize();

    list.swap(list2);
    EXPECT_EQ(list.getHead(), node2);
    EXPECT_EQ(list2.getHead(), node);
    EXPECT_EQ(list.getSize(), size2);
    EXPECT_EQ(list2.getSize(), size);
}

TEST_F(DoubleLinkedListTextFixture, Mid_GetMidElement)
{
    int midValue = list.at(list.getSize() / 2);

    EXPECT_EQ(list.mid(), midValue);
}

TEST_F(DoubleLinkedListTextFixture, GetHead_ReturnHead)
{
    EXPECT_NO_THROW(list.getHead());
}

TEST(DoubleLinkedListTest, GetHead_EmptyList)
{
    DoubleLinkedList<int> list;
    EXPECT_EQ(list.getHead(), nullptr);
}

TEST(DoubleLinkedListTest, GetTail_EmptyList)
{
    DoubleLinkedList<int> list;
    EXPECT_EQ(list.getTail(), nullptr);
}

TEST_F(DoubleLinkedListTextFixture, GetTail_ReturnTail)
{

    DoubleLinkedList<int>::DoubleNode *node = list.getHead();
    while (node->next != nullptr)
    {
        node = node->next;
    }

    EXPECT_EQ(node, list.getTail());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}