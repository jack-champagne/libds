#include <gtest/gtest.h>

extern "C" {
#include "vec.h"
}

#define MAX_LEN 1024

TEST(LLTests, InitAsserts) {
  LinkedList* new_list = linked_list();
  EXPECT_NE(new_list, (void*) NULL)
      << "LinkedList returns null pointer";
  EXPECT_EQ(new_list->size, 0)
      << "new_list has non-zero size on init.";
  EXPECT_EQ(ll_is_empty(new_list), 1)
      << "ll_is_empty is not returning true for empty list";
  EXPECT_EQ(ll_get(new_list, 0), (void*) NULL) 
      << "Get at index 0 not returning null on empty list";
  EXPECT_EQ(ll_remove(new_list, 0), (void*) NULL) 
      << "Remove at index 0 not returning null element";
}

TEST(LLTests, SizeChanges) {
  LinkedList* new_list = linked_list();
  EXPECT_EQ(new_list->size, 0);
  int a = 40001;
  ll_append(new_list, &a);
  EXPECT_EQ(new_list->size, 1);
  ll_append(new_list, &(new_list->size));
  EXPECT_EQ(new_list->size, 2);
  ll_prepend(new_list, &(new_list->size));
  EXPECT_EQ(new_list->size, 3);
  ll_insert_at(new_list, 3, &(new_list->size));
  EXPECT_EQ(new_list->size, 4);
  ll_remove(new_list, 2);
  EXPECT_EQ(new_list->size, 3);
  ll_remove(new_list, 0);
  EXPECT_EQ(new_list->size, 2);
  ll_remove(new_list, 1);
  EXPECT_EQ(new_list->size, 1);
  ll_remove(new_list, 1);
  EXPECT_EQ(new_list->size, 1);
  ll_remove(new_list, 0);
  EXPECT_EQ(new_list->size, 0);
  ll_destroy(new_list);
}

TEST(LLTests, AppendRuntime) {
  int num = 100;
  LinkedList* new_list = linked_list();
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      ll_append(new_list, &j);
    }
  }

  ll_destroy(new_list);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
