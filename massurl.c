/*
 * massurl.c
 *
 * Created by Yigit Colakoglu on 07/06/2021.
 * Copyright yigit@yigitcolakoglu.com. 2021. All rights reserved.
 */

#include "strings.h"
#include "tree.h"
#include "urlparse.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXURL 100000
#define MAXPAYLOAD 10000

static void usage(void) {
fputs("\
usage: massurl [-r] [-v] [-o outfile] [-p payloads] [-n minparamnum] input_file\n", stderr);
  exit(1);
}

TreeNode *root = NULL;

int main(int argc, char *argv[]) {

  FILE *fin = stdin, *fout = stdout, *payloads = NULL;
  char *param, urlstr[MAXURL], payload[MAXPAYLOAD];
  int minparamn, verbose = 0, npayloads = 1;
  int randpayloads = 0;
  time_t begin = time(NULL);
  unsigned long lines, errors = 0;

  while (--argc > 0) {
    param = *++argv;
    if (param[0] == '-') {
      param++;
      switch (*param) {
      case 'o':
        if ((fout = fopen(*++argv, "w")) == NULL) {
          fprintf(stderr, "Can't open output file for writing.\n");
          return 1;
        }
        if (ferror(fout)) {
          fprintf(stderr, "Can't open output file for writing.\n");
          return 1;
        }
        break;
      case 'n':
        minparamn = atoi(*++argv);
        argc--;
        break;
      case 'v':
        verbose = 1;
        break;
      case 'r':
        randpayloads = 1;
        break;
      case 'h':
        usage();
        break;
      case 'p':
        if ((payloads = fopen(*++argv, "r")) == NULL) {
          fprintf(stderr, "Can't open payload file for reading.\n");
          return 1;
        }
        if (ferror(fout)) {
          fprintf(stderr, "Can't open payload file for reading.\n");
          return 1;
        }
        break;
      default:
        fprintf(stderr, "Parameter -%c does not exist!\n", *param);
        usage();
      }
    } else {
      if ((fin = fopen(param, "r")) == NULL) {
        fprintf(stderr, "Can't open file %s\n", param);
        return 1;
      }
    }
  }
  printf("v:%d r:%d\n", verbose, randpayloads);

  URL *url;
  while (fgets(urlstr, MAXURL, fin) != NULL) {
    lines++;
    if ((url = parseurl(urlstr)) == NULL) {
      errors++;
      if (verbose)
        fprintf(stderr, "Malformed URL %s", urlstr);
      continue;
    }
    TreeNode *newnode = treealloc();
    newnode->path = url->base;
    newnode->params = url->params;
    newnode->parent = NULL;
    newnode->left = newnode->right = NULL;
    newnode->nparams = url->nparams;
    newnode->red = 1; /* Always color new nodes red */
    root = addtree(root, newnode);
    balancetree(root, newnode);
  }

  if ( randpayloads )
    printtree(root, fout, NULL, minparamn);
  else if ( payloads == NULL )
    printtree(root, fout, "%s", minparamn);
  if ( payloads ) {
    while (fgets(payload, MAXPAYLOAD, payloads) != NULL) {
      npayloads++;
      for(int i=0; i<strlen(payload); i++){
          if(*(payload+i) == '\n'){
              *(payload+i)='\0';
              break;
          }
      }
      printtree(root, fout, payload, minparamn);
      minparamn = (minparamn) ? minparamn : 1;
    }
  }
  time_t end = time(NULL);
  fprintf(stderr, "%lu urls processeed in %d seconds\nGenerated %lu urls\nSkipped %lu malformed urls\n", lines, (end-begin), npayloads*lines, errors);
  return 0;
}
