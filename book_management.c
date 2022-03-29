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
//int load_books(FILE *file, Book* books, BookList *theBook);
int add_book(Book book);
int load_books(FILE *file);
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

Book *head=NULL;
// [打印图书信息]
void printbook()
{
    Book *pr=head;
    printf("*********************************Book information**********************************\n");
	if(pr == NULL)
	{
		printf("There are no books in the library\n");
	}
    while(pr != NULL)
	{		 
         printf("ID:%ld\tTITLE:%s\tAUTHOR:%s\tYEAR OF PUBLICATION:%d\tNUMBER OF COPIES:%d\tLENDING QUANTITY:%d\n",pr->id,pr->title,pr->authors,pr->year,pr->copies,pr->borrow);	
	     pr = pr->next;
	}
    printf("*******************************************************************************\n");
}

// [注册新图书]
void addbook()
{
	Book *p = NULL;
    Book *pr = head;   
    p=(Book *)malloc(sizeof(Book));
	//p->title = (char *)malloc(sizeof(char));
	//->authors = (char *)malloc(sizeof(char));
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
	    scanf("%ld",&pr->id);
		getchar();
        if(!(pr->id >= 0 && pr->id <= 999999)){
            printf("Illegal input\n");
            //fflush(stdin);
            continue;			
		}

        printf("please enter TITLE(length:0~19):\n");
		//pr->title = (char *)malloc(sizeof(char));
		scanf("%s",pr->title);
		getchar();
		if(strlen(pr->title) > 20){
            printf("Illegal input!!\n");
            //fflush(stdin);
            continue;
		}

     	printf("please enter AUTHOR(length:0~19):\n");
		//pr->authors = (char *)malloc(sizeof(char));
		scanf("%s",pr->authors);
		getchar();
		if(strlen(pr->authors) > 20){
            printf("Illegal input\n");
            //fflush(stdin);
            continue;
		}

		printf("please enter the year of publication(num:0~2022):\n");
	    scanf("%u",&pr->year);
		getchar();
	    if(!(pr->year >= 0 && pr->year <= 2022)){
            printf("Illegal input\n");
            //fflush(stdin);
            continue;
        }
		
    	printf("please enter number of copies the library has(num:0~99):\n");
	    scanf("%d",&pr->copies);
		getchar();
	    if(!(pr->copies >= 0 && pr->copies <= 99)){
            printf("Illegal input\n");
            //fflush(stdin);
            continue;
        }
     	pr->borrow=0;
		if(pr->borrow == 0){
			printf("ADD SUCCESSFULLY!!\n");
			return;
		}
		free(p);
		//free(p->title);
		//free(p->authors);
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
// //初始化链表
// Book* initList(){
//     Book* L = (Book*)malloc(sizeof(Book));
//     L -> next = NULL;
//     return L;
// }
// //尾插法
// void tailInsert(Book* L){
//     Book* node = L;
//     while(node->next != NULL){
//         node = node -> next;
//     }
//     Book* n = (Book*)malloc(sizeof(Book));
//     n -> next = NULL;
//     node -> next = n;
// }
// //尾删除
// int tailDelete(Book* L, int length){
// 	BookList a;
//     a.list = L;
//     Book* node = L -> next;
//     while(node){
//         if(a.length == length){
//             a.list->next = node->next;
//             free(node);
//             return 1;
//         }
//         a.list = node;
//         node = node->next;
//     }
//     return 0;
// }

// //加载图书
// int load_books(FILE *file, Book* books, BookList *theBook){
//     file = fopen("library.txt", "r");
//     if(file){
// 		Book *tmp;
// 		while (1)
// 		{
// 			tmp = books;
// 			tailInsert(books);
// 			while (tmp->next != NULL)
// 			{
// 				tmp = tmp->next;
// 			}
// 			if (fscanf(file, "%u %s %s %u %u %u", &tmp->id, tmp->title, tmp->authors, &tmp->year, &tmp->copies, &tmp->borrow) == EOF)
// 			{
// 				break;
// 			}else{
// 				theBook->length ++;
// 			}
// 		}
// 		theBook->length ++;
// 		tailDelete(books, theBook->length);
// 		theBook->length --;
// 		return 0;
// 	}else{
// 		printf("The file does not exist\n");
// 		return 0;
// 	}
// }
// //将链表读入txt文件
// int store_books(FILE *file){
//     Book *pr = head;
// 	if((file = fopen("library.txt","w")) == NULL)
// 	{
// 		printf("Failure to open file!\n");
//         exit(1);
// 	}
//     while(pr)
// 	{
// 		fprintf(file,"%d ",pr->id);
//         fprintf(file,"%s ",pr->title);
//         fprintf(file,"%s ",pr->authors);
// 		fprintf(file,"%d ",pr->year);
// 		fprintf(file,"%d ",pr->copies);
// 		fprintf(file,"%d ",pr->borrow);
//         fprintf(file,"%s","\n");//换行
//         pr=pr->next;
// 	}
// 	fclose(file);
// 	return 0;
// }
int load_books(FILE *file){
    Book *p;
    Book *pr;
    pr=head;
    if((file = fopen("library.txt","r")) == NULL)
	{
		printf("Failure to open file!\n");
        exit(1);
	}
	while(!feof(file))
	{
		p=(Book *)malloc(sizeof(Book)); 
		//p->authors = (char *)malloc(sizeof(char));
		//p->title = (char *)malloc(sizeof(char));
		if(p == NULL)
		{
			printf("No enough memory!\n");
        	Login();
		}
        if(fread(p,sizeof(Book),1,file) != 1){
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
    Book *pr = head;
	if((file = fopen("library.txt","w")) == NULL)
	{
		printf("Failure to open file!\n");
        exit(1);
	}
    while(pr)
	{
		fwrite(pr,sizeof(Book),1,file);
        pr=pr->next;
	}
	fclose(file);
	return 0;
}



// [查找图书]
void lookupbook()
{
	int choice;
	Book *pr=head;
	char name[20],author[20];
	unsigned int year1;
	if(pr == NULL)
	{
		printf("There is no book in the library\n");
        return;
	}
	printf("Please select how to find books:\n1:Search by book name\n2:Find by author name\n3:Find by year\n0:Exit\n");
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
				if(strcmp(pr->title,name) == 0){
                     printf("ID:%ld\tTITLE:%s\tAUTHOR:%s\tYEAR OF PUBLICATION:%d\tNUMBER OF COPIES:%d\tLENDING QUANTITY:%d\n",pr->id,pr->title,pr->authors,pr->year,pr->copies,pr->borrow);	                
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
				if(strcmp(pr->authors,author) == 0){
                     printf("ID:%ld\tTITLE:%s\tAUTHOR:%s\tYEAR OF PUBLICATION:%d\tNUMBER OF COPIES:%d\tLENDING QUANTITY:%d\n",pr->id,pr->title,pr->authors,pr->year,pr->copies,pr->borrow);	
				}
			    pr = pr->next;
			}
            printf("********************************************************************************\n");
            break;
		case 3:
            printf("Please enter the year of publication of the book\n");
			scanf("%u",&year1);
		    if(year1 < 1 || year1 > 2022){
                printf("Illegal input\n");
                return;
			}	
            printf("******************************Result********************************\n");
            while(pr != NULL)
			{
				if(year1 == pr->year){
                     printf("ID:%ld\tTITLE:%s\tAUTHOR:%s\tYEAR OF PUBLICATION:%d\tNUMBER OF COPIES:%d\tLENDING QUANTITY:%d\n",pr->id,pr->title,pr->authors,pr->year,pr->copies,pr->borrow);	
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
	Book *pr = head;
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
		if(pr->id == id){
			if(pr->borrow >= pr->copies){
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
	have = (pr->copies)-(pr->borrow);
	if(num > have){
		printf("Sorry, there are not enough books in the library at present\n");
		return;
	}
	pr->borrow += num;
	printf("Borrowing succeeded\n");
}

// [归还图书]
void returnbook()
{
	long id;
	int num;
	Book *pr = head;
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
		if(pr->id == id){
			if(pr->borrow == 0){
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
	if(num > pr->borrow){
		printf("Sorry, you returned more books than you borrowed\n");
		return;
	}
	pr->borrow -= num;
	printf("Return successful\n");
}

// [查看已借阅情况]
void viewbook()
{
	Book *pr=head;
	if(pr == NULL)
	{
		printf("There are no books in the library\n");
        return;
	}
    printf("*******************************Borrowed book information*******************************\n");
    while(pr != NULL)
	{	
		 if(pr->borrow > 0){
             printf("ID:%ld\tTITLE:%s\tAUTHOR:%s\tYEAR OF PUBLICATION:%d\tNUMBER OF COPIES:%d\tLENDING QUANTITY:%d\n",pr->id,pr->title,pr->authors,pr->year,pr->copies,pr->borrow);	
		 }
		 pr = pr->next;
	}
    printf("*******************************************************************************\n");
}


// [删除现存图书]
void delbook(){
	long delid;
	Book *pr = head,*p = head;
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
	while(delid != p->id && p->next != NULL){
		pr = p;
		p = p->next;
	}
	if(delid == p->id){
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


