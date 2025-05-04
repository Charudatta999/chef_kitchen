#include <gtest/gtest.h>
#include "../inc/DoublelyLinkedList.hpp"

namespace LinkedList {

class DoublelyLinkedListTest : public ::testing::Test {
protected:
    DoublelyLinkedList list;

    // Helper function to verify list integrity
    void VerifyList() {
        // Check size matches actual node count
        size_t count = 0;
        DoubleLL* current = list.GetHead();
        while (current) {
            ++count;
            current = current->next_;
        }
        EXPECT_EQ(list.GetSize(), count);

        // Verify head and tail pointers
        if (list.GetSize() == 0) {
            EXPECT_EQ(list.GetHead(), nullptr);
            EXPECT_EQ(list.GetTail(), nullptr);
        } else {
            EXPECT_NE(list.GetHead(), nullptr);
            EXPECT_NE(list.GetTail(), nullptr);
            EXPECT_EQ(list.GetHead()->prev_, nullptr);
            EXPECT_EQ(list.GetTail()->next_, nullptr);
        }

        // Verify prev/next pointers
        current = list.GetHead();
        while (current && current->next_) {
            EXPECT_EQ(current->next_->prev_, current);
            current = current->next_;
        }
        current = list.GetTail();
        while (current && current->prev_) {
            EXPECT_EQ(current->prev_->next_, current);
            current = current->prev_;
        }
    }

    // Helper to verify node content
    void VerifyNode(DoubleLL* node, int key, const std::string& val) {
        ASSERT_NE(node, nullptr);
        EXPECT_EQ(node->key_, key);
        EXPECT_EQ(node->val_, val);
    }

    // Helper to check list nodes in order
    void VerifyListContent(const std::vector<std::pair<int, std::string>>& expected) {
        DoubleLL* current = list.GetHead();
        for (const auto& [key, val] : expected) {
            ASSERT_NE(current, nullptr);
            VerifyNode(current, key, val);
            current = current->next_;
        }
        EXPECT_EQ(current, nullptr); // Ensure no extra nodes
    }
};

// Test constructor
TEST_F(DoublelyLinkedListTest, Constructor) {
    EXPECT_EQ(list.GetSize(), 0);
    EXPECT_EQ(list.GetHead(), nullptr);
    EXPECT_EQ(list.GetTail(), nullptr);
    VerifyList();
}

// Test AddNode (append)
TEST_F(DoublelyLinkedListTest, AddNode) {
    // Empty list
    EXPECT_TRUE(list.AddNode(1, "one"));
    EXPECT_EQ(list.GetSize(), 1);
    VerifyNode(list.GetHead(), 1, "one");
    VerifyNode(list.GetTail(), 1, "one");
    VerifyList();

    // Add to non-empty list
    EXPECT_TRUE(list.AddNode(2, "two"));
    EXPECT_EQ(list.GetSize(), 2);
    VerifyNode(list.GetHead(), 1, "one");
    VerifyNode(list.GetTail(), 2, "two");
    VerifyListContent({{1, "one"}, {2, "two"}});
    VerifyList();
}

// Test AddNodeFront
TEST_F(DoublelyLinkedListTest, AddNodeFront) {
    // Empty list
    EXPECT_TRUE(list.AddNodeFront(1, "one"));
    EXPECT_EQ(list.GetSize(), 1);
    VerifyNode(list.GetHead(), 1, "one");
    VerifyNode(list.GetTail(), 1, "one");
    VerifyList();

    // Non-empty list
    EXPECT_TRUE(list.AddNodeFront(2, "two"));
    EXPECT_EQ(list.GetSize(), 2);
    VerifyNode(list.GetHead(), 2, "two");
    VerifyNode(list.GetTail(), 1, "one");
    VerifyListContent({{2, "two"}, {1, "one"}});
    VerifyList();
}

// Test AddNode at position
TEST_F(DoublelyLinkedListTest, AddNodeAtPosition) {
    // Invalid positions
    EXPECT_FALSE(list.AddNode(1, "one", -1));
    EXPECT_FALSE(list.AddNode(1, "one", 1));
    EXPECT_EQ(list.GetSize(), 0);

    // Position 0 (front)
    EXPECT_TRUE(list.AddNode(1, "one", 0));
    EXPECT_EQ(list.GetSize(), 1);
    VerifyNode(list.GetHead(), 1, "one");
    VerifyNode(list.GetTail(), 1, "one");
    VerifyList();

    // Position 1 (end)
    EXPECT_TRUE(list.AddNode(2, "two", 1));
    EXPECT_EQ(list.GetSize(), 2);
    VerifyListContent({{1, "one"}, {2, "two"}});
    VerifyList();

    // Position 1 (middle)
    EXPECT_TRUE(list.AddNode(3, "three", 1));
    EXPECT_EQ(list.GetSize(), 3);
    VerifyListContent({{1, "one"}, {3, "three"}, {2, "two"}});
    VerifyList();

    // Position 3 (end)
    EXPECT_TRUE(list.AddNode(4, "four", 3));
    EXPECT_EQ(list.GetSize(), 4);
    VerifyListContent({{1, "one"}, {3, "three"}, {2, "two"}, {4, "four"}});
    VerifyList();
}

// Test GetNode by value
TEST_F(DoublelyLinkedListTest, GetNodeByValue) {
    // Empty list
    EXPECT_EQ(list.GetNode("one"), nullptr);

    // Single node
    list.AddNode(1, "one");
    DoubleLL* node = list.GetNode("one");
    VerifyNode(node, 1, "one");
    EXPECT_EQ(list.GetNode("two"), nullptr);

    // Multiple nodes
    list.AddNode(2, "two");
    list.AddNode(3, "three");
    VerifyNode(list.GetNode("one"), 1, "one");
    VerifyNode(list.GetNode("two"), 2, "two");
    VerifyNode(list.GetNode("three"), 3, "three");
    EXPECT_EQ(list.GetNode("four"), nullptr);
    VerifyList();
}

// Test GetNode by key
TEST_F(DoublelyLinkedListTest, GetNodeByKey) {
    // Empty list
    EXPECT_EQ(list.GetNode(1), nullptr);

    // Single node
    list.AddNode(1, "one");
    DoubleLL* node = list.GetNode(1);
    VerifyNode(node, 1, "one");
    EXPECT_EQ(list.GetNode(2), nullptr);

    // Multiple nodes
    list.AddNode(2, "two");
    list.AddNode(3, "three");
    VerifyNode(list.GetNode(1), 1, "one");
    VerifyNode(list.GetNode(2), 2, "two");
    VerifyNode(list.GetNode(3), 3, "three");
    EXPECT_EQ(list.GetNode(4), nullptr);
    VerifyList();
}

// Test MoveNodeFront
TEST_F(DoublelyLinkedListTest, MoveNodeFront) {
    list.AddNode(1, "one");
    list.AddNode(2, "two");
    list.AddNode(3, "three");

    // Move head (no-op)
    DoubleLL* node = list.GetNode(1);
    EXPECT_TRUE(list.MoveNodeFront(node));
    VerifyListContent({{1, "one"}, {2, "two"}, {3, "three"}});
    VerifyList();

    // Move tail
    node = list.GetNode(3);
    EXPECT_TRUE(list.MoveNodeFront(node));
    VerifyListContent({{3, "three"}, {1, "one"}, {2, "two"}});
    VerifyList();

    // Move middle
    node = list.GetNode(1);
    EXPECT_TRUE(list.MoveNodeFront(node));
    VerifyListContent({{1, "one"}, {3, "three"}, {2, "two"}});
    VerifyList();
}

// Test RemoveNode by pointer
TEST_F(DoublelyLinkedListTest, RemoveNodeByPointer) {
    list.AddNode(1, "one");
    list.AddNode(2, "two");
    list.AddNode(3, "three");

    // Remove head
    DoubleLL* node = list.GetNode(1);
    EXPECT_TRUE(list.RemoveNode(node));
    EXPECT_EQ(list.GetSize(), 2);
    VerifyListContent({{2, "two"}, {3, "three"}});
    VerifyList();

    // Remove tail
    node = list.GetNode(3);
    EXPECT_TRUE(list.RemoveNode(node));
    EXPECT_EQ(list.GetSize(), 1);
    VerifyListContent({{2, "two"}});
    VerifyList();

    // Remove last node
    node = list.GetNode(2);
    EXPECT_TRUE(list.RemoveNode(node));
    EXPECT_EQ(list.GetSize(), 0);
    EXPECT_EQ(list.GetHead(), nullptr);
    EXPECT_EQ(list.GetTail(), nullptr);
    VerifyList();
}

// Test RemoveNode by key
TEST_F(DoublelyLinkedListTest, RemoveNodeByKey) {
    list.AddNode(1, "one");
    list.AddNode(2, "two");
    list.AddNode(3, "three");

    // Remove non-existent key
    EXPECT_FALSE(list.RemoveNode(4));
    EXPECT_EQ(list.GetSize(), 3);

    // Remove middle
    EXPECT_TRUE(list.RemoveNode(2));
    EXPECT_EQ(list.GetSize(), 2);
    VerifyListContent({{1, "one"}, {3, "three"}});
    VerifyList();

    // Remove head
    EXPECT_TRUE(list.RemoveNode(1));
    EXPECT_EQ(list.GetSize(), 1);
    VerifyListContent({{3, "three"}});
    VerifyList();

    // Remove last
    EXPECT_TRUE(list.RemoveNode(3));
    EXPECT_EQ(list.GetSize(), 0);
    VerifyList();
}

// Test SwapNodes
TEST_F(DoublelyLinkedListTest, SwapNodes) {
    list.AddNode(1, "one");
    list.AddNode(2, "two");
    list.AddNode(3, "three");
    list.AddNode(4, "four");

    // Swap same node
    DoubleLL* node1 = list.GetNode(1);
    EXPECT_TRUE(list.SwapNodes(node1, node1));
    VerifyListContent({{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}});
    VerifyList();

    // Swap adjacent (head and next)
    DoubleLL* node2 = list.GetNode(2);
    EXPECT_TRUE(list.SwapNodes(node1, node2));
    VerifyListContent({{2, "two"}, {1, "one"}, {3, "three"}, {4, "four"}});
    VerifyList();

    // Swap adjacent (reverse order)
    node1 = list.GetNode(1);
    node2 = list.GetNode(3);
    EXPECT_TRUE(list.SwapNodes(node1, node2));
    VerifyListContent({{2, "two"}, {3, "three"}, {1, "one"}, {4, "four"}});
    VerifyList();

    // Swap non-adjacent
    node1 = list.GetNode(2);
    node2 = list.GetNode(4);
    EXPECT_TRUE(list.SwapNodes(node1, node2));
    VerifyListContent({{4, "four"}, {3, "three"}, {1, "one"}, {2, "two"}});
    VerifyList();

    // Swap head and tail
    node1 = list.GetNode(4);
    node2 = list.GetNode(2);
    EXPECT_TRUE(list.SwapNodes(node1, node2));
    VerifyListContent({{2, "two"}, {3, "three"}, {1, "one"}, {4, "four"}});
    VerifyList();
}

// Test destructor
TEST_F(DoublelyLinkedListTest, Destructor) {
    DoublelyLinkedList* tempList = new DoublelyLinkedList();
    tempList->AddNode(1, "one");
    tempList->AddNode(2, "two");
    delete tempList; // Should not crash, memory freed
}

} // namespace LinkedList