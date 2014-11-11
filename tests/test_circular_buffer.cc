#include <gtest/gtest.h>

#include "circular_buffer.h"

class TestCircularBuffer : public ::testing::Test {
public:
    circular_buffer<std::int16_t, 3> cb;
};

TEST_F(TestCircularBuffer, EmptyOnConstruct) {
    EXPECT_TRUE(cb.empty());
    EXPECT_FALSE(cb.full());
}

TEST_F(TestCircularBuffer, PushBack)
{
    cb.push_back(16);
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(1, cb.size());

    std::int16_t x = cb.front();
    EXPECT_EQ(16, x);
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(1, cb.size());

    x = cb.back();
    EXPECT_EQ(16, x);
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(1, cb.size());
}

TEST_F(TestCircularBuffer, PushFront)
{
    cb.push_front(16);
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(1, cb.size());

    std::int16_t x = cb.front();
    EXPECT_EQ(16, x);
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(1, cb.size());

    x = cb.back();
    EXPECT_EQ(16, x);
    EXPECT_FALSE(cb.empty());
    EXPECT_FALSE(cb.full());
    EXPECT_EQ(1, cb.size());
}


TEST_F(TestCircularBuffer, MultiplePushBack)
{
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    ASSERT_EQ(1, cb[0]);
    ASSERT_EQ(2, cb[1]);
    ASSERT_EQ(3, cb[2]);
    cb.push_back(4);
    cb.push_back(5);
    cb.push_back(6);
    ASSERT_EQ(4, cb[0]);
    ASSERT_EQ(5, cb[1]);
    ASSERT_EQ(6, cb[2]);
}

TEST_F(TestCircularBuffer, MultiplePushBackPopBack)
{
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.pop_back();
    cb.pop_back();
    cb.pop_back();
    ASSERT_TRUE(cb.empty());
    ASSERT_FALSE(cb.full());
    ASSERT_EQ(0, cb.size());
}

TEST_F(TestCircularBuffer, PushBackReadBack)
{
    cb.push_back(0);
    ASSERT_EQ(0, cb.back());
    cb.push_back(1);
    ASSERT_EQ(1, cb.back());
    cb.push_back(2);
    ASSERT_EQ(2, cb.back());
    cb.push_back(3);
    ASSERT_EQ(3, cb.back());
}

TEST_F(TestCircularBuffer, PushFrontReadFront)
{
    cb.push_front(0);
    ASSERT_EQ(0, cb.front());
    cb.push_front(1);
    ASSERT_EQ(1, cb.front());
    cb.push_front(2);
    ASSERT_EQ(2, cb.front());
    cb.push_front(3);
    ASSERT_EQ(3, cb.front());
}

TEST_F(TestCircularBuffer, PushBackReadFront)
{
    cb.push_back(0);
    ASSERT_EQ(0, cb.front());
    cb.push_back(1);
    ASSERT_EQ(0, cb.front());
    cb.push_back(2);
    ASSERT_EQ(0, cb.front());
    cb.push_back(3);
    ASSERT_EQ(1, cb.front());
}

TEST_F(TestCircularBuffer, PushFrontReadBack)
{
    cb.push_front(0);
    ASSERT_EQ(0, cb.back());
    cb.push_front(1);
    ASSERT_EQ(0, cb.back());
    cb.push_front(2);
    ASSERT_EQ(0, cb.back());
    cb.push_front(3);
    ASSERT_EQ(1, cb.back());
}

TEST_F(TestCircularBuffer, IteratorTest)
{
    std::int16_t i = 0;
    cb.push_back(0);
    cb.push_back(1);
    cb.push_back(2);
    for (auto it = cb.begin(); it != cb.end(); ++it) {
        ASSERT_EQ(cb[i++], *it);
    }
    ASSERT_EQ(3, i);

    cb.push_back(3);
    cb.push_back(4);
    cb.push_back(5);
    i = 0;
    for (auto it = cb.begin(); it != cb.end(); ++it) {
        ASSERT_EQ(cb[i++], *it);
    }
    ASSERT_EQ(3, i);

    i = 0;
    for (auto elem: cb) {
        ASSERT_EQ(cb[i++], elem);
    }
    ASSERT_EQ(3, i);
}
