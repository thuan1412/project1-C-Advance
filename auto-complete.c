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
const char * get_prefix() {
  	static char word[30];
	int i=0;
	char c;
	do {
		c = getch();	
		if (c=='\t') {
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
	} while (c!='\t');
  	word[i-1]='\0';
	return word;
}

int main() {
    btinit();
    char filename[30] = "./data/auto-complete.db";
    BTA* complete_tree = btopn(filename, 0, 1);

    int rsize,
        i;
    while (1) {
        // set the prefix value
        char prefix[50]="", value[100];
        printf("Enter prefix: ");
		strcpy(prefix, get_prefix());
		// printf("%s", prefix);
        int len_prefix = strlen(prefix);
        char start[30], end[30];
        strcpy(start, prefix);
        strcpy(end, start);
        int check = bfndky(complete_tree, prefix, &rsize);

        end[len_prefix-1] = start[len_prefix-1] + 1;
		char c;
		if (strncmp(start, prefix, len_prefix) >= 0) {
            do  {
				int check = bnxtky(complete_tree, prefix, &rsize);
				if (strncmp(prefix, start, len_prefix)==0) {
					printf("%s\n", prefix);
				}
				
            } while (strcmp(prefix, end) < 0 & ((c = getch()) =='\t' | c =='\n'));
        }
        btpos(complete_tree, ZSTART);
        printf("\n---------------------------------\n");
    }
}