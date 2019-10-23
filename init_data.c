#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "btree.h"

void create_autocomplete_tree() {
    char *file_name = "auto-complete.db";
    int i;
    btinit();
    BTA *complete_tree;
    complete_tree = btopn(file_name, 0, 1);
    if (complete_tree == NULL) {
        complete_tree = btcrt(file_name, 0, 1);
    } 

    FILE *f = fopen("/usr/share/dict/words","r");
    // FILE *f = fopen("test2.txt", "r");
    char word[50];
    char temp_value[600]="";
    int rsize;

    while (!feof(f)){
        fgets(word, 50, f);
        word[strlen(word)-1]= '\0';
        // printf("%ld\n", strlen(word));
        int len = strlen(word);
        for (i=1; i < len +1; i++) {
            char key[30]="";
            strncpy(key, word, i);
            // printf("%s\n", key);
            if (btsel(complete_tree, key, temp_value, 200, &rsize) != 0) {
                int check = btins(complete_tree, key, word, 30);
                // printf("Insert key %10s  - Value %15s. Status: %d\n", key, word, check);
            } else {
                strcpy(temp_value, "");
                int check = btsel(complete_tree, key, temp_value, sizeof(temp_value), &rsize);
                if (strlen(temp_value) < 500) {
                strcat(temp_value, "\n");
                strcat(temp_value, word);
                btupd(complete_tree, key, temp_value, strlen(temp_value) + 1);
                }
                // printf("Update %10s - value %15s - word %10s - status %d\n", key, temp_value, word, check);
                // printf("%s - %s\n", key,temp_value);
            }
        }
    }
    fclose(f);
    btcls(complete_tree);
}


int main() {
    create_autocomplete_tree();
    char *file_name = "auto-complete.db";
    
    BTA *complete_tree;
    complete_tree = btopn(file_name, 0, 1);
    
    if (complete_tree == NULL) {
        printf("created\n");
        complete_tree = btcrt(file_name, 0, 1);
    } 
    
    while (1) {
        char prefix[100], completion[100];
        int rsize;
        printf("Enter prefix: ");
        fgets(prefix,30, stdin);
        prefix[strlen(prefix) - 1] = '\0';
        if  (strcmp(prefix, "q")==0) {
        // remove(file_name);  
            exit(1);
        }
        int check = btsel(complete_tree, prefix, completion, 300, &rsize);
        printf("%s\n", prefix);
        // printf("%s- %d - %s\n", prefix, check, completion);
        if (!check) 
            printf("%s %d\n", completion, rsize);
        else printf("Does not exist this key: %d\n", check);
    }
    btcls(complete_tree);
}