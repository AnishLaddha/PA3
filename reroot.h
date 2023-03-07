#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
  char value;
  int val;
  int status; //0 for H/V, 1 for a num
  int dim[2];
  struct _Node *left, *right;
} Node;

typedef struct _LNode {
  struct _Node* tnode;
  struct _LNode* next;
}LNode;


void push(LNode **head, LNode *new);
LNode* pop(LNode **head);
void free_tree(Node* root);
void print_po(Node *root);
Node* reroot_left(Node * root);
Node* reroot_right(Node *root);
void print_pre(FILE *fp, Node *root);
void out_3_pr(FILE *fp, Node *root);