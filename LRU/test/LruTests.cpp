#include "../inc/Lru.hpp"
#include <gtest/gtest.h>
using namespace LRU;


class LruTest : public ::testing::Test
{};
    
TEST_F(LruTest, Constructor)
{
    LRU::Lru lruCache(5);
    ASSERT_EQ(lruCache.GetCacheSize(), 5);
}
TEST_F(LruTest, EvictNonEmptyCache)
{
    LRU::Lru lruCache(2);
    lruCache.Put(1, "one");
    lruCache.Put(2, "two");
    ASSERT_TRUE(lruCache.Evict());
    ASSERT_EQ(lruCache.GetUsageOrderSize(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}