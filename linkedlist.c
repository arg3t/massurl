/*
 * linkedlist.c
 *
 * Created by Yigit Colakoglu on 07/06/2021.
 * Copyright yigit@yigitcolakoglu.com. 2021. All rights reserved.
 */

#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


LinkedList *linkedlistalloc(void){
    return (LinkedList *) malloc(sizeof(LinkedList));
}

int linkedlistfind(LinkedList *p, char *str) {
    int count = 0;
    while(p != NULL){
        if(!strcmp(p->data, str))
            return count;
        count++;
        p = p->next;
    }
    return -1;
}

LinkedList *linkedlistadd(LinkedList *p, char *data){
    if(p == NULL){
        p = linkedlistalloc();
        p->next = NULL;
        p->data = data;
    }else
        p->next = linkedlistadd(p->next, data);
    return p;
}

void linkedlistprint(LinkedList *p, FILE *out){
    if(p != NULL){
        (p->data == NULL) ? fprintf(out, "NULL") : fprintf(out, "%s", p->data);
        (p->next == NULL) ? : fprintf(out, "%c",'&');
        linkedlistprint(p->next, out);
    }
}
