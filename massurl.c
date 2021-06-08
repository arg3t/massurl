/*
 * massurl.c
 *
 * Created by Yigit Colakoglu on 07/06/2021.
 * Copyright yigit@yigitcolakoglu.com. 2021. All rights reserved.
 */

#include <stdio.h>
#include "urlparse.h"
#include "tree.h"
#include "strings.h"
#define MAXURL 100000

static void usage(void){
    fputs("\n", stderr);
}

enum outformat{ PLAIN = 01 };

int main(int argc, char *argv[]) {

    FILE *fin = stdin, *fout = stdout;
    char *param, urlstr[MAXURL];

    while(--argc > 0){
        param= *++argv;
        if(param[0] == '-'){
            param++;
            argc--;
            switch(*param){
                case 'o':
                  if ((fout = fopen(*++argv, "w")) == NULL) {
                    fprintf(stderr, "Can't open output file for writing.\n");
                    return 1;
                  }
                  if(ferror(fout)){
                    fprintf(stderr, "Can't open output file for writing.\n");
                    return 1;
                  }
                break;
                default:
                  fprintf(stderr, "Parameter -%c does not exist!", *param);
            }
        }else{
            if((fin = fopen(param, "r")) == NULL){
                fprintf(stderr, "Can't open file %s\n", param);
                return 1;
            }
        }
    }

    TreeNode *urltree = treealloc();
    URL *url;
    while(fgets(urlstr, MAXURL, fin) != NULL){
        if((url = parseurl(urlstr)) == NULL){
            fprintf(stderr, "Malformed URL %s", urlstr);
            continue;
        }
        if(urltree->path == NULL){
            urltree->path = url->base;
            urltree->params = url->params;
        }else{
            urltree = addtree(urltree, url);
        }
    }
    printtree(urltree, fout);
    return 0;
}
