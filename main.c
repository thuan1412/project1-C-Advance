#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

void menu();


int main() {
    int choice;
    int *find;
    char value[20];
    char key[20];
    char* names = "pj1.db";
    int size_mean_rev, size_serise_word_rev;
    
    BTA *btree;
    btree = btopn(names, 0, 1);
    if (btree == NULL) {
        btree = btcrt(names, 0, 1);
    }
    btdups(btree, 1);
    while (choice!=4)    {
        menu();

        printf("Enter choice: ");
        scanf("%d%*c", &choice);
        switch (choice) {
        case 1:
            printf("Enter keys:  ");
            fgets(key, 20, stdin);
            printf("%s", key);
            printf("Enter values:  ");
            fgets(value, 20, stdin);
            printf("%s", value);
            btins(btree, key, value,20);
            break;
        case 2:
            printf("Enter keys:  ");
            fgets(key, 20, stdin);
            btseln(btree, key, value, sizeof(value), &size_mean_rev);
            printf("%s", value);
        default:
            break;
        }
    }
    
}

void menu() {
    printf("------------------------\n");
    printf("1. Add node.\n");
    printf("2. Search key.\n");
    printf("3. Delete node.\n");
    printf("4. Auto-complete search\n");
    printf("5. Suggest search\n");
    printf("------------------------\n");
}