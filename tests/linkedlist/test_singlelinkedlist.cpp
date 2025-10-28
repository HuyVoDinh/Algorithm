#include <gtest/gtest.h>
#include "linkedlist/singlelinkedlist.h"

TEST(SingleLinkedListTest, PushBackAndToVector) {
    SingleLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    ASSERT_EQ(list.getSize(), 3);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}