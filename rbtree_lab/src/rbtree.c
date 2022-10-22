#include "rbtree.h"
#include <stdlib.h>
#define SENTINEL TRUE

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)malloc(sizeof(rbtree)* 1);
  p->nil = (node_t *)malloc(sizeof(node_t) * 1);
  p->root = p->nil;
  if (p->nil != NULL){
	p->nil->color = RBTREE_BLACK;
  }
  // TODO: initialize struct if needed
  return p;
}

void delete_tree_nodes(node_t *n){
if (n != NULL){
	delete_tree_nodes(n->left);
	delete_tree_nodes(n->right);
	free(n);
	}
	return ;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if (t != NULL) {
	delete_tree_nodes(t->root);
	free(t);
	if (t) printf("still");
	else printf("die");
  }
  return ;
}

void left_rotate(rbtree  *t, node_t *n){
	node_t *y = n->right;
	n->right = y->left;
	if (y->left != t->nil) {
		y->left->parent = n;
	}
	y->parent = n->parent;
	if (n->parent == t->nil) {
		t->root = y;
	}
	else if (n == n->parent->left) {
		n->parent->left = y;
	}
	else{
		n->parent->right = y;
	}
	y->left = n;
	n->parent = y;
}
void right_rotate(rbtree *t, node_t *n) {
	node_t *y = n->left;
	n->left = y -> right;
	if (y-> right!= t->nil) {
		y->left->parent = n;
	}
	y->parent = n->parent;
	if (n->parent == t->nil) {
		t->root = y;
	}
	else if (n== n->parent->left){
		n->parent->right = y;
	}
	else{
		n->parent->left = y;
	}
	y->right = n;
	n->parent = y;
}

void rbtree_insert_fixup(rbtree *t, node_t *new){
	node_t *y;
	while (new->parent->color == RBTREE_RED){
		if (new->parent == new->parent->parent->left){
			y = new->parent->parent->right;
			if (y->color == RBTREE_RED){
				new->parent->color = RBTREE_BLACK;
				y->color = RBTREE_BLACK;
				new->parent->parent->color = RBTREE_RED;
				new = new->parent->parent;
			}
			else if (new == new->parent->right){
				new = new->parent;
				left_rotate(t, new);
			}
			new->parent->color = RBTREE_BLACK;
			new->parent->parent->color = RBTREE_RED;
			right_rotate(t, new->parent->parent);
		}
		else{
			y = new->parent->parent->left;
			if (y->color == RBTREE_RED){
				new->parent->color = RBTREE_BLACK;
				y->color = RBTREE_BLACK;
				new->parent->parent->color = RBTREE_RED;
				new = new->parent->parent;
			}
			else if (new == new->parent->left){
				new = new->parent;
				right_rotate(t, new);
			}
			new->parent->color = RBTREE_BLACK;
			new->parent->parent->color = RBTREE_RED;
			left_rotate(t, new->parent->parent);
		}
	}
	t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
	node_t *p = t -> root;
	node_t *c = t -> nil;
	node_t *new = (node_t *)calloc(1, sizeof(node_t));
	new->key = key;
	while (p != NULL && (p != t->nil)){
		c = p;
		if (p->key < key) p = p->left;
		else p = p->right;
	}
	new->parent = c;
	if (c == t->nil){
		t->root = new;
	}
	else if (key < c->key)
	{
		c->left = new;
	}
	else{
		c->right = new;
	}
	new->right = t->nil;
	new->left = t->nil;
	new->color = RBTREE_RED;
	rbtree_insert_fixup(t, new);
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TOD O: implement to_array
  return 0;
}
