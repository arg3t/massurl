/*
 * urlparse.h
 *
 * Created by Yigit Colakoglu on 07/06/2021.
 * Copyright yigit@yigitcolakoglu.com. 2021. All rights reserved.
 */

#include "linkedlist.h"

#ifndef urlparse_h
#define urlparse_h

typedef struct{
    unsigned int https : 1;
    char *base;
    LinkedList *params;
    int nparams;
} URL;

URL *parseurl(char *urlstr);
URL *urlalloc(void);

#endif /* Symbol’s value as variable is void: \. */
