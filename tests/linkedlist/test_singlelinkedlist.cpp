#include <gtest/gtest.h>
#include "linkedlist/singlelinkedlist.h"
#include "linkedlist/exception/LinkedListException.h"
#include <vector>
#include <iostream>
TEST(SingleLinkedListTest, Constructor1_P)
{
    SingleLinkedList<int> list;

    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SingleLinkedListTest, Constructor2_P)
{
    SingleLinkedList<int>::SingleNode *node1 = new SingleLinkedList<int>::SingleNode(10);
    SingleLinkedList<int>::SingleNode *node2 = new SingleLinkedList<int>::SingleNode(20);
    SingleLinkedList<int>::SingleNode *node3 = new SingleLinkedList<int>::SingleNode(10);

    node1->next = node2;
    node2->next = node3;

    SingleLinkedList<int> list(node1, 3);
    EXPECT_EQ(list.getHead(), node1);
    EXPECT_EQ(list.getSize(), 3);
}

TEST(SingleLinkedListTest, CopyConstructor_EmptyList)
{
    SingleLinkedList<int> list1;
    SingleLinkedList<int> list2(list1);

    EXPECT_EQ(list2.getSize(), 0);
    EXPECT_EQ(list2.getHead(), nullptr);
}

class SingleLinkedListTextFixture : public ::testing::Test
{
protected:
    SingleLinkedList<int> list;

    void SetUp() override
    {
        std::cout << "Debug\n";
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

TEST_F(SingleLinkedListTextFixture, CopyConstructor_NonEmptyList)
{
    SingleLinkedList<int> list2(list);
    EXPECT_EQ(list2.getSize(), 7);
    EXPECT_EQ(list2.getHead()->value, 10);
    EXPECT_EQ(list2.getTail()->value, 30);
    EXPECT_NE(list.getHead(), list2.getHead());
}

TEST(SingleLinkedListTest, PushFront_EmptyList)
{
    SingleLinkedList<int> list;
    list.push_front(10);

    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 1);

    list.clear();
}

TEST_F(SingleLinkedListTextFixture, PushFront_NonEmptyList)
{
    int curSize = list.getSize();
    list.push_front(5);
    curSize++;

    EXPECT_EQ(list.getHead()->value, 5);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST(SingleLinkedListTest, PushFront_MultipleElements)
{
    SingleLinkedList<int> list;
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

TEST(SingleLinkedListTest, PushBack_EmptyList)
{
    SingleLinkedList<int> list;

    list.push_back(10);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 1);
    list.clear();
}

TEST_F(SingleLinkedListTextFixture, PushBack_NonEmptyList)
{
    int curSize = list.getSize();
    list.push_back(40);
    curSize++;

    SingleLinkedList<int>::SingleNode *finalNode = list.getHead();

    while (finalNode->next != nullptr)
    {
        finalNode = finalNode->next;
    }

    EXPECT_EQ(finalNode->value, 40);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST(SingleLinkedListTest, PopFront_EmptyList)
{
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

TEST_F(SingleLinkedListTextFixture, PopFront_NonEmptyList_ManyElements)
{
    int curSize = list.getSize();
    SingleLinkedList<int>::SingleNode *secondNode = list.getHead()->next;
    list.pop_front();
    curSize--;

    EXPECT_EQ(list.getHead(), secondNode);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST(SingleLinkedListTest, PopBack_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;

    EXPECT_THROW(list.pop_back(), EmptyListException);
}

TEST(SingleLinkedListTest, PopBack_OneElement_EmptyList)
{
    SingleLinkedList<int> list;
    list.push_front(10);
    list.pop_back();
    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getSize(), 0);
}

TEST_F(SingleLinkedListTextFixture, PopBack_ManyElement_RemoveEndElement)
{
    int curSize = list.getSize();
    list.pop_back();
    curSize--;

    SingleLinkedList<int>::SingleNode *finalNode = list.getHead();
    EXPECT_EQ(curSize, list.getSize());
}

TEST(SingleLinkedListTest, Remove_OneElement_RemoveValidElement)
{
    SingleLinkedList<int> list;
    list.push_back(10);

    EXPECT_EQ(list.remove(10), true);
    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getSize(), 0);
}

TEST_F(SingleLinkedListTextFixture, Remove_ManyElement_RemoveValidElementAtFirst)
{
    bool result = list.remove(10);

    SingleLinkedList<int>::SingleNode *isLinked = list.getHead();
    while (isLinked != nullptr)
    {
        isLinked = isLinked->next;
    }

    EXPECT_EQ(result, true);
    EXPECT_EQ(isLinked, nullptr);
    EXPECT_EQ(list.getHead()->value, 20);
    EXPECT_EQ(list.getSize(), 6);
}

TEST_F(SingleLinkedListTextFixture, Remove_ManyElement_RemoveValidElementAtMid)
{
    bool result = list.remove(20);

    SingleLinkedList<int>::SingleNode *isLinked = list.getHead();
    while (isLinked != nullptr)
    {
        isLinked = isLinked->next;
    }

    EXPECT_EQ(result, true);
    EXPECT_EQ(isLinked, nullptr);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 6);
}

TEST_F(SingleLinkedListTextFixture, Remove_ManyElement_RemoveValidElementAtEnd)
{
    bool result = list.remove(30);

    SingleLinkedList<int>::SingleNode *isLinked = list.getHead();
    while (isLinked != nullptr)
    {
        isLinked = isLinked->next;
    }

    EXPECT_EQ(result, true);
    EXPECT_EQ(isLinked, nullptr);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 6);
}

TEST(SingleLinkedListTest, Remove_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;

    EXPECT_THROW(list.remove(5), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, Remove_ManyElement_RemoveInvalidElement)
{
    bool result = list.remove(15);

    SingleLinkedList<int>::SingleNode *isLinked = list.getHead();
    while (isLinked != nullptr)
    {
        isLinked = isLinked->next;
    }

    EXPECT_EQ(result, false);
    EXPECT_EQ(isLinked, nullptr);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), 7);
}

TEST(SingleLinkedListTest, Contains_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;

    EXPECT_THROW(list.contains(5), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, Contains_ManyElement_ValidValue)
{
    EXPECT_EQ(list.contains(20), true);
}

TEST_F(SingleLinkedListTextFixture, Contains_ManyElement_InvalidValue)
{
    EXPECT_EQ(list.contains(15), false);
}

TEST(SingleLinkedListTest, Find_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;

    EXPECT_THROW(list.find(5), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, Find_ManyElement_ValidValue)
{
    EXPECT_EQ(list.find(20)->value, 20);
}

TEST_F(SingleLinkedListTextFixture, Find_ManyElement_InvalidValue)
{
    EXPECT_EQ(list.find(25), nullptr);
}

TEST(SingleLinkedListTest, Front_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;

    EXPECT_THROW(list.front(), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, Front_ManyElement_ReturnFirstElement)
{
    EXPECT_EQ(list.front(), 10);
}

TEST(SingleLinkedListTest, Back_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;

    EXPECT_THROW(list.back(), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, Back_ManyElement_ReturnEndElement)
{
    EXPECT_EQ(list.back(), 30);
}

TEST_F(SingleLinkedListTextFixture, Clear_ManyElement_ClearAllElement)
{
    list.clear();

    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SingleLinkedListTest, GetSize_EmptyList_ReturnSize)
{
    SingleLinkedList<int> list;

    EXPECT_EQ(list.getSize(), 0);
}

TEST_F(SingleLinkedListTextFixture, GetSize_ManyElement_ReturnSize)
{
    EXPECT_EQ(list.getSize(), 7);
}

TEST(SingleLinkedListTest, IsEmpty_EmptyList_ReturnEmpty)
{
    SingleLinkedList<int> list;

    EXPECT_EQ(list.isEmpty(), true);
}

TEST_F(SingleLinkedListTextFixture, IsEmpty_ManyElement_IsNotEmpty)
{
    EXPECT_EQ(list.isEmpty(), false);
}

TEST(SingleLinkedListTest, At_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;

    EXPECT_THROW(list.at(0), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, At_NonEmptyList_InvalidIndex_ThrowException1)
{
    EXPECT_THROW(list.at(-1), IndexOutOfRangeException);
}

TEST_F(SingleLinkedListTextFixture, At_NonEmptyList_InvalidIndex_ThrowException2)
{
    EXPECT_THROW(list.at(list.getSize()), IndexOutOfRangeException);
}

TEST_F(SingleLinkedListTextFixture, At_NonEmptyList_ValidIndex_ReturnValue)
{
    EXPECT_EQ(list.at(1), 20);
}

TEST_F(SingleLinkedListTextFixture, IndexOf_NonEmptyList_ValidValue_ReturnIndex)
{
    EXPECT_EQ(list.indexOf(20), 1);
}

TEST_F(SingleLinkedListTextFixture, IndexOf_NonEmptyList_InvalidValue_ReturnNonIndex)
{
    EXPECT_EQ(list.indexOf(25), -1);
}

TEST(SingleLinkedListTest, IndexOf_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;

    EXPECT_THROW(list.indexOf(1), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, Insert_NonEmpty_InvalidIndex_ThrowException1)
{
    EXPECT_THROW(list.insert(-1, 40), IndexOutOfRangeException);
}

TEST_F(SingleLinkedListTextFixture, Insert_NonEmpty_InvalidIndex_ThrowException2)
{
    EXPECT_THROW(list.insert(list.getSize() + 1, 40), IndexOutOfRangeException);
}

TEST_F(SingleLinkedListTextFixture, Insert_NonEmpty_ValidIndex_FirstIndex)
{
    int curSize = list.getSize();
    list.insert(0, 40);
    curSize++;

    SingleLinkedList<int>::SingleNode *current = list.getHead();
    while (current != nullptr)
    {
        current = current->next;
    }

    EXPECT_EQ(current, nullptr);
    EXPECT_EQ(list.getHead()->value, 40);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST_F(SingleLinkedListTextFixture, Insert_NonEmpty_ValidIndex_FinalIndex)
{
    int curSize = list.getSize();
    list.insert(list.getSize(), 40);
    curSize++;

    SingleLinkedList<int>::SingleNode *current = list.getHead();
    while (current->next != nullptr)
    {
        current = current->next;
    }

    EXPECT_EQ(current->next, nullptr);
    EXPECT_EQ(current->value, 40);
    EXPECT_EQ(list.getHead()->value, 10);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST_F(SingleLinkedListTextFixture, Insert_NonEmpty_ValidIndex_RandomIndex)
{
    int curSize = list.getSize();
    list.insert(1, 40);
    curSize++;

    SingleLinkedList<int>::SingleNode *current = list.getHead();
    while (current != nullptr)
    {
        current = current->next;
    }

    EXPECT_EQ(current, nullptr);
    EXPECT_EQ(list.indexOf(40), 1);
    EXPECT_EQ(list.getSize(), curSize);
}

TEST_F(SingleLinkedListTextFixture, RemoveAt_NonEmpty_InValidIndex)
{
    EXPECT_THROW(list.removeAt(-1), IndexOutOfRangeException);
    EXPECT_THROW(list.removeAt(list.getSize()), IndexOutOfRangeException);
}

TEST(SingleLinkedListTest, RemoveAt_OneElement)
{
    SingleLinkedList<int> list;
    list.push_back(10);

    EXPECT_NO_THROW(list.removeAt(0));
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_EQ(list.getHead(), nullptr);
}

TEST_F(SingleLinkedListTextFixture, RemoveAt_NonEmpty_RemoveFirstIndex)
{
    SingleLinkedList<int>::SingleNode *secondNode = list.getHead()->next;

    EXPECT_NO_THROW(list.removeAt(0));
    EXPECT_EQ(list.getSize(), 6);
    EXPECT_EQ(list.getHead(), secondNode);
}

TEST_F(SingleLinkedListTextFixture, RemoveAt_NonEmpty_RemoveLastIndex)
{
    EXPECT_NO_THROW(list.removeAt(6));
    EXPECT_EQ(list.getSize(), 6);

    SingleLinkedList<int>::SingleNode *node = list.getHead();
    while (node != nullptr)
    {
        node = node->next;
    }
    EXPECT_EQ(node, nullptr);
}

TEST_F(SingleLinkedListTextFixture, RemoveAt_NonEmpty_RemoveMidIndex)
{
    EXPECT_NO_THROW(list.removeAt(1));
    EXPECT_EQ(list.getSize(), 6);

    SingleLinkedList<int>::SingleNode *node = list.getHead();
    while (node != nullptr)
    {
        node = node->next;
    }
    EXPECT_EQ(node, nullptr);
}

TEST(SingleLinkedListTest, Reverse_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;
    EXPECT_THROW(list.reverse(), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, Reverse_NonEmpty)
{
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

TEST(SingleLinkedListTest, Sort_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;
    EXPECT_THROW(list.sort(), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, Sort_NonEmptyList_Desc)
{
    EXPECT_NO_THROW(list.sort(true));

    EXPECT_EQ(list.getHead()->value, 60);
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

TEST_F(SingleLinkedListTextFixture, Sort_NonEmptyList_Incr)
{
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

TEST(SingleLinkedListTest, Unique_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;
    EXPECT_THROW(list.unique(), EmptyListException);
}

TEST(SingleLinkedListTest, Unique_NonEmptyList_UniqueElement)
{
    SingleLinkedList<int> list;

    list.push_front(10);
    list.push_front(10);
    list.push_front(20);
    list.push_front(20);
    list.push_front(30);

    EXPECT_NO_THROW(list.unique());
    EXPECT_EQ(list.getHead()->value, 30);
    EXPECT_EQ(list.getSize(), 3);
    std::vector<int> v = list.toVector();
    EXPECT_EQ(v[0], 30);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 10);
}

TEST(SingleLinkedListTest, Unique_NonEmptyList_KeepOne)
{
    SingleLinkedList<int> list;
    list.push_front(10);
    list.push_front(10);
    list.push_front(10);
    list.push_front(10);

    EXPECT_NO_THROW(list.unique());
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);
}

TEST(SingleLinkedListTest, ToVector_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;
    EXPECT_THROW(list.toVector(), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, ToVector_NonEmptyList_ConvertToVector)
{
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

TEST_F(SingleLinkedListTextFixture, Merge_NonEmpty_MergeTwoLinkedList)
{
    SingleLinkedList<int> list2;
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

TEST_F(SingleLinkedListTextFixture, Print_NonEmpty)
{
    EXPECT_NO_THROW(list.print());
}

TEST_F(SingleLinkedListTextFixture, CopyFrom_NonEmpty_CopyFromEmpty_ThrowException)
{
    SingleLinkedList<int> list2;
    EXPECT_THROW(list.copyFrom(list2), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, CopyFrom_NonEmpty_CopyFromOtherLinkedList1)
{
    SingleLinkedList<int> list2;
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

TEST_F(SingleLinkedListTextFixture, CopyFrom_NonEmpty_CopyFromOtherLinkedList2)
{
    SingleLinkedList<int> list2;
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

TEST_F(SingleLinkedListTextFixture, CopyFrom_NonEmpty_CopyFromOtherLinkedList3)
{
    SingleLinkedList<int> list2;
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

TEST(SingleLinkedListTest, CopyFrom_NonEmpty_CopyFromOtherLinkedList4)
{
    SingleLinkedList<int> list;
    SingleLinkedList<int> list2;
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

TEST(SingleLinkedListTest, Clone_EmptyList_ThrowException)
{
    SingleLinkedList<int> list;
    EXPECT_THROW(list.clone(), EmptyListException);
}

TEST_F(SingleLinkedListTextFixture, Clone_NonEmpty_CloneList)
{
    // LinkedList<int> *clone = new SingleLinkedList<int>();
    SingleLinkedList<int> *clone;
    clone = list.clone();
    EXPECT_NE(clone->getHead(), list.getHead());
    EXPECT_EQ(clone->getSize(), list.getSize());
}

TEST_F(SingleLinkedListTextFixture, Equals_CompareEqual)
{
    SingleLinkedList<int> list2;
    list2.push_back(10);
    list2.push_back(20);
    list2.push_back(60);
    list2.push_back(20);
    list2.push_back(40);
    list2.push_back(40);
    list2.push_back(30);

    EXPECT_EQ(list.equals(list2), true);
}

TEST_F(SingleLinkedListTextFixture, Equals_CompareNotEqual)
{
    SingleLinkedList<int> list2;
    list2.push_back(10);
    list2.push_back(20);
    list2.push_back(60);
    list2.push_back(20);
    list2.push_back(40);
    list2.push_back(40);
    list2.push_back(35);

    EXPECT_EQ(list.equals(list2), false);
}

TEST_F(SingleLinkedListTextFixture, Swap_SwapTwoLinkedList)
{
    SingleLinkedList<int> list2;
    list2.push_back(5);
    list2.push_back(15);

    SingleLinkedList<int>::SingleNode *node = list.getHead();
    SingleLinkedList<int>::SingleNode *node2 = list2.getHead();
    int size = list.getSize();
    int size2 = list2.getSize();

    list.swap(list2);
    EXPECT_EQ(list.getHead(), node2);
    EXPECT_EQ(list2.getHead(), node);
    EXPECT_EQ(list.getSize(), size2);
    EXPECT_EQ(list2.getSize(), size);
}

TEST_F(SingleLinkedListTextFixture, Mid_GetMidElement)
{
    int midValue = list.at(list.getSize() / 2);

    EXPECT_EQ(list.mid(), midValue);
}

TEST_F(SingleLinkedListTextFixture, GetHead_ReturnHead)
{
    EXPECT_NO_THROW(list.getHead());
}

TEST(SingleLinkedListTest, GetHead_EmptyList)
{
    SingleLinkedList<int> list;
    EXPECT_EQ(list.getHead(), nullptr);
}

TEST(SingleLinkedListTest, GetTail_EmptyList)
{
    SingleLinkedList<int> list;
    EXPECT_EQ(list.getTail(), nullptr);
}

TEST_F(SingleLinkedListTextFixture, GetTail_ReturnTail)
{

    SingleLinkedList<int>::SingleNode *node = list.getHead();
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