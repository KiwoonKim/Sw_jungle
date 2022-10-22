#include "rbtree.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#define SENTINEL 0
void test_init(void)
{
    rbtree *t = new_rbtree();
    assert(t != NULL);
#ifdef SENTINEL
    assert(t->nil != NULL);
    assert(t->root == t->nil);
    printf("sentienl");
#else
    assert(t->root == NULL);
#endif
    delete_rbtree(t);
    printf("hey");
}
// root node should have proper values and pointers
void test_insert_single(const key_t key) {
  rbtree *t = new_rbtree();
  node_t *p = rbtree_insert(t, key);
  assert(p != NULL);
  assert(t->root == p);
  assert(p->key == key);
  // assert(p->color == RBTREE_BLACK);  // color of root node should be black
#ifdef SENTINEL
  assert(p->left == t->nil);
  assert(p->right == t->nil);
  assert(p->parent == t->nil);
#else
  assert(p->left == NULL);
  assert(p->right == NULL);
  assert(p->parent == NULL);
#endif
  delete_rbtree(t);
  printf("0");
}

int main(int argc, char *argv[])
{
    test_init();
    test_insert_single(1000);
    // rbtree *t = new_rbtree();
    // node_t *p = rbtree_insert(t, 1000);
    // node_t *s = rbtree_insert(t, 2000);
    // printf("%d\n", p->key);
    // printf("%d\n", s->right->key);
    // printf("%d", s->right->color);
}
