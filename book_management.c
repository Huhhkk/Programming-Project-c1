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

// [打印图书信息]
void printbook()
{
    BOOKS *pr=head;
    printf("*********************************打印图书信息**********************************\n");
	if(pr == NULL)
	{
		printf("抱歉!图书馆没有图书!  (*_*)\n");
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
	{   //遍历到最后一个节点添加图书信息
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
	    printf("please input id(range:0~999999):\n");
	    scanf("%ld",&pr->data.id);
		getchar();
        if(!(pr->data.id >= 0 && pr->data.id <= 999999)){
            printf("非法输入(图书编号范围0~999999!!)\n");
            fflush(stdin);//刷新标准输入缓冲区
            continue;			
		}
        printf("please input name(length:0~19):\n");
		scanf("%s",pr->data.name);
		if(strlen(pr->data.name) > 20){
            printf("非法输入(图书名长度0~19)!!\n");
            fflush(stdin);
            continue;
		}
     	printf("please input author(length:0~19):\n");
		scanf("%s",pr->data.author);
		if(strlen(pr->data.author) > 20){
            printf("非法输入(图书作者名长度0~19)!!\n");
            fflush(stdin);
            continue;
		}
    	printf("please input count(num:0~99):\n");
	    scanf("%d",&pr->data.count);
		getchar();
	    if(!(pr->data.count >= 0 && pr->data.count <= 99)){
            printf("非法输入(每类书总存数不得超过99本!!)\n");
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
	addbook();
	printbook();
	FILE *fp;
	load_books(fp);
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
			printf("1");
            lookupbook();
            break;
        case 2:
			printf("2");
            borrowbook();
            store_books(fp);
            break;
        case 3:
			printf("3");
            returnbook();
            store_books(fp);
            break;
		case 4:
			printf("4");
            viewbook();
            break;
        case 0:
            Login();
        default:
			printf("DEFAULT");
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
	printf("LOGIN DONE");
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
	printf("STORE");
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
		printf("There is no book in the library!!  (*_*)\n");
        return;
	}
	printf("请选择查找图书方式:\n1:按图书名查找\n2:按作者名查找\n0:放弃查找\n");
	scanf("%d",&choice);
    switch(choice){
        case 1:
			printf("请输入要查找的图书名(长度0~19):\n");
			scanf("%s",name);
		    if(strlen(name) > 20){
                printf("非法输入(图书名长度0~19)!!\n");
                printf("查找失败，系统自动为你返回上一级页面\n");
                return;
			}	
            printf("******************************打印筛选后图书信息********************************\n");
            while(pr != NULL)
			{
				if(strcmp(pr->data.name,name) == 0){
                     printf("图书编号:%ld\t图书名:%s\t图书作者:%s\t图书总存数:%d\t借出数量:%d\n",pr->data.id,pr->data.name,pr->data.author,pr->data.count,pr->data.borrow);	                
				}
			    pr = pr->next;
			}
            printf("********************************************************************************\n");
            break;
        case 2:
            printf("请输入要查找的作者名(长度0~19):\n");
			scanf("%s",author);
		    if(strlen(author) > 20){
                printf("非法输入(作者名长度0~19)!!\n");
                printf("查找失败，系统自动为你返回上一级页面\n");
                return;
			}	
            printf("******************************打印筛选后图书信息********************************\n");
            while(pr != NULL)
			{
				if(strcmp(pr->data.author,author) == 0){
                     printf("图书编号:%ld\t图书名:%s\t图书作者:%s\t图书总存数:%d\t借出数量:%d\n",pr->data.id,pr->data.name,pr->data.author,pr->data.count,pr->data.borrow);
				}
			    pr = pr->next;
			}
            printf("********************************************************************************\n");
            break;
        case 0:
			printf("放弃修改，系统自动为你返回上一级页面\n");
            return;
        default:
			printf("非法输入，系统自动为你返回上一级页面\n");
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
		printf("抱歉!图书馆没有图书!请先让管理员注册图书!!  (*_*)\n");
	    printf("借阅失败，系统自动为你返回上一级页面\n");
        return;
	}
	printf("请输入你想要借阅图书的id:\n");
	scanf("%ld",&id);
	if(!(id >= 0 && id <= 999999)){
         printf("非法输入(图书编号范围0~999999!!)\n");
         printf("系统自动为你返回上一级页面 (^@^)\n");
         return;
    }
	while(pr->next != NULL){
		if(pr->data.id == id){
			if(pr->data.borrow >= pr->data.count){
				printf("抱歉(~-~),该类图书已借阅完了!!\n");	
				printf("借阅失败，系统自动为你返回上一级页面\n");
                return;
			}else{
				break;
			}          
		}else{
			if(pr == NULL){
				printf("图书馆没有id为%ld的图书!! (&!&)\n",id);
			    printf("借阅失败，系统自动为你返回上一级页面\n");
                return;
			}else{
					pr = pr->next;
			}
		}
	}
	printf("请输入借阅该类图书的数量:\n");
	scanf("%d",&num);
	have = (pr->data.count)-(pr->data.borrow);
	if(num > have){
		printf("抱歉，图书馆目前该类图书仅有%d本可借\n",have);
		printf("借书失败，系统自动为你返回上一级页面\n");
		return;
	}
	pr->data.borrow += num;
	printf("恭喜借阅成功!!祝你学习愉快(^*^)\n");
}

// [归还图书]
void returnbook()
{
	long id;
	int num;
	BOOKS *pr = head;
	if(pr == NULL)
	{
		printf("抱歉!图书馆没有图书!请先让管理员注册图书!!  (*_*)\n");
		printf("归还失败，系统自动为你返回上一级页面\n");
        return;
	}
	printf("请输入你想要归还图书的id:\n");
	scanf("%ld",&id);
	if(!(id >= 0 && id <= 999999)){
         printf("非法输入(图书编号范围0~999999!!)\n");
         printf("系统自动为你返回上一级页面 (^@^)\n");
         return;
    }
	while(1){
		if(pr->data.id == id){
			if(pr->data.borrow == 0){
				printf("抱歉(~-~),该类图书你没有借阅何来归还!!\n");
				printf("归还失败，系统自动为你返回上一级页面\n");
                return;
			}else{
				break;
			}          
		}
		else if(pr->next == NULL){
			printf("图书馆没有id为%ld的图书!! (&!&)\n",id);
			printf("归还失败，系统自动为你返回上一级页面\n");
            return;
		}
		pr = pr->next;
	}
	printf("请输入归还该类图书的数量:\n");
	scanf("%d",&num);
	if(num > pr->data.borrow){
		printf("抱歉，你还书的数量超过借书的数量\n");
		printf("还书失败，系统自动为你返回上一级页面\n");
		return;
	}
	pr->data.borrow -= num;
	printf("恭喜归还成功!!祝你学习愉快(^*^)\n");
}

// [查看已借阅情况]
void viewbook()
{
	BOOKS *pr=head;
	if(pr == NULL)
	{
		printf("抱歉!图书馆没有图书!请先让管理员注册图书!!  (*_*)\n");
		printf("查看失败，系统自动为你返回上一级页面\n");
        return;
	}
    printf("*******************************打印已借阅图书信息*******************************\n");
    while(pr != NULL)
	{	
		 if(pr->data.borrow > 0){
             printf("图书编号:%ld\t图书名:%s\t图书作者:%s\t图书总存数:%d\t借出数量:%d\n",pr->data.id,pr->data.name,pr->data.author,pr->data.count,pr->data.borrow);
		 }
		 pr = pr->next;
	}
    printf("*******************************************************************************\n");
}
