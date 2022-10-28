#include "rbtree.h"
#include <stdlib.h>
#define SENTINEL TRUE

rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    if (p == NULL) return NULL;
    p->nil = (node_t *)calloc(1, sizeof(node_t));
    if (p->nil == NULL) return NULL;
    p->root = p->nil;
    p->nil->color = RBTREE_BLACK;
    // TODO: initialize struct if needed
    return p;
}

void delete_tree_nodes(rbtree *t, node_t *n){
    if (n == t->nil) {		
	return ;	
    }
    delete_tree_nodes(t, n->left);
    n->left = NULL;
    delete_tree_nodes(t, n->right);
    n->right = NULL;
    free(n);
}

void delete_rbtree(rbtree *t) {
    // TODO: reclaim the tree nodes's memory
    if (t == NULL) return ;
    if (t->root != t->nil){
	delete_tree_nodes(t, t->root);
    }
    free(t->nil);
    t->nil = NULL;
    free(t);
    // 여기서 t = NULL 해도 반영 안됨.
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
	y->right->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == t->nil) {
	t->root = y;
    }
    else if (n== n->parent->right){
	n->parent->right = y;
    }
    else{
	n->parent->left = y;
    }
    y->right = n;
    n->parent = y;
}

void rbtree_insert_fixup(rbtree *t, node_t *new){
    node_t *y = NULL;
    while (new->parent->color == RBTREE_RED){
	if (new->parent == new->parent->parent->left){
	    y = new->parent->parent->right;
	    if (y->color == RBTREE_RED){
		new->parent->color = RBTREE_BLACK;
		y->color = RBTREE_BLACK;
		new->parent->parent->color = RBTREE_RED;
		new = new->parent->parent;
	    }
	    else {
		if (new == new->parent->right){
		    new = new->parent;
		    left_rotate(t, new);
		}
		new->parent->color = RBTREE_BLACK;
		new->parent->parent->color = RBTREE_RED;
		right_rotate(t, new->parent->parent);
	    }
	}
	else{
	    y = new->parent->parent->left;
	    if (y->color == RBTREE_RED){
		new->parent->color = RBTREE_BLACK;
		y->color = RBTREE_BLACK;
		new->parent->parent->color = RBTREE_RED;
		new = new->parent->parent;
	    }
	    else {
		if (new == new->parent->left){
		    new = new->parent;
		    right_rotate(t, new);
		}		
		new->parent->color = RBTREE_BLACK;
		new->parent->parent->color = RBTREE_RED;
		left_rotate(t, new->parent->parent);
	    }
	}
    }
    t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
    // TODO: implement insert
    node_t *p = t -> root;
    node_t *c = t -> nil;
    node_t *new = (node_t *)calloc(1, sizeof(node_t));
    if (new == NULL) {exit(1); return NULL;}
    while (p != NULL && (p != t->nil)){
	c = p;
	if (key < p->key) p = p->left;
	else p = p->right;
    }
    new->parent = c;
    if (c == t->nil){
	t->root = new;
    }
    else if (key < c->key) c->left = new;
    else c->right = new;
    new->right = t->nil;
    new->left = t->nil;
    new->key = key;
    new->color = RBTREE_RED;
    rbtree_insert_fixup(t, new);
    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    node_t *ret;
    ret = t->root;
    while (ret -> key != key && ret != t->nil){
	if (ret -> key > key) {
	    ret = ret -> left;
	}
	else ret = ret -> right;
    }
    if (ret == t->nil) return NULL;
    // TODO: implement find
    return ret;
}

node_t *rbtree_min(const rbtree *t) {
    node_t *ret = t -> root;
    while (ret -> left != t -> nil)
    {
	ret = ret -> left;
    }
    // TODO: implement find
    return ret;
}

node_t *rbtree_max(const rbtree *t) {
    node_t *ret = t -> root;
    while (ret -> right != t-> nil){
	ret = ret -> right;
    }
    // TODO: implement find
    return ret;
}
node_t *rbtree_sub_min(const rbtree *t, node_t* x) {
    node_t *ret = x;
    while (ret -> left != t -> nil)
    {
	ret = ret -> left;
    }
    // TODO: implement find
    return ret;
}
void rb_transplant(rbtree *t, node_t *u, node_t *v){
    if (u->parent == t->nil){
	t->root = v;
    }
    else if (u == u->parent->left){
	u->parent->left = v;
    }
    else {
	u->parent->right = v;
    }
    v->parent = u->parent;
}

void rb_erase_fixup(rbtree *t, node_t  *n){
    while (n != t->root && n->color == RBTREE_BLACK)
    {

	if (n == n->parent->left){ // n이 왼쪽에서 왔을 경우
	    node_t *w = n->parent->right; 	// n의 형제 노드로 시작
	    if (w->color == RBTREE_RED){	// 그 색이 빨강이면
		w->color = RBTREE_BLACK;	// 검정으로 만들고 
		n->parent->color = RBTREE_RED;	//부모를 빩으로 바꾼뒤
		left_rotate(t, n->parent);	// 왼쪽 회전
		w = n->parent->right;				// w를 부모로 바꿈 회전 전에는 w의 왼쪽 자식이였음
	    }
	    if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK){
		w->color = RBTREE_RED;
		n = n->parent;
	    }
	    else {
		if (w->right->color == RBTREE_BLACK) {	// 새로운 w의 왼쪽이 빨강이면
		    w->left->color = RBTREE_BLACK;
		    w->color = RBTREE_RED;
		    right_rotate(t, w);
		    w = n->parent->right;
		}
		w->color = n->parent->color;
		n->parent->color = RBTREE_BLACK;
		w->right->color = RBTREE_BLACK;
		left_rotate(t, n->parent);
		n = t->root;
	    }
	}
	else{ // n이 오른쪽에서 온경우
	    node_t *w = n->parent->left;
	    if (w->color == RBTREE_RED){
		w->color = RBTREE_BLACK;
		w->parent->color = RBTREE_RED;
		right_rotate(t, n->parent);
		w = n->parent->left; 
	    }
	    if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK){
		w->color =RBTREE_RED;
		n = n->parent;
	    }
	    else {
		if (w->left->color == RBTREE_BLACK) {
		    w->right->color = RBTREE_BLACK;
		    w->color = RBTREE_RED;
		    left_rotate(t, w);
		    w = n->parent->left;
		} 
		w->color = n->parent->color;
		n->parent->color = RBTREE_BLACK;
		w->left->color = RBTREE_BLACK;
		right_rotate(t, n->parent);
		n = t->root;
	    }
	}
    }
    n->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
    // TODO: implement erase
    node_t *y = p;
    node_t *x = NULL;
    color_t y_origin_c = y->color;
    // 삭제노드가 말단 노드인 경우와 그렇지 않은 경우.
    if (p->left == t->nil) {
	x = p->right;
	rb_transplant(t, p, p->right); // p의 오른쪽에 있는 녀석을 p의 자리로 옮겨 심기
    }
    else if(p->right == t->nil) {
	x = p->left;
	rb_transplant(t, p, p->left);
    }
    else {
	y = y->right;
	while (y->left != t->nil)
	{
	    y = y->left;
	}
	y_origin_c = y->color;
	x = y->right;
	if (y->parent == p){
	    x->parent = y;
	}
	else{
	    rb_transplant(t, y, y->right);
	    y->right = p->right;
	    y->right->parent = y;
	}
	rb_transplant(t, p, y);
	y->left = p->left;
	y->left->parent = y;
	y->color = p->color;
    }
    if (y_origin_c == RBTREE_BLACK) rb_erase_fixup(t, x);
    free(p);
    return 0;
}
/*
   void put_num(const rbtree *t, node_t *nd, key_t *arr, const size_t n, int *i)
   {
   if (n == *i || nd == t->nil) return ;
   if (nd->left != t->nil) put_num(t, nd->left, arr, n, i);
   if (*i < n) {
 *(arr + *i) = nd->key;
 *i += 1;
 }
 if (nd->right != t->nil) put_num(t, nd->right, arr, n, i);
 }
 */
int put_num2(const rbtree *t, node_t *nd, key_t *arr, const size_t n, int i)
{
    if (!(i < n) || nd == t->nil) return i;
    i = put_num2(t, nd->left, arr, n, i);
    if (i < n) arr[i++] = nd->key;
    i = put_num2(t, nd->right, arr, n, i);
    return i;
}
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
    int i = 0;
    put_num2(t, t->root, arr, n, i);  // TOD O: implement to_array
    return 0;
}
