#include <stdio.h>
#include <stdlib.h>
#include "reroot.h"

int main(int argc, char** argv)
{
  if(argc != 5)
  {
    return EXIT_FAILURE;
  }
  FILE *fp = fopen(argv[1], "r");
  if(fp == NULL)
  {
    return EXIT_FAILURE;
  }
  LNode *head = NULL;
  LNode *head_clone = NULL;
  
  char c_get;
  c_get = fgetc(fp);

  int x_temp;
  int y_temp;
  int lab;
  char lab_temp;
  //check if end of file
  while(c_get != EOF)
  {  
    //check if new line
    if(c_get == '\n')
    {
      c_get = fgetc(fp);
    }
    //printf("c_get: %c\n", c_get);
    //create tree node and list node 
    Node* a = malloc(sizeof(Node));
    LNode* b = malloc(sizeof(LNode));

    Node* a_clone = malloc(sizeof(Node));
    LNode* b_clone = malloc(sizeof(LNode));

    b->next = NULL;
    b->tnode = a;

    b_clone->next = NULL;
    b_clone->tnode = a_clone;

    a->left = NULL;
    a->right = NULL;
    a->status = 0;
    a->val = -1;
    a->value = 'a';

    a_clone->left = NULL;
    a_clone->right = NULL;
    a_clone->status = 0;
    a_clone->val = -1;
    a_clone->value = 'a';

    //determine which kind of thing it is
    if(c_get != 'H' && c_get != 'V')
    {
      fseek(fp, -1, SEEK_CUR);
      if (fscanf(fp, "%d(%d,%d)\n",&lab, &x_temp, &y_temp) == 0)
      {
        fprintf(stderr, "Could not read values\n");
        printf("%c\n",c_get);
        return 1;
      }
      //printf("read val: %d\n",lab);
      a->val = lab;
      a->dim[0] = x_temp;
      a->dim[1] = y_temp;
      a->status = 1;
      push(&head, b);

      a_clone->val = lab;
      a_clone->dim[0] = x_temp;
      a_clone->dim[1] = y_temp;
      a_clone->status = 1;
      push(&head_clone, b_clone);
      //printf("%d\n", head->tnode->val);
    }
    else
    {
      //printf("here\n");
      fseek(fp, -1, SEEK_CUR);
      if (fscanf(fp, "%c\n",&lab_temp) == 0)
      {
        fprintf(stderr, "Could not read values\n");
        printf("%c\n",c_get);
        return 1;
      }
      a->value = lab_temp;
      LNode* right_n = pop(&head);
      LNode* left_n = pop(&head);
      a->right = right_n->tnode;
      a->left = left_n->tnode;
      push(&head, b);
      free(right_n);
      free(left_n);

      a_clone->value = lab_temp;
      LNode* right_n_clone = pop(&head_clone);
      LNode* left_n_clone = pop(&head_clone);
      a_clone->right = right_n_clone->tnode;
      a_clone->left = left_n_clone->tnode;
      push(&head_clone, b_clone);
      free(right_n_clone);
      free(left_n_clone);
    }
    c_get = fgetc(fp);
  }
  fclose(fp);

  fp = fopen(argv[4], "w");
  if(fp == NULL)
  {
    free_tree(head->tnode);
    free_tree(head_clone->tnode);
    free(head);
    free(head_clone);
    return EXIT_FAILURE;
  }
  out_3_pr(fp, head->tnode);
  fclose(fp);

  head->tnode = reroot_left(head->tnode);
  fp = fopen(argv[2], "w");
  if(fp == NULL)
  {
    free_tree(head->tnode);
    free_tree(head_clone->tnode);
    free(head);
    free(head_clone);
    return EXIT_FAILURE;
  }
  print_pre(fp, head->tnode);
  fclose(fp);

  head_clone->tnode = reroot_right(head_clone->tnode);
  fp = fopen(argv[3], "w");
  if(fp == NULL)
  {
    free_tree(head->tnode);
    free_tree(head_clone->tnode);
    free(head);
    free(head_clone);
    return EXIT_FAILURE;
  }
  print_pre(fp, head_clone->tnode);
  fclose(fp);

  free_tree(head->tnode);
  free(head);
  free_tree(head_clone->tnode);
  free(head_clone);
}