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

typedef struct {
    char *path;
    LinkedList *params;
    struct tnode *left;
    struct tnode *right;
} TreeNode;

TreeNode *addtree(TreeNode *root, URL *url);
TreeNode *treealloc(void);
void printtree(TreeNode *root, FILE *out);

#endif /* Symbol’s value as variable is void: \. */
