#include <termios.h>
#include <stdio.h>
#include <string.h> 

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
 
const char * get_prefix() {
  static char word[30];
	int i=0;
	char c;
	do {
		c = getch();
		word[i] = c;
    if (c!='\t')
		printf("%c", c);
		i++;
	} while (c!='\t');
	// printf("%s\n", word);  
  word[i-1]='\0';
	return word;
}

int main(void) {
  char prefix[30];
  strcpy(prefix, get_prefix());
  printf("%sa", prefix);
  return 0;
}