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
		if (c=='\t' || c=='\n') {
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
	} while (c!='\t' || c!='\n');
  	word[i-1]='\0';
	return word;
}

void menu();

int complete(BTA *complete_tree) {
    btpos(complete_tree, ZSTART);
	// char c;
  	char prefix[30];
    strcpy(prefix, "");
  	// int i=0, j=0;
  	int value;
    char start[30], end[30];
  	// int n_words = 0;
  	printf("Enter word: ");
    int i=0,j=0;
    while (1)
    {
        char c = getch();
        if ((c != '\t') && (c != '\n') && (c != 27) && (c != 127))
        {
            prefix[i++] = c;
            putchar(c);
            j++;
        }
        if (c == 127 && j > 0)
        {
            putchar('\b');
            printf("%c[0K", 27);
            prefix[i--] = '\0';
            // j--;
        } if (c=='\t') break;
    }
    prefix[i] = '\0';
    printf("\n");
    // printf(" %ld  %s\n", strlen(prefix), prefix);

    strcpy(start, prefix);
    strcpy(end, start);
    end[strlen(end) -1] = start[strlen(end)-1] + 1;      

    int check = bfndky(complete_tree, prefix, &value);
    // printf("%d - %d - %s - %s\n", strncmp(start, prefix, strlen(start)), check, start, prefix);
    int count = 0;

    // if (check!=0 && strncmp(start, prefix, strlen(start))==0) {
    //     printf("\nNo word start with: %s %s \n", start, prefix);
    //     return 0;
    // }
    do  {
        count = 0;
        do {
            check = bnxtky(complete_tree, prefix, &value);
            if (strncmp(start, prefix, strlen(start))!=0) {
                printf("\nNo word start with: %s\n", start);
                return 0;
            }
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
    } while (strncmp(start, prefix, strlen(start)) == 0 );
}

void search(BTA *word_tree) {
    char word[100], mean[5000];
    int rsize;
    strcpy(word, "");
    strcpy(mean, "");
    printf("Enter word: ");
    fgets(word,30, stdin);
    word[strlen(word) - 1] = '\0';

    int check = btsel(word_tree, word, mean, 5000, &rsize);
    // printf("%s\n", completion);
    // printf("%s- %d - %s\n", word, check, mean);
    if (!check) 
        printf("%s\n", mean);
    else printf("Does not exist this key:%s \nError:%d \n", word, check);
    btpos(word_tree, ZSTART);
}

//soundex search
static char code[128] = {0};
void add_code(char *string, int character)
{
    while (*string)
    {
        code[(int)*string] = code[0x20 ^ (int)*string] = character;
        string++;
    }
}

void soundexInit()
{
    char *formatSoundex[] =
        {"AEIOU", "", "BFPV", "CGJKQSXZ", "DT", "L", "MN", "R", 0};
    int i;
    for (i = 0; formatSoundex[i]; i++)
    {
        add_code(formatSoundex[i], i - 1);
    }
}

char *getSoundex(char *string)
{
    static char soundex[5];
    int character, prev, i;

    soundex[0] = soundex[4] = 0;
    if (!string || !*string)
        return soundex;

    soundex[0] = *string++;

    prev = code[(int)soundex[0]];
    for (i = 1; *string && i < 4; string++)
    {
        if ((character = code[(int)*string]) == prev)
            continue;

        if (character == -1)
            prev = 0;
        else if (character > 0)
        {
            soundex[i++] = character + '0';
            prev = character;
        }
    }
    while (i < 4)
        soundex[i++] = '0';
    return soundex;
}

void delete(BTA * complete_tree, BTA *word_tree){
    btpos(complete_tree, ZSTART);
    btpos(word_tree, ZEND);
    
    char word[30];
    int i, j, rsize;
    printf("Input the delete word: ");
    fgets(word,30,stdin);
    word[strlen(word)-1] ='\0';
    // for (i=0;i<strlen(word);i++){
    //     word[i]=tolower(word[i]);
    // }
    i = btdel(complete_tree, word);
    j = btdel(word_tree, word);

    if(i==0 || j ==0){
        printf("Delete \'%s\' succeed \n", word);
    }
    else printf("Does not exist \'%s\' in dictionary!\n %d",word,j );
}

void addNode(BTA* complete_tree, BTA *word_tree){
    char word[40];
    char mean[500];
    int i,rsize;
    printf("Enter new word:");
    fgets(word, 40, stdin);
	word[strlen(word)-1] = '\0';
    
	if(btsel(word_tree,word,mean,500,&rsize)==0){
		printf("The word \'%s\' has been existed on word_tree!\n",word);		
	} else if (btsel(complete_tree,word,mean,500,&rsize)==0) {
		printf("The word \'%s\' has been existed on complete_tree!\n",word);		
	} else {
		printf("Enter word means:");
		fgets(mean,500,stdin);
        mean[strlen(mean)-1] = '\0';
		btins(word_tree,word,mean,500);
        binsky(complete_tree, word, 1);
		printf("The word \'%s\' has been added!\n",word);
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
    char complete_fname[30] = "./data/auto-complete.db";
    BTA* complete_tree = btopn(complete_fname, 0, 1);
    
    char word_mean_fname[30] = "./data/word-mean.db";
    BTA *word_tree = btopn(word_mean_fname, 0, 1);

    char soundex_fname[30]  = "./data/soundex.db";
    BTA *soundex_tree = btopn(soundex_fname, 0, 1);

    while (choice!=6)    {
        menu();
        printf("Enter choice: ");
        scanf("%d%*c", &choice);
        switch (choice) {
        case 1:
            addNode(complete_tree, word_tree);
            break;
        case 2:
            search(word_tree);
            break;
        case 3:
            delete(complete_tree, word_tree);
            break;
        case 4:
            complete(complete_tree);
            break;
        case 5:
            soundexInit();
            btpos(soundex_tree, ZSTART);
            char keyWord[20];
            int value;
            printf("Enter key word to search soundex: ");
            gets(keyWord);
            char *soundexKeyWord = getSoundex(keyWord);
            char result[200000];
            if (btsel(soundex_tree, getSoundex(keyWord), result, sizeof(result), &value))
            {
                printf("no suggestions ! \n");
            }
            else
            {
                printf("this suggestion is: \n");
                printf("%s \n", result);
            }
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