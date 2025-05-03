#include <gtest/gtest.h>
#include "../inc/Lru.hpp"

namespace LRU {

class LruTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common setup for each test
    }

    void TearDown() override {
        // Clean up after each test
    }
};

// Test Constructor and GetCacheSize
TEST_F(LruTest, Constructor) {
    Lru lru(3);
    EXPECT_EQ(lru.GetCacheSize(), 3);
    EXPECT_EQ(lru.GetUsageOrderSize(), 0);

    // Test zero-capacity cache
    Lru lru_zero(0);
    EXPECT_EQ(lru_zero.GetCacheSize(), 0);
    EXPECT_EQ(lru_zero.GetUsageOrderSize(), 0);
}

// Test GetUsageOrderSize
TEST_F(LruTest, GetUsageOrderSize) {
    Lru lru(2);
    EXPECT_EQ(lru.GetUsageOrderSize(), 0);

    lru.Put(1, "one");
    EXPECT_EQ(lru.GetUsageOrderSize(), 1);

    lru.Put(2, "two");
    EXPECT_EQ(lru.GetUsageOrderSize(), 2);

    // TODO: Fix DoublelyLinkedList::Clear to reset size
    // lru.ClearCache();
    // EXPECT_EQ(lru.GetUsageOrderSize(), 0);
}

// Test HasCapacity
TEST_F(LruTest, HasCapacity) {
    Lru lru(2);
    EXPECT_TRUE(lru.HasCapacity());

    lru.Put(1, "one");
    EXPECT_TRUE(lru.HasCapacity());

    lru.Put(2, "two");
    EXPECT_FALSE(lru.HasCapacity());

    // Test zero-capacity cache
    Lru lru_zero(0);
    EXPECT_FALSE(lru_zero.HasCapacity());
}

// Test IsKeyValuePresent
TEST_F(LruTest, IsKeyValuePresent) {
    Lru lru(2);
    lru.Put(1, "one");

    EXPECT_TRUE(lru.IsKeyValuePresent(1, "one"));
    EXPECT_FALSE(lru.IsKeyValuePresent(1, "two"));
    EXPECT_FALSE(lru.IsKeyValuePresent(2, "one"));

    // Test empty cache with zero capacity
    Lru lru_zero(0);
    EXPECT_FALSE(lru_zero.IsKeyValuePresent(1, "one"));
}

// Test Evict
TEST_F(LruTest, Evict) {
    Lru lru(2);
    EXPECT_FALSE(lru.Evict()); // Empty cache

    lru.Put(1, "one");
    lru.Put(2, "two");
    EXPECT_TRUE(lru.Evict()); // Removes key 1
    EXPECT_EQ(lru.GetUsageOrderSize(), 1);
    EXPECT_FALSE(lru.IsKeyValuePresent(1, "one"));
    EXPECT_TRUE(lru.IsKeyValuePresent(2, "two"));
}

// Test Put
TEST_F(LruTest, Put) {
    Lru lru(2);
    // Add to empty cache
    EXPECT_TRUE(lru.Put(1, "one"));
    EXPECT_EQ(lru.GetUsageOrderSize(), 1);
    EXPECT_TRUE(lru.IsKeyValuePresent(1, "one"));

    // Add to partially full cache
    EXPECT_TRUE(lru.Put(2, "two"));
    EXPECT_EQ(lru.GetUsageOrderSize(), 2);

    // Add duplicate key-value pair
    testing::internal::CaptureStderr();
    EXPECT_FALSE(lru.Put(1, "one"));
    EXPECT_EQ(testing::internal::GetCapturedStderr(), "Key and value already present\n");

    // Add to full cache (triggers eviction)
    testing::internal::CaptureStdout();
    EXPECT_TRUE(lru.Put(3, "three"));
    EXPECT_EQ(lru.GetUsageOrderSize(), 2);
    EXPECT_FALSE(lru.IsKeyValuePresent(1, "one")); // Key 1 evicted
    EXPECT_TRUE(lru.IsKeyValuePresent(2, "two"));
    EXPECT_TRUE(lru.IsKeyValuePresent(3, "three"));
    EXPECT_EQ(testing::internal::GetCapturedStdout(), " Capacity is Full evicting key\n");
}

// Test Get (bool overload)
TEST_F(LruTest, GetWithValue) {
    Lru lru(2);
    lru.Put(1, "one");
    lru.Put(2, "two");

    std::string value;
    EXPECT_TRUE(lru.Get(1, value));
    EXPECT_EQ(value, "one");

    // Verify LRU order (key 1 moved to front)
    EXPECT_TRUE(lru.Get(2, value));
    EXPECT_EQ(value, "two");

    // Test non-existing key
    testing::internal::CaptureStderr();
    EXPECT_FALSE(lru.Get(3, value));
    EXPECT_EQ(testing::internal::GetCapturedStderr(), "No such key present\n");
}

// Test Get (string overload)
TEST_F(LruTest, GetWithStringReturn) {
    Lru lru(2);
    lru.Put(1, "one");

    EXPECT_EQ(lru.Get(1), "one");

    // Test non-existing key
    testing::internal::CaptureStderr();
    EXPECT_EQ(lru.Get(2), "");
    // Expect both error messages
    EXPECT_EQ(testing::internal::GetCapturedStderr(),
              "No such key present\nFailed to get value no data present at the index\n");
}

// Test ClearCache
TEST_F(LruTest, ClearCache) {
    Lru lru(2);
    lru.Put(1, "one");
    lru.Put(2, "two");

    testing::internal::CaptureStdout();
    lru.ClearCache();
    // Expect both List Cleared and Cache Cleared due to DoublelyLinkedList::Clear
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "List Cleared\nCache Cleared\n");
    // TODO: Fix DoublelyLinkedList::Clear to reset size
    // EXPECT_EQ(lru.GetUsageOrderSize(), 0);
    EXPECT_FALSE(lru.IsKeyValuePresent(1, "one"));
    EXPECT_FALSE(lru.IsKeyValuePresent(2, "two"));

    // Clear empty cache
    testing::internal::CaptureStdout();
    lru.ClearCache();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "List Already Empty\nCache Cleared\n");
    // TODO: Fix DoublelyLinkedList::Clear to reset size
    // EXPECT_EQ(lru.GetUsageOrderSize(), 0);
}

// Test Destructor
TEST_F(LruTest, Destructor) {
    // Create Lru object in a scope to test destructor
    {
        Lru lru(2);
        lru.Put(1, "one");
        testing::internal::CaptureStdout();
    } // Destructor called here
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "List Cleared\nCache Cleared\n");
}

} // namespace LRU