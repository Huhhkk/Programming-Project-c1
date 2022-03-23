#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include "Interface.h"
#include "book_management.h"
#define LEN sizeof(struct book)
#define LEN1 sizeof(struct reader)
#define LEN2 sizeof(struct account)

int store_books(FILE *file);
int load_books(FILE *file);
int add_book(Book book);
int remove_book(Book book);
BookList find_book_by_title (const char *title);
BookList find_book_by_author (const char *author);
BookList find_book_by_year (unsigned int year);
void main1();
char choice();


// typedef struct _Book {
// 	    unsigned int id; //Book ID
// 		char *title; //book title
// 		char *authors; //comma separated list of authors
// 		unsigned int year; // year of publication
// 		unsigned int copies; //number of copies the library has
// 		struct _Book *next; //pointer to the next book element
// }Book;

// typedef struct _BookList {
// 	 Book* list; // pointer to a list of struct Book.
// 	 unsigned int length; // number of elements in the (Book*) List 
// }BookList;


typedef struct book{
	long id;                 //图书编号
    char name[20];       //图书名
    char author[20];     //图书作者
    int count;               //图书存数
    int borrow;              //借出数量
}BOOK;
typedef struct books{
	BOOK data;
    struct books *next;
}BOOKS;
BOOKS *head=NULL;



char choice(){
    char c, flag;
    int i;   
    while(1){
        for(i = 0; (c = getchar()) != '\n'; flag = c, ++i);
        if(i == 1){
            if(flag == '1' || flag == '2' || flag == '3' || flag == '4' || flag == '5' || flag == '6' || flag == '0'){
                return flag;
            }
        }else if(i == 0){
            Login();
        }
        printf("Invalid input, please re-enter");          
    }    
    return '\0';
}


void main1(){
    FILE *fp;
    int load_books(fp);
    printf("\n****************************Welcome to the reader operation page****************************\n");
	printf("^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~\n"); 
    printf("\t\t\t☆  1:Find books\n\t\t\t☆  2:Borrow books\n\t\t\t☆  3:Return books\n\t\t\t☆  4:View borrowed information\n\t\t\t☆  5:保存图书信息\n\t\t\t☆  6:载入图书信息\n\t\t\t☆  0:返回主页\n");
	printf("Please select:\n");
	printf("^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~\n"); 
    switch(choice()){
        case '1':
            lookupbook();
            break;
        case '2':
            borrowbook();
            break;
        case '3':
            returnbook();
            break;
		case '4':
            viewbook();
            break;
		case '5':
            save();
            break;
		case '6':
            load();
            break;
        case '0':
            return 0;
        default:
            break;
    }
}

int load_books(FILE *file){
    BOOKS *p;
    BOOKS *pr;
    pr=head;
    if((file = fopen("library.txt","r")) == NULL)
	{
		printf("Failure to open file!\n");
        exit(1);
	}
	while(!feof(file))
	{
		p=(BOOKS *)malloc(sizeof(BOOKS)); 
		if(p == NULL)
		{
			printf("No enough memory!\n");
        	return;
		}
        if(fread(p,sizeof(BOOKS),1,file) != 1){
			break;
        }else{
			if (head == NULL)
			{
				head = p;
				pr = p;
		        pr->next = NULL;
			}
        	else
			{
				pr->next = p;
	        	pr = p;
	        	pr->next = NULL;
			}
		}
	}
    fclose(file);
	return 0;
}

int store_books(FILE *file){
    BOOKS *pr = head;
	if((file = fopen("library.txt","w")) == NULL)
	{
		printf("Failure to open file!\n");
        exit(1);
	}
    while(pr)
	{
		fwrite(pr,sizeof(BOOKS),1,file);
        pr=pr->next;
	}
	fclose(file);
	return 0;
}