#include "rbtree.h"

#include <stdlib.h>
rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  p->nil->color = 1;
  p->root = p->nil;
  // TODO: initialize struct if needed
  return p;
}

void delete_tree_nodes(node_t *n){
	if (n->left){
		delete_tree_nodes(n->left);
	}
	else if (n->right){
		delete_tree_nodes(n->right);
	}
	free(n);
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
	delete_tree_nodes(t->root);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
	node_t *p = t -> root;
	node_t *Tnil = t -> nil;
	/*
	if (p == Tnil) {
		p->color = 1;
		p->key = key;
		p->parent = p->left = p->right = t->nil;
		return t->root;
	}
	*/
	node_t *new = (node_t *)calloc(1, sizeof(node_t));
	new->color = 0;
	new->key = key;
	new->left = new->right = Tnil;
	while (p->left != Tnil || p->right != Tnil){
		if (p->key < key) p = p->left;
		else p = p->right;
	}
	if (p->key < key) {
		new->parent = p;
		p->left = new;
	}
	else {
		new->parent = p;
		p->right = new;
	}
	rbtree_insert_fixup(t, new);
  return t->root;
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
			
	}
}
void right_rotate(rbtree *t, node_t *n) {
	node_t *y = n->left;
	n->left = y -> right;
	if (y->right != t->nil) {
		y->left->parent = n;
	}
	y->parent = n->parent;
	if (n->parent == t->nil) {
		t->root = y;
	}
	else if (n== n->parent->left){
		
	}
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
