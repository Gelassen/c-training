#include <gtest/gtest.h>
#include "CustomStack.h"

// Test fixture for CustomStack
class CustomStackTest : public ::testing::Test {
protected:
    CustomStack<int> stack;
};

// Test push() and size()
TEST_F(CustomStackTest, PushIncreasesSize) {
    stack.push(10);
    stack.push(20);
    EXPECT_EQ(stack.size(), 2);
}

// Test pop() functionality
TEST_F(CustomStackTest, PopReturnsLastElement) {
    stack.push(42);
    int value = stack.pop();
    EXPECT_EQ(value, 42);
    EXPECT_EQ(stack.size(), 0);
}

// Test isEmpty() method
TEST_F(CustomStackTest, IsEmptyWorks) {
    EXPECT_TRUE(stack.isEmpty());
    stack.push(99);
    EXPECT_FALSE(stack.isEmpty());
}

// Test peek() without modifying the stack
TEST_F(CustomStackTest, PeekReturnsTopWithoutRemoving) {
    stack.push(77);
    EXPECT_EQ(stack.peek(), 77);
    EXPECT_EQ(stack.size(), 1);
}

// Test popping from an empty stack
TEST_F(CustomStackTest, PopThrowsExceptionWhenEmpty) {
    EXPECT_THROW(stack.pop(), std::out_of_range);
}

// Test peeking from an empty stack
TEST_F(CustomStackTest, PeekThrowsExceptionWhenEmpty) {
    EXPECT_THROW(stack.peek(), std::out_of_range);
}
