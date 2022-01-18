#include <gtest/gtest.h>

extern "C" {
#include "vec.h"
#include "queue.h"
#include "stack.h"
#include "cdvec.h"
}

#define MAX_LEN 1024

#define O1BATCHSIZE 100000

TEST(LLTests, InitAsserts) {
  LinkedList* new_list = linkedlist();
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
  ll_destroy(new_list);
}

TEST(LLTests, SizeChanges) {
  LinkedList* new_list = linkedlist();
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
  int num = O1BATCHSIZE;
  LinkedList* new_list = linkedlist();
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

  LinkedList* new_list = linkedlist();
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
  iter_destroy(my_iter);
  ll_destroy(new_list);

  for (i = 0; i < 5; i++) {
    free(my_strs[i]);
  }
}

TEST(LLTests, AppendTime_VS) {
  LinkedList* new_list = linkedlist();
  int* mints[O1BATCHSIZE];
  for (int i = 0; i < O1BATCHSIZE; i++) {
    mints[i] = (int*) malloc(sizeof(int));
    *mints[i] = i;
  }

  for (int i = 0; i < O1BATCHSIZE; i++) {
    ll_append(new_list, mints[i]);
  }

  for (int i = 0; i < O1BATCHSIZE; i++) {
    free(mints[i]);
  }
  ll_destroy(new_list);
}

TEST(LLTests, PrependTime_VS) {
  LinkedList* new_list = linkedlist();
  int* mints[O1BATCHSIZE];
  for (int i = 0; i < O1BATCHSIZE; i++) {
    mints[i] = (int*) malloc(sizeof(int));
    *mints[i] = i;
  }

  for (int i = 0; i < O1BATCHSIZE; i++) {
    ll_prepend(new_list, mints[i]);
  }

  for (int i = 0; i < O1BATCHSIZE; i++) {
    free(mints[i]);
  }
  ll_destroy(new_list);
}

TEST(QueueTests, InitQueue) {
  Queue* new_queue = queue();
  EXPECT_EQ(q_size(new_queue), 0);
  EXPECT_EQ(q_dequeue(new_queue),(void*) 0);

  q_destroy(new_queue);
}

TEST(QueueTests, De_En_QueueSpeed_Size) {
  Queue* new_queue = queue();
  int i;
  for (i = 0; i < 1000000; i++) {
    q_enqueue(new_queue, &i);
    EXPECT_EQ(q_size(new_queue), i + 1);
  }

  q_destroy(new_queue);
}

TEST(QueueTests, QueueIterator) {
  Queue* new_queue = queue();
  int i;
  for (i = 0; i < O1BATCHSIZE; i++) {
    q_enqueue(new_queue, &i);
  }

  Iterator* iter = q_iterator(new_queue);
  int* data;
  while ((data = (int*) iter_next(iter)) != NULL) {
    EXPECT_EQ(*data, O1BATCHSIZE);
  }
  iter_destroy(iter);
  q_destroy(new_queue);
}

TEST(StackTests, InitStack) {
  Stack* new_stack = stack();
  EXPECT_EQ(stk_pop(new_stack), (void*) NULL);
  EXPECT_EQ(stk_size(new_stack), 0);
  Iterator* new_iter = stk_iterator(new_stack);
  EXPECT_EQ(iter_next(new_iter), (void*) NULL);
  iter_destroy(new_iter);
  stk_destroy(new_stack);
}

TEST(StackTests, Push_Pop_Speed) {
  Stack* new_stack = stack();
  int* mints[O1BATCHSIZE];
  int i;
  for (i = 0; i < O1BATCHSIZE; i++) {
    mints[i] = (int*) malloc(sizeof(int));
    *mints[i] = i;
    stk_push(new_stack, mints[i]);
  }

  int* data;
  i = 0;
  for (i = O1BATCHSIZE - 1; i >= 0; i--) {
    data = (int*) stk_pop(new_stack);
    EXPECT_EQ(*data, *mints[i]);
  }

  Iterator* iter = stk_iterator(new_stack);
  iter_destroy(iter);
  stk_destroy(new_stack);

  for (i = 0; i < O1BATCHSIZE; i++) {
    free(mints[i]);
  }
}

TEST(CDLinkedList, FirstTest) {
  CDLinkedList* list = cdlinkedlist();

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

  cdll_append(list, my_strs[1]);
  cdll_prepend(list, my_strs[0]);
  cdll_append(list, my_strs[3]);
  cdll_insert_at(list, 2, my_strs[2]);
  cdll_append(list, my_strs[4]);

  EXPECT_EQ(cdll_remove(list, 0), my_strs[0]);

  cdll_destroy(list);
  for (int i = 0; i < 5; i++) {
    free(my_strs[i]);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
