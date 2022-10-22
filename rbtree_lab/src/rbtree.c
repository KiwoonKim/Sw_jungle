#include "rbtree.h"
#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->root = NULL;
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  if (p->nil != NULL){
	p->nil->color = 1;
  }
  // TODO: initialize struct if needed
  return p;
}

void delete_tree_nodes(node_t *n){
if (n != NULL){
	if (n->left != NULL){
		delete_tree_nodes(n->left);
	}
	else if (n->right != NULL){
		delete_tree_nodes(n->right);
	}
	free(n);}
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if (t != NULL) {
		delete_tree_nodes(t->root);
		free(t);
  }
}
/*
void left_rotate(rbtree  *t, node_t *n){
	node_t *y = n->;
	n-> = y->left;
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
void _rotate(rbtree *t, node_t *n) {
	node_t *y = n->left;
	n->left = y -> ;
	if (y-> != t->nil) {
		y->left->parent = n;
	}
	y->parent = n->parent;
	if (n->parent == t->nil) {
		t->root = y;
	}
	else if (n== n->parent->left){
		
	}
}
void rbtree_insert_fixup(rbtree *t, node_t *new){
	node_t *y;
	while (new->parent->color == 0){
		if (new->parent == new->parent->parent->left){
			y = new->parent->parent->;
			if (y->color == 0){
				new->parent->color = 1;
				y->color = 1;
				new->parent->parent->color = 0;
				new = new->parent->parent;
			}
			else if (new == new->parent->){
				new = new->parent;
				left_rotate(t, new);
			}
			new->parent->color = 1;
			new->parent->parent->color = 0;
			_rotate(t, new->parent->parent);
		}
		else{
			y = new->parent->parent->left;
			if (y->color == 0){
				new->parent->color = 1;
				y->color = 1;
				new->parent->parent->color = 0;
				new = new->parent->parent;
			}
			else if (new == new->parent->left){
				new = new->parent;
				_rotate(t, new);
			}
			new->parent->color = 1;
			new->parent->parent->color = 0;
			left_rotate(t, new->parent->parent);
		}
	}
	t->root->color = 1;
}
*/
node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
	node_t *p = t -> root;
	node_t *Tnil = t -> nil;
	/*
	if (p == Tnil) {
		p->color = 1;
		p->key = key;
		p->parent = p->left = p-> = t->nil;
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
//	rbtree_insert_fixup(t, new);
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
