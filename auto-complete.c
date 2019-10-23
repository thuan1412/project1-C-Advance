#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "btree.h"

int main() {
    btinit();
    char filename[30] = "complete.db";
    BTA* complete_tree = btopn(filename, 0, 1);
    if (complete_tree==NULL) {
        FILE *f = fopen("/usr/share/dict/words","r");
        complete_tree = btcrt(filename, 0, 0);
        char word[50];
        while (!feof(f)){
            fgets(word, 50, f);
            word[strlen(word)-1]= '\0';
            binsky(complete_tree, word, 1);
        }
        fclose(f);
    }

    int rsize;
    while (1) {
        // set/reset the key value
        char key[50]="", value[100];
        // btpos(complete_tree, ZSTART);
        printf("Enter prefix: ");
        fgets(key, 30, stdin);
        key[strlen(key) - 1] = '\0';
        int len_key = strlen(key);
        char start[30], end[30];
        strcpy(start, key);
        strcpy(end, start);
        bfndky(complete_tree, key, &rsize);

        end[len_key-1] = start[len_key-1] + 1;
        if (strncmp(start, key, len_key) > 0) {
            printf("%s - %s - %s\n", start, key, end);
        }
        else {
            while (strcmp(key, end) < 0) {
            int check = bnxtky(complete_tree, key, &rsize);
            printf("%s\n", key);
            }
        }
        btpos(complete_tree, ZSTART);
    }
}