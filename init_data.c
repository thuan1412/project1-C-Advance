#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "btree.h"


void create_soundexz_tree() {
    char *file_name = "auto-complete.db";
    int i;
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
    // btinit();
    
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
    int check = 0;
    for (i=0; i<l-1; i++) {
        if (word[i+1]=='/') {
            temp[i] = '\0';
            check = 1;
            return temp;
        } else
        {
            temp[i] = word[i];
        }
    }
    return word;
}

void create_word_mean_tree() {
    FILE *f = fopen("ENG_VN.txt", "r");
    FILE *f_word = fopen("words.txt", "w");

    char temp[500], word[500];
    char *file_name = "./data/word-mean.db";
    // btinit();
    
    BTA *word_tree;
    word_tree = btopn(file_name, 0, 1);
    
    if (word_tree == NULL) {
        printf("created\n");
        word_tree = btcrt(file_name, 0, 1);
    }   
    int check = 0;
    int first_word = 1;
    while (!feof(f)) {
        strcpy(temp, "");

        fgets(temp, 500, f);
        char mean[5000];

        temp[strlen(temp) - 1] = '\0';
        if (temp[0]=='@') {
            check = 0;
            if (!first_word) {
                // printf("Mean: \n %s", mean);
                check = btins(word_tree, word, mean, 5000);

                if (check) {
                } else {
                    // printf("%s\n", word);
                    fputs(word, f_word);
                    fputs("\n", f_word);
                }
            }        
            // printf("------------------------------------\n");
            strcpy(word, "");
            strcpy(word, process_word(temp));
            strcpy(mean,"");    
            // word
            // printf("Word: %s\n", word);
            
        } else if (check==0) {
            strcat(mean, temp);
            strcat(mean, "\n");
            // printf("Mean: %s\n", temp);
            check=1;
            first_word=0;
        } else if (check==1 && temp[0]=='-')
        {
            strcat(mean, temp);
            strcat(mean, "\n");
        } 
    }
    fclose(f_word);
    fclose(f);
    btcls(word_tree);
}

int main() {
    btinit();
    create_autocomplete_tree();
    // FILE *f = fopen("ENG_VN.txt", "r");
    // FILE *f_word = fopen("words.txt", "w");
    create_word_mean_tree();
    // char temp[500], word[500];
    // char *file_name = "./data/word-mean.db";
    
    // BTA *word_tree;
    // word_tree = btopn(file_name, 0, 1);
    
    // if (word_tree == NULL) {
    //     printf("created\n");
    //     word_tree = btcrt(file_name, 0, 1);
    // }   
    // int check = 0;
    // int first_word = 1;
    // while (!feof(f)) {
    //     strcpy(temp, "");

    //     fgets(temp, 500, f);
    //     char mean[5000];

    //     temp[strlen(temp) - 1] = '\0';
    //     if (temp[0]=='@') {
    //         check = 0;
    //         if (!first_word) {
    //             // printf("Mean: \n %s", mean);
    //             check = btins(word_tree, word, mean, 5000);

    //             if (check) {
    //                 printf("Error: %d\n%s\n%s\n", check, word, mean);
    //             } else {
    //                 // printf("%s\n", word);
    //                 fputs(word, f_word);
    //                 fputs("\n", f_word);
    //             }
    //         }        
    //         // printf("------------------------------------\n");
    //         strcpy(word, "");
    //         strcpy(word, process_word(temp));
    //         strcpy(mean,"");    
    //         // word
    //         // printf("Word: %s\n", word);
            
    //     } else if (check==0) {
    //         strcat(mean, temp);
    //         strcat(mean, "\n");
    //         // printf("Mean: %s\n", temp);
    //         check=1;
    //         first_word=0;
    //     } else if (check==1 && temp[0]=='-')
    //     {
    //         strcat(mean, temp);
    //         strcat(mean, "\n");
    //     } 
    //     // else  if (strcmp(temp, "")==0){
        //     // printf("Word: %s\n", word);
        //     // printf("Mean: \n %s", mean);
        //     check = btins(word_tree, word, mean, 5000);
            
        //     if (check) {
        //         printf("Error: %d\n%s\n%s\n", check, word, mean);
        //     } else {
        //         printf("%s\n", word);
        //         fputs(word, f_word);
        //         fputs("\n", f_word);
        //     }

        //     // printf("End %s1\n");
        //     // printf("%d\n", strcmp(temp, ""));
        // }
    // }
    // fclose(f_word);

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
    
    // int check = btsel(word_tree, "wash-out");
    // while (1) {
    //     char prefix[100], completion[5000];
    //     int rsize;
    //     strcpy(prefix, "");
    //     strcpy(completion, "");
    //     printf("Enter prefix: ");
    //     fgets(prefix,30, stdin);
    //     prefix[strlen(prefix) - 1] = '\0';

    //     int check = btsel(word_tree, prefix, completion, 5000, &rsize);
    //     // printf("%s\n", completion);
    //     // printf("%s- %d - %s\n", prefix, check, completion);
    //     if (!check) 
    //         printf("%s\n", completion);
    //     else printf("Does not exist this key: %d %s\n", check, prefix);
    //     btpos(word_tree, ZSTART);
    // }
    // // remove(file_name);
    // // fclose(f);
    // btcls(word_tree);
}