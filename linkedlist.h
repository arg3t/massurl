/*
 * linkedlist.h
 *
 * Created by Yigit Colakoglu on 07/06/2021.
 * Copyright yigit@yigitcolakoglu.com. 2021. All rights reserved.
 */

#ifndef linkedlist_h
#define linkedlist_h

#include <stdio.h>

typedef struct {
    struct linkedlist *next;
    char *data;
} LinkedList;

LinkedList *linkedlistalloc(void);
int linkedlistfind(LinkedList *p, char *str);
LinkedList*linkedlistadd(LinkedList *p, char *data);
void linkedlistprint(LinkedList *p, FILE *out);
#endif /* Symbol’s value as variable is void: \. */
