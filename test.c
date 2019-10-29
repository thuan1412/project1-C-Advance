#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void menu();

void search(char prefix[30]) {
    // btpos(complete_tree, ZSTART);
  	int value;
    printf("%s\n", prefix);
    // fflush(stdin);
}

int main() {
    int choice, t;
    
    do {
      	char prefix[30];
        menu();
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        // if (choice < 0 || choice > 5) { 
        //     printf("%d\n", choice);
        //     exit(0);
        // }
        switch (choice) {
            case 1:
                printf("Option 1\n");
                gets(prefix);                
                break;
            case 2:
                printf("%d\n", choice);
            	printf("Enter word: ");
                gets(prefix);
                // printf("a: ");
                // scanf("%d%*c", &t);
                // search(prefix);
                break;
            default:
                printf("????");
                break;
        }
    } while (choice!=4);
}

void menu() {
    printf("\n------------------------\n");
    printf("1. Add node.\n");
    printf("2. Search key.\n");
    printf("3. Delete node.\n");
    printf("4. Suggest search\n");
    printf("------------------------\n");
}