#include <stdio.h>
#include <stdlib.h>
#include "reroot.h"



void push(LNode **head, LNode *new)
{
  new->next = *head;
  *head = new;
  //printf("head: %d\n", *head->tnode->val);
  // if(head->next !=NULL)
  // {
  //   printf("new/next: %d\n", *head->next->tnode->val);
  // }
  // else{
  //   printf("new/next: NULL");
  // }
}
LNode* pop(LNode **head)
{
  LNode* temp = *head;
  *head = (*head)->next;
  return temp;
}

void free_tree(Node* root)
{
  if(root == NULL)
  {
    return;
  }
  free_tree(root->left);
  free_tree(root->right);
  free(root);
}

void print_po(Node *root)
{
  if(root == NULL)
  {
    return;
  }
  print_po(root->left);
  print_po(root->right);

  if(root->value == 'H' || root->value == 'V')
  {
    printf("%c\n", root->value);
  }
  else{
    printf("%d(%d,%d)\n", root->val, root->dim[0], root->dim[1]);
  }
}

Node* reroot_left(Node *root)
{
  //printf("root: %c\n", root->value);

  int flip_flop = 0; //0 == left mode, 1 == right mode
  Node *curr = root->left;
  Node *end = curr->right;
  Node *temp = NULL;
  while(end != NULL)
  {
    if(flip_flop == 0)
    {
      temp = curr->left;
      curr->left = root;
      root->left = temp;

      root = curr;
      curr = end;
      end = end->left;
      flip_flop = 1;
    }
    else
    {
      temp = curr->right;
      curr->right = root;
      root->right = temp;

      root = curr;
      curr = end;
      end = end->right;
      flip_flop = 0;
    }
  }
  return root;
}

Node* reroot_right(Node *root)
{
  //printf("root: %c\n", root->value);

  int flip_flop = 1; //0 == left mode, 1 == right mode
  Node *curr = root->right;
  Node *end = curr->left;
  Node *temp = NULL;
  while(end != NULL)
  {
    if(flip_flop == 0)
    {
      temp = curr->left;
      curr->left = root;
      root->left = temp;

      root = curr;
      curr = end;
      end = end->left;
      flip_flop = 1;
    }
    else
    {
      temp = curr->right;
      curr->right = root;
      root->right = temp;

      root = curr;
      curr = end;
      end = end->right;
      flip_flop = 0;
    }
  }
  return root;
}

void print_pre(FILE *fp, Node *root)
{
  if(root == NULL) return;

  if(root->value == 'H' || root->value == 'V')
  {
    fprintf(fp,"%c\n", root->value);
  }
  else{
    fprintf(fp,"%d(%d,%d)\n", root->val, root->dim[0], root->dim[1]);
  }
  print_pre(fp, root->left);
  print_pre(fp, root->right);
}

void out_3_pr(FILE *fp, Node *root)
{
  if(root == NULL) return;
  if(root->value == 'H' || root->value == 'V')
  {
    fprintf(fp,"%c\n", root->value);
  }
  else{
    fprintf(fp,"%d\n", root->val);
  }
  out_3_pr(fp, root->left);
  out_3_pr(fp, root->right);
}