#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "btree.h"

int main() {
    char *file_name = "auto-complete.db";
    btinit();
    BTA *complete_tree;
    complete_tree = btopn(file_name, 0, 1);
    if (complete_tree == NULL) {
        complete_tree = btcrt(file_name, 0, 1);
    }

      // while (1) {
    //     char prefix[10], completion[500];
    //     int rsize;
    //     printf("Enter prefix: ");
    //     fgets(prefix,30, stdin);
    //     // prefix = "a";
    //     int check = btsel(complete_tree, prefix, completion, 30, &rsize);
    //     // printf("%s\n", completion);
    //     printf("%s- %d - %s\n", prefix, check, completion);
    // }
    
}