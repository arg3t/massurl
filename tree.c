/*
 * tree.c
 *
 * Created by Yigit Colakoglu on 07/06/2021.
 * Copyright yigit@yigitcolakoglu.com. 2021. All rights reserved.
 */

#include "tree.h"
#include "linkedlist.h"
#include "urlparse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern TreeNode *root;

TreeNode *addtree(TreeNode *parent, TreeNode *p) {
  if (parent == NULL)
    return p;
  int strdiff = strcmp(parent->path, p->path);
  if (!strdiff) {
    while (p->params != NULL) {
      if (p->params == NULL ||
          linkedlistfind(parent->params, p->params->data) == -1) {
        p->params = linkedlistadd(parent->params, p->params->data);
      }
      p->params = p->params->next;
    }
  } else if (strdiff < 0) {
    parent->left = addtree(parent->left, p);
    parent->left->parent = parent;
  } else {
    parent->right = addtree(parent->right, p);
    parent->right->parent = parent;
  }
  return parent;
}

void rotatetreeleft(TreeNode *p) {
  TreeNode *r = p->right;
  p->right = r->left;
  if (p->right)
    p->right->parent = p;
  r->parent = p->parent;
  if (p->parent == NULL)
    root = r;
  else if (p->parent->left == p)
    p->parent->left = r;
  else
    p->parent->right = r;
  r->left = p;
  p->parent = r;
}

void rotatetreeright(TreeNode *p) {
  TreeNode *l = p->left;
  p->left = l->right;
  if (p->left)
    p->left->parent = p;
  l->parent = p->parent;
  if (p->parent == NULL)
    root = l;
  else if (p->parent->left == p)
    p->parent->left = l;
  else
    p->parent->right = l;
  l->right = p;
  p->parent = l;
}

void balancetree(TreeNode *root, TreeNode *node) {
  TreeNode *p = NULL;
  TreeNode *gP = NULL;
  
  while (node->parent != NULL && node->parent->parent != NULL && node->red && node->parent->red ) {
    p = node->parent;
    gP = node->parent->parent;
    if (gP->left == p) {
      if (gP->right != NULL && gP->right->red) {
        gP->red = 1;
        gP->left->red = 0;
        gP->right->red = 0;
        node = gP;
      }else{
        if(p->right == node){
          rotatetreeleft(p);
          node = p;
          p = node->parent;
        }else{
          rotatetreeright(gP);
          int c = p->red;
          p->red = gP->red;
          gP->red = c;
          node = p;
        }
      }
    } else {
      if(gP->left != NULL && gP->left->red){
        gP->red = 1;
        gP->left->red = 0;
        gP->right->red = 0;
        node = gP;
      }else{
        if(p->left == node){
          rotatetreeright(p);
          node = p;
          p = node->parent;
        }else{
          rotatetreeleft(gP);
          int c = p->red;
          p->red = gP->red;
          gP->red = c;
          node = p;
        }
      }
    }
  }
  root->red = 0;
}

TreeNode *treealloc(void) { return (TreeNode *)malloc(sizeof(TreeNode)); }

void printtree(TreeNode *root, FILE *out, char *payload, int minparams) {
  if (root != NULL) {
    printtree(root->left, out, payload, minparams);
    if(root->nparams >= minparams){
      fprintf(out, "%s", root->path);
      (!root->nparams) ? : fprintf(out, "%c",'?');
      linkedlistprint(root->params, out, payload);
      fprintf(out, "%c", '\n');
    }
    printtree(root->right, out, payload, minparams);
  }
}
