#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "btree.h"

void create_soundexz_tree() {
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

void create_autocomplete_tree() {
    char *file_name = "./data/auto-complete.db";
    btinit();
    
    BTA *complete_tree;
    complete_tree = btopn(file_name, 0, 1);
    
    if (complete_tree == NULL) {
        printf("created\n");
        complete_tree = btcrt(file_name, 0, 1);
    } 
    FILE *f = fopen("/usr/share/dict/words","r");
    char word[50];
    while (!feof(f)){
        fgets(word, 50, f);
        word[strlen(word)-1]= '\0';
        binsky(complete_tree, word, 1);
    }
    fclose(f);
    btcls(complete_tree);

}

char *process_word(char word[50]) {
    int i=0;
    int l = strlen(word);
    while (isdigit(word[i]) || word[i]=='@' || word[i]=='-') {
        i++;
    }
    word = word+i;
    static char temp[30];
    strcpy(temp, "");
    for (i=0; i<l; i++) {
        if (word[i]=='/') {
            temp[i] = '\0';
            return temp;
        } else
        {
            temp[i] = word[i];
        }
    }
    return temp;
}

int main() {
    // create_autocomplete_tree();
    FILE *f = fopen("eng_vn_test.txt", "r");
    char temp[500], word[500];
    // char test[100] = "@a b c /'eibi:'si:/";
    // strcpy(word, process_word(test));
    // printf("%s\n", word);
    while (!feof(f)) {
        int check = 0;
        fgets(temp, 500, f);
        temp[strlen(temp) - 1] = '\0';
        if (temp[0]=='@') {

            strcpy(word, process_word(temp));
            printf("Word: %s\n", word);
        } else if (check==0) {
            printf("Mean: %s", temp);
            check=1;
        } else if (check==1)
        {
            printf("%s", temp);
        }
        
    }
    

    // int rsize;
    // while (1) {
    //     char key[50]="", value[100];
    //     // btpos(test, ZSTART);
    //     printf("Enter prefix: ");
    //     fgets(key, 30, stdin);
    //     key[strlen(key) - 1] = '\0';
    //     int len_key = strlen(key);
    //     char start[30], end[30];
    //     strcpy(start, key);
    //     strcpy(end, start);
    //     bfndky(test, key, &rsize);

    //     end[len_key-1] = start[len_key-1] + 1;
    //     if (strncmp(start, key, len_key) > 0) {
    //         printf("%s - %s - %s\n", start, key, end);
    //     }
    //     else {
    //         while (strcmp(key, end) < 0) {
    //         int check = bnxtky(test, key, &rsize);
    //         printf("%s\n", key);
    //         }
    //     }
    //     btpos(test, ZSTART);
    // }
    
    
    
    // while (1) {
    //     char prefix[100], completion[100];
    //     int rsize;
    //     printf("Enter prefix: ");
    //     fgets(prefix,30, stdin);
    //     prefix[strlen(prefix) - 1] = '\0';
    //     if  (strcmp(prefix, "q")==0) {
    //     // remove(file_name);  
    //         exit(1);
    //     }
    //     int check = btsel(complete_tree, prefix, completion, 300, &rsize);
    //     printf("%s\n", prefix);
    //     // printf("%s- %d - %s\n", prefix, check, completion);
    //     if (!check) 
    //         printf("%s %d\n", completion, rsize);
    //     else printf("Does not exist this key: %d\n", check);
    // }
    // btcls(complete_tree);
}