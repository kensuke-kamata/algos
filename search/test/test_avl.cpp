#include <gtest/gtest.h>
#include <vector>
#include "avl.h"

class AVLTreeTest : public ::testing::Test {
 protected:
  avl::tree<int> tree;

  void SetUp() override {

  }

  void TearDown() override {

  }
};

TEST_F(AVLTreeTest, Root) {
  EXPECT_FALSE(tree.contains(0));
  tree.insert(0);
  EXPECT_TRUE(tree.contains(0));
  tree.clear();
  EXPECT_FALSE(tree.contains(0));
}

TEST_F(AVLTreeTest, LeftSkewed) {
  tree.clear();
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);

  EXPECT_EQ(tree.height(), 1);
  std::vector<int> expect = {1, 2, 3};
  std::vector<int> result = tree.inorder();
  EXPECT_EQ(expect, result);
}

TEST_F(AVLTreeTest, RightSkewed) {
  tree.clear();
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);

  EXPECT_EQ(tree.height(), 1);
  std::vector<int> expect = {1, 2, 3};
  std::vector<int> result = tree.inorder();
  EXPECT_EQ(expect, result);
}

TEST_F(AVLTreeTest, LeftRightSkewed) {
  tree.clear();
  tree.insert(3);
  tree.insert(1);
  tree.insert(2);

  EXPECT_EQ(tree.height(), 1);
  std::vector<int> expect = {1, 2, 3};
  std::vector<int> result = tree.inorder();
  EXPECT_EQ(expect, result);
}

TEST_F(AVLTreeTest, RightLeftSkewed) {
  tree.clear();
  tree.insert(1);
  tree.insert(3);
  tree.insert(2);

  EXPECT_EQ(tree.height(), 1);
  std::vector<int> expect = {1, 2, 3};
  std::vector<int> result = tree.inorder();
  EXPECT_EQ(expect, result);
}

TEST_F(AVLTreeTest, RemoveRoot) {
  tree.clear();
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);

  // Test removing node
  EXPECT_TRUE(tree.contains(3));
  tree.remove(3);
  EXPECT_FALSE(tree.contains(3));

  EXPECT_EQ(tree.height(), 1);
  std::vector<int> expect = {1, 2};
  std::vector<int> result = tree.inorder();
  EXPECT_EQ(expect, result);
}

TEST_F(AVLTreeTest, RemoveLeaf) {
  tree.clear();
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);

  // Test removing node
  EXPECT_TRUE(tree.contains(1));
  tree.remove(1);
  EXPECT_FALSE(tree.contains(1));

  EXPECT_EQ(tree.height(), 1);
  std::vector<int> expect = {2, 3};
  std::vector<int> result = tree.inorder();
  EXPECT_EQ(expect, result);
}

TEST_F(AVLTreeTest, RemoveMiddle) {
  tree.clear();
  tree.insert(3);
  tree.insert(2);
  tree.insert(1);

  // Test removing node
  EXPECT_TRUE(tree.contains(2));
  tree.remove(2);
  EXPECT_FALSE(tree.contains(2));

  EXPECT_EQ(tree.height(), 1);
  std::vector<int> expect = {1, 3};
  std::vector<int> result = tree.inorder();
  EXPECT_EQ(expect, result);
}
