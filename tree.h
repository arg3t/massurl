/*
 * tree.h
 *
 * Created by Yigit Colakoglu on 07/06/2021.
 * Copyright yigit@yigitcolakoglu.com. 2021. All rights reserved.
 */

#include "urlparse.h"
#include <stdio.h>

#ifndef tree_h
#define tree_h

typedef struct tnode {
    char *path;
    unsigned int red : 1;
    LinkedList *params;
    int nparams;
    struct tnode *parent;
    struct tnode *left;
    struct tnode *right;
} TreeNode;

TreeNode *addtree(TreeNode *parent, TreeNode *node);
void rotatetreeright(TreeNode *node);
void rotatetreeleft(TreeNode *node);
void balancetree(TreeNode *root, TreeNode *node);
TreeNode *treealloc(void);
void printtree(TreeNode *root, FILE *out, char *payload, int minparams);

#endif /* Symbol’s value as variable is void: \. */
