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
 
int main() {
    btinit();
    char filename[30] = "./data/auto-complete.db";
    BTA* complete_tree = btopn(filename, 0, 1);
    // if (complete_tree==NULL) {
    //     FILE *f = fopen("/usr/share/dict/words","r");
    //     complete_tree = btcrt(filename, 0, 0);
    //     char word[50];
    //     while (!feof(f)){
    //         fgets(word, 50, f);
    //         word[strlen(word)-1]= '\0';
    //         binsky(complete_tree, word, 1);
    //     }
    //     fclose(f);
    // }

    int rsize,
        i;
    while (1) {
        // set/reset the key value
        char key[50]="", value[100];
        // btpos(complete_tree, ZSTART);
        printf("Enter prefix: ");
        fgets(key, 30, stdin);
        if (getch())
        key[strlen(key) - 1] = '\0';
        int len_key = strlen(key);
        char start[30], end[30];
        strcpy(start, key);
        strcpy(end, start);
        int check = bfndky(complete_tree, key, &rsize);

        end[len_key-1] = start[len_key-1] + 1;
        if (strncmp(start, key, len_key) < 0) {
            printf("%s - %s - %s\n", start, key, end);
        }
        else {
            char c='c';
            while (strcmp(key, end) < 0 & (c = getch()) == '\t' ) {
            int check = bnxtky(complete_tree, key, &rsize);
            printf("%s\n", key);
            // c = getch();
            // if (c=='\t') {
            //     for (i=0 ; i<strlen(key) - strlen(start); i++) {
            //         printf("\b");
            //         printf("%c[0K", 27);
            //         }
            //     }
            }
        }
        btpos(complete_tree, ZSTART);
        printf("\n");

    }
}