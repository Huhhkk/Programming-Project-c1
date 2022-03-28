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
void lookupbook();
void borrowbook();
void returnbook();
void viewbook();
void addbook();
void printbook();
void addbook();

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

// BookList a;
// void init(){
//     a.list = (Book *)malloc(sizeof(Book));
//     a.list->next = NULL;
//     a.length = 0;
// }

BOOKS *head=NULL;
// [打印图书信息]
void printbook()
{
    BOOKS *pr=head;
    printf("*********************************Book information**********************************\n");
	if(pr == NULL)
	{
		printf("There are no books in the library\n");
	}
    while(pr != NULL)
	{		 
         printf("ID:%ld\tTITLE:%s\tAUTHOR:%s\tNUMBER:%d\tBORROWEDNUMBER:%d\n",pr->data.id,pr->data.name,pr->data.author,pr->data.count,pr->data.borrow);
	     pr = pr->next;
	}
    printf("*******************************************************************************\n");
}

// [注册新图书]
void addbook()
{
	BOOKS *p = NULL;
    BOOKS *pr = head;
    p=(BOOKS *)malloc(sizeof(BOOKS));
	if(p == NULL) exit(0);
	while(head != NULL && pr->next != NULL  )
	{   
	    pr = pr->next;
	}
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
	while(1){
	    printf("please enter ID(range:0~999999):\n");
	    scanf("%ld",&pr->data.id);
		getchar();
        if(!(pr->data.id >= 0 && pr->data.id <= 999999)){
            printf("Illegal input\n");
            fflush(stdin);
            continue;			
		}
        printf("please enter TITLE(length:0~19):\n");
		scanf("%s",pr->data.name);
		if(strlen(pr->data.name) > 20){
            printf("Illegal input!!\n");
            fflush(stdin);
            continue;
		}
     	printf("please enter AUTHOR(length:0~19):\n");
		scanf("%s",pr->data.author);
		if(strlen(pr->data.author) > 20){
            printf("Illegal input\n");
            fflush(stdin);
            continue;
		}
    	printf("please enter STOCK(num:0~99):\n");
	    scanf("%d",&pr->data.count);
		getchar();
	    if(!(pr->data.count >= 0 && pr->data.count <= 99)){
            printf("Illegal input\n");
            fflush(stdin);
            continue;
        }
     	pr->data.borrow=0;
		if(pr->data.borrow == 0){
			printf("DONE!!\n");
			return;
		}
		free(p);
	}
}

void main1(){
	FILE *fp;
    printf("\n****************************Welcome to the reader operation page****************************\n");
	printf("^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~\n"); 
    printf("\t\t\t  1:Lookup books\n\t\t\t  2:Borrow books\n\t\t\t  3:Return books\n\t\t\t  4:View the state of the books\n\t\t\t  0:Return to the previous menu\n");
	printf("Please select:\n");
	printf("^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~\n"); 
	int num;
	scanf("%d", &num);
	if (num == 1 || num == 2 || num == 3 || num == 4 || num == 0)
	{
		switch(num){
        case 1:
            lookupbook();
            main1();
        case 2:
            borrowbook();
            store_books(fp);
            main1();
        case 3:
            returnbook();
            store_books(fp);
            main1();
		case 4:
            viewbook();
            main1();
        case 0:
            Login();
        default:
            break;
    }
	} else{
		printf("Invalid enter!!");
		Login();
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
        	Login();
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
//以二进制的格式将链表读入txt文件
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


// [查找图书]
void lookupbook()
{
	int choice;
	BOOKS *pr=head;
	char name[20],author[20];
	if(pr == NULL)
	{
		printf("There is no book in the library\n");
        return;
	}
	printf("Please select how to find books:\n1:Search by book name\n2:Find by author name\n0:Exit\n");
	scanf("%d",&choice);
    switch(choice){
        case 1:
			printf("Please enter the name of the book you want to find\n");
			scanf("%s",name);
		    if(strlen(name) > 20){
                printf("Illegal input\n");
                main1();
			}	
            printf("******************************Result********************************\n");
            while(pr != NULL)
			{
				if(strcmp(pr->data.name,name) == 0){
                     printf("ID:%ld\tTITLE:%s\tAUTHOR:%s\tTOTAL BOOK STOCK:%d\tLENDING QUANTITY:%d\n",pr->data.id,pr->data.name,pr->data.author,pr->data.count,pr->data.borrow);	                
				}
			    pr = pr->next;
			}
            printf("********************************************************************************\n");
            break;
        case 2:
            printf("Please enter the author name you want to find\n");
			scanf("%s",author);
		    if(strlen(author) > 20){
                printf("Illegal input\n");
                return;
			}	
            printf("******************************Result********************************\n");
            while(pr != NULL)
			{
				if(strcmp(pr->data.author,author) == 0){
                     printf("ID:%ld\tTITLE:%s\tAUTHOR:%s\tTOTAL BOOK STOCK:%d\tLENDING QUANTITY:%d\n",pr->data.id,pr->data.name,pr->data.author,pr->data.count,pr->data.borrow);
				}
			    pr = pr->next;
			}
            printf("********************************************************************************\n");
            break;
        case 0:
			main1();
			break;
        default:
			printf("Illegal input\n");
            break;
    }
}

// [借阅图书]
void borrowbook()
{
	long id;
	int num,have;
	BOOKS *pr = head;
	if(pr == NULL)
	{
		printf("There are no books in the library\n");
        return;
	}
	printf("Please enter the ID of the book you want to borrow:\n");
	scanf("%ld",&id);
	if(!(id >= 0 && id <= 999999)){
         printf("Illegal input\n");
         return;
    }
	while(pr->next != NULL){
		if(pr->data.id == id){
			if(pr->data.borrow >= pr->data.count){
				printf("Sorry, the book has been borrowed\n");	
                return;
			}else{
				break;
			}          
		}else{
			if(pr == NULL){
				printf("The library doesn't have this book\n");
                return;
			}else{
					pr = pr->next;
			}
		}
	}
	printf("Please enter the number of books to borrow:\n");
	scanf("%d",&num);
	have = (pr->data.count)-(pr->data.borrow);
	if(num > have){
		printf("Sorry, there are not enough books in the library at present\n");
		return;
	}
	pr->data.borrow += num;
	printf("Borrowing succeeded\n");
}

// [归还图书]
void returnbook()
{
	long id;
	int num;
	BOOKS *pr = head;
	if(pr == NULL)
	{
		printf("There are no books in the library\n");
        return;
	}
	printf("Please enter the ID of the book you want to return:\n");
	scanf("%ld",&id);
	if(!(id >= 0 && id <= 999999)){
         printf("Illegal input\n");
         return;
    }
	while(1){
		if(pr->data.id == id){
			if(pr->data.borrow == 0){
				printf("You didn't borrow this book\n");
                return;
			}else{
				break;
			}          
		}
		else if(pr->next == NULL){
			printf("There is no such book which ID is %ld!! (&!&)\n",id);
            return;
		}
		pr = pr->next;
	}
	printf("Please enter the number of books returned:\n");
	scanf("%d",&num);
	if(num > pr->data.borrow){
		printf("Sorry, you returned more books than you borrowed\n");
		return;
	}
	pr->data.borrow -= num;
	printf("Return successful\n");
}

// [查看已借阅情况]
void viewbook()
{
	BOOKS *pr=head;
	if(pr == NULL)
	{
		printf("There are no books in the library\n");
        return;
	}
    printf("*******************************Borrowed book information*******************************\n");
    while(pr != NULL)
	{	
		 if(pr->data.borrow > 0){
             printf("ID:%ld\tTITLE:%s\tAUTHOR:%s\tTOTAL BOOK STOCK:%d\tLENDING QUANTITY:%d\n",pr->data.id,pr->data.name,pr->data.author,pr->data.count,pr->data.borrow);
		 }
		 pr = pr->next;
	}
    printf("*******************************************************************************\n");
}


// [注销现存图书]
void delbook(){
	long delid;
	BOOKS *pr = head,*p = head;
	if(head == NULL){
		printf("There are no books in the library\n");
        return;
	}
	printf("Please enter the book ID you want to delete:");
	scanf("%ld",&delid);
	if(!(delid >= 0 && delid <= 999999)){
        printf("Illegal input\n");
		return;
    }
	while(delid != p->data.id && p->next != NULL){
		pr = p;
		p = p->next;
	}
	if(delid == p->data.id){
		if(p == head){
			head = p->next;
		}else{
			pr->next = p->next;
		}
		free(p);
		printf("Successfully delete the book whose ID is %ld\n",delid);
	}else{
		printf("There is no such book whose ID is %ld!! (&!&)\n",delid);
	}
}


