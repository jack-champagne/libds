#include <gtest/gtest.h>

extern "C" {
#include "vec.h"
}

#define MAX_LEN 1024

TEST(LLTests, InitAsserts) {
  LinkedList* new_list = linked_list();
  EXPECT_NE(new_list, (void*) NULL)
      << "LinkedList returns null pointer";
  EXPECT_EQ(ll_size(new_list), 0)
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
  EXPECT_EQ(ll_size(new_list), 0);
  int a = 40001;
  int b = 40010;
  ll_append(new_list, &a);
  EXPECT_EQ(ll_size(new_list), 1);
  ll_append(new_list, &b);
  EXPECT_EQ(ll_size(new_list), 2);
  ll_prepend(new_list, &b);
  EXPECT_EQ(ll_size(new_list), 3);
  ll_insert_at(new_list, 3, &b);
  EXPECT_EQ(ll_size(new_list), 4);
  ll_remove(new_list, 2);
  EXPECT_EQ(ll_size(new_list), 3);
  ll_remove(new_list, 0);
  EXPECT_EQ(ll_size(new_list), 2);
  ll_remove(new_list, 1);
  EXPECT_EQ(ll_size(new_list), 1);
  ll_remove(new_list, 1);
  EXPECT_EQ(ll_size(new_list), 1);
  ll_remove(new_list, 0);
  EXPECT_EQ(ll_size(new_list), 0);
  ll_destroy(new_list);
}

TEST(LLTests, AppendRuntime) {
  int num = 10000000;
  LinkedList* new_list = linked_list();
  for (int i = 0; i < num; i++) {
    ll_append(new_list, &i);
  }

  ll_destroy(new_list);
}

TEST(LLTests, PrependAppendOrdering) {
  char* my_strs[5];

  my_strs[0] = (char*) malloc(sizeof(char) * 50);
  strcpy(my_strs[0], "This is the first piece of data.\n");
  my_strs[1] = (char*) malloc(sizeof(char) * 50);
  strcpy(my_strs[1], "This is the second piece of data.\n");
  my_strs[2] = (char*) malloc(sizeof(char) * 50);
  strcpy(my_strs[2], "This is the third piece of data.\n");
  my_strs[3] = (char*) malloc(sizeof(char) * 50);
  strcpy(my_strs[3], "This is the fourth piece of data.\n");
  my_strs[4] = (char*) malloc(sizeof(char) * 50);
  strcpy(my_strs[4], "This is the fifth piece of data.\n");

  LinkedList* new_list = linked_list();
  ll_prepend(new_list, my_strs[2]);
  ll_append(new_list, my_strs[3]);
  ll_prepend(new_list, my_strs[1]);
  ll_append(new_list, my_strs[4]);
  ll_prepend(new_list, my_strs[0]);

  // Test seperately
  Iterator* my_iter = ll_iterator(new_list);
  int i = 0;
  char* my_data;
  while ((my_data = (char*) iter_next(my_iter)) != NULL) {
    EXPECT_EQ(my_strs[i], my_data);
    i++;
  }

}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
