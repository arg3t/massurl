/*
 * tree.c
 *
 * Created by Yigit Colakoglu on 07/06/2021.
 * Copyright yigit@yigitcolakoglu.com. 2021. All rights reserved.
 */

#include "tree.h"
#include "linkedlist.h"
#include "urlparse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TreeNode *addtree(TreeNode *p, URL *url) {
  if (p == NULL) {
    TreeNode *newnode = treealloc();
    newnode->path = url->base;
    newnode->params = url->params;
    newnode->left = newnode->right = NULL;
    return newnode;
  }
  int strdiff = strcmp(url->base, p->path);
  if (!strdiff) {
    while(url->params != NULL){
      if(p->params == NULL || linkedlistfind(p->params, url->params->data) == -1){
        p->params = linkedlistadd(p->params, url->params->data);
      }
      url->params = url->params->next;
    }
  } else if (strdiff < 0) {
    p->left = addtree(p->left, url);
  } else {
    p->right = addtree(p->right, url);
  }
  return p;
}

TreeNode *treealloc(void){
    return (TreeNode *) malloc(sizeof(TreeNode));
}

void printtree(TreeNode *root, FILE *out){
    if(root != NULL){
        printtree(root->left, out);
        fprintf(out, "%s ", root->path);
        linkedlistprint(root->params, out);
        fprintf(out, "%c", '\n');
        printtree(root->right, out);
    }
}
