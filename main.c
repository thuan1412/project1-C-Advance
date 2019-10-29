#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "btree.h"
#include <termios.h>

static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  new = old; //make new settings same as old settings
  new.c_lflag &= ~ICANON; //disable buffered i/o
  new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &new); //apply terminal io settings
}
 
/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}
 
/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}
 
/* 
Read 1 character without echo 
getch() function definition.
*/
char getch(void) 
{
  return getch_(0);
}
 
/* 
Read 1 character with echo 
getche() function definition.
*/
char getche(void) 
{
  return getch_(1);
}

void clearInput(int n)
{
    int i = 0;
    while (i < n)
    {
        putchar('\b');
        printf("%c[0K", 27);
        i++;
    }
}

char c;
const char * get_prefix() {
  	static char word[30];
	int i=0;
	char c;
	do {
		c = getch();	
		if (c=='\t' | c=='\n') {
			return word;
		}
		word[i] = c;
		printf("%c", c);
		if (c==127) {
			putchar('\b');
			word[--i] = '\0';
			printf("%c[0K", 27);
		} else 
			i++;
	} while (c!='\t' | c!='\n');
  	word[i-1]='\0';
	return word;
}

void menu();

int complete(BTA *complete_tree) {
    btpos(complete_tree, ZSTART);
	// char c;
  	char prefix[30];
  	// int i=0, j=0;
  	int value;
    char start[30], end[30];
  	// int n_words = 0;
  	printf("Enter word: ");
    strcpy(prefix, get_prefix());
    // fgets(prefix, 100, stdin);
    // prefix[strlen(prefix) - 1] = '\0';

    strcpy(start, prefix);
    strcpy(end, start);
    end[strlen(end) -1] = start[strlen(end)-1] + 1;      

    int check = bfndky(complete_tree, prefix, &value);
    // printf("%d - %d - %s - %s\n", strncmp(start, prefix, strlen(start)), check, start, prefix);
    int count = 0;

    if (check!=0 && strncmp(start, prefix, strlen(start))==0) {
        printf("\nNo word start with: %s", start);
        return 0;
    }
    while (strncmp(start, prefix, strlen(start)) == 0 ) {
        count = 0;
        do {
            check = bnxtky(complete_tree, prefix, &value);
            printf("%s\n", prefix);
            count++;
        } while (strcmp(prefix, end) <0  & count<5);
        if (count < 5) {
            printf("No more word, press any key to exit option\n");
        } else 
            printf("Enter tab for continute. Enter any key to exit\n");
        if (getch()!='\t') {
            return 0;
        }
    }
}

int main() {
    int choice;
    int *find;
    char value[20];
    char key[20];
    char* names = "pj1.db";
    int size_mean_rev, size_serise_word_rev;
    
    btinit();
    char filename[30] = "./data/auto-complete.db";
    BTA* complete_tree = btopn(filename, 0, 1);

    while (choice!=6)    {
        menu();
        printf("Enter choice: ");
        scanf("%d%*c", &choice);
        switch (choice) {
        case 1:
            // printf("Enter keys:  ");
            // fgets(key, 20, stdin);
            // printf("%s", key);
            // printf("Enter values:  ");
            // fgets(value, 20, stdin);
            // printf("%s", value);
            // btins(btree, key, value,20);
            printf("Option 1\n");
            break;
        case 4:
            complete(complete_tree);
            break;
        default:
            break;
        }
    }
    
}

void menu() {
    printf("\n------------------------\n");
    printf("1. Add node.\n");
    printf("2. Search key.\n");
    printf("3. Delete node.\n");
    printf("4. Auto-complete.\n");
    printf("5. Suggest search\n");
    printf("6. Exit\n");
    printf("------------------------\n");
}