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

#define RANDLEN 6


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


char rstr[RANDLEN+1];

char *randstr(){
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int n = RANDLEN;
    while((--n) > -1){
        size_t index = (double) rand()/RAND_MAX * (sizeof charset - 1);
        rstr[n] = charset[index];
    }
    return rstr;
}

void linkedlistprint(LinkedList *p, FILE *out, char* payload){
    int random = 0;
    if(!payload){
        random = 1;
        payload = randstr();
    }
    if(p != NULL){
        (p->data == NULL) ? fprintf(out, "NULL=NULL") : fprintf(out, "%s=%s", p->data, payload);
        (p->next == NULL) ? : fprintf(out, "%c",'&');
        if(random)
            payload = NULL;
        linkedlistprint(p->next, out, payload);
    }
}
