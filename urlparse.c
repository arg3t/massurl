/*
 * urlparse.c
 *
 * Created by Yigit Colakoglu on 07/06/2021.
 * Copyright yigit@yigitcolakoglu.com. 2021. All rights reserved.
 */

#include "urlparse.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

URL *parseurl(char *url) {
  URL *urlp = urlalloc();
  urlp->params = NULL;
  urlp->nparams = 0;
  short stage = 0; /* var to keep track of where we are in url */
  int counter = 0;

  while (*url != '\0' && *url != '\n') {
    switch (*url++) {
    case ':':
      counter++;
      if (stage == 0) {
        urlp->https = *(url - 2) == 's';
        if (*(url + 1) == '\0' || *url == '\0' || *url == '\n') /* weird stuff would happen with strings like "http:" */
          return NULL;
        url += 2; /* Skip the // after the :*/
        stage = 1;
        counter+=3;
      }
      break;

    case '?':
      if (stage == 1) {
        urlp->base =
            (char *)malloc(counter); /* +1 for the '\0' in the end */
        strncpy(urlp->base, url - counter, counter - 1);
        stage = 2;
        counter = 1;
      } else {
        return NULL;
      }
      break;

    case '=':
      if (stage == 2) {
        char *foo;
        foo = (char *)malloc(counter);
        strncpy(foo, url - counter, counter-1);
        counter = 1;
        if (urlp->params == NULL){
          urlp->params = linkedlistalloc();
          urlp->params->data = foo;
        }else
          urlp->params = linkedlistadd(urlp->params, foo);
        urlp->nparams++;
        while(*url != '&' && *url != '\0' && *url != '\n')
          url++;
        url++;
      } else {
        return NULL;
      }
      break;

    default:
      counter++;
      break;
    }
  }

  switch(stage){
    case 0:
      return NULL;
      break;
    case 1:
      urlp->base = (char *)malloc(counter); /* +1 for the '\0' in the end */
      strncpy(urlp->base, url - (counter-1), counter - 1);
      break;
    case 2:
      break;
    default:
      return NULL;
    }
  return urlp;
}

URL *urlalloc(void) { return (URL *)malloc(sizeof(URL)); }
