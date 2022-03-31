#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include "Interface.h"
#include "book_management.h"
#include "librarian.h"
#define LEN sizeof(struct book)
#define LEN1 sizeof(struct reader)
#define LEN2 sizeof(struct account)

int store_books(FILE *file);
int add_book(Book book);
int load_books(FILE *file);
int remove_book(Book book);
BookList find_book_by_title(const char *title);
BookList find_book_by_author(const char *author);
BookList find_book_by_year(unsigned int year);
void main1();
char choice();
void lookupbook();
void borrowbook();
void returnbook();
void viewbook();
void printbook();

Book *head = NULL;

// Print book information
void printbook()
{
	Book *pr = head;
	printf("*********************************Book information**********************************\n");
	if (pr == NULL)
	{
		printf("There are no books in the library\n");
	}
	while (pr != NULL)
	{
		printf("ID:%u\tTITLE:%s\tAUTHOR:%s\tYEAR OF PUBLICATION:%u\tNUMBER OF COPIES:%u\tLENDING QUANTITY:%u\n", pr->id, pr->title, pr->authors, pr->year, pr->copies, pr->borrow);
		pr = pr->next;
	}
	printf("*******************************************************************************\n");
}

// Register new books
int add_book(Book book)
{
	Book *p = NULL;
	Book *pr = head;
	p = (Book *)malloc(sizeof(Book));
	p->title = (char *)malloc(sizeof(char) * 100);
	p->authors = (char *)malloc(sizeof(char) * 100);
	if (p == NULL)
		exit(0);
	while (head != NULL && pr->next != NULL)
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
	while (1)
	{
		printf("please enter ID(range:0~999999):\n");
		scanf("%u", &pr->id);
		getchar();
		if (!(pr->id >= 0 && pr->id <= 999999))
		{
			printf("Illegal input\n");
			main2();
		}

		printf("please enter TITLE(length:0~19):\n");
		scanf("%s", pr->title);
		getchar();
		if (strlen(pr->title) > 20)
		{
			printf("Illegal input!!\n");
			main2();
		}

		printf("please enter AUTHOR(length:0~19):\n");
		scanf("%s", pr->authors);
		getchar();
		if (strlen(pr->title) > 20)
		{
			printf("Illegal input\n");
			main2();
		}

		printf("please enter the year of publication(num:0~2022):\n");
		scanf("%u", &pr->year);
		getchar();
		if (!(pr->year >= 0 && pr->year <= 2022))
		{
			printf("Illegal input\n");
			main2();
		}

		printf("please enter number of copies the library has(num:0~99):\n");
		scanf("%u", &pr->copies);
		getchar();
		if (!(pr->copies >= 0 && pr->copies <= 99))
		{
			printf("Illegal input\n");
			main2();
		}
		pr->borrow = 0;
		if (pr->borrow == 0)
		{
			printf("ADD SUCCESSFULLY!!\n");
			return 0;
		}
		free(p);
	}
}

// Reader login selection interface
void main1()
{
	printf("\n****************************Welcome to the reader operation page****************************\n");
	printf("^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~\n");
	printf("\t\t\t  1:Lookup books\n\t\t\t  2:Borrow books\n\t\t\t  3:Return books\n\t\t\t  4:View the state of the books\n\t\t\t  0:Return to the previous menu\n");
	printf("Please select:\n");
	printf("^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~\n");
	int num;
	scanf("%d", &num);
	if (num == 1 || num == 2 || num == 3 || num == 4 || num == 0)
	{
		switch (num)
		{
		case 1:
			lookupbook();
			main1();
		case 2:
			borrowbook();
			main1();
		case 3:
			viewbook();
			returnbook();
			main1();
		case 4:
			viewbook();
			main1();
		case 0:
			Login();
		default:
			break;
		}
	}
	else
	{
		printf("Invalid enter!!");
		Login();
	}
}

// Load book information from txt file
int load_books(FILE *file)
{
	Book *p;
	Book *pr;
	pr = head;
	if ((file = fopen("library.txt", "r")) == NULL)
	{
		printf("Failure to open file!\n");
		exit(1);
	}
	while (!feof(file))
	{
		p = (Book *)malloc(sizeof(Book));
		p->authors = (char *)malloc(sizeof(char) * 100);
		p->title = (char *)malloc(sizeof(char) * 100);
		if (p == NULL)
		{
			printf("No enough memory!\n");
			Login();
		}
		if (fscanf(file, "%d %s %s %d %d %d\n", &p->id, p->title, p->authors, &p->year, &p->copies, &p->borrow) != 6)
		{
			break;
		}
		else
		{
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

// Store the book information in the current library into txt file
int store_books(FILE *file)
{
	Book *pr = head;
	if ((file = fopen("library.txt", "w")) == NULL)
	{
		printf("Failure to open file!\n");
		exit(1);
	}
	while (pr)
	{
		fprintf(file, "%d ", pr->id);
		fprintf(file, "%s ", pr->title);
		fprintf(file, "%s ", pr->authors);
		fprintf(file, "%d ", pr->year);
		fprintf(file, "%d ", pr->copies);
		fprintf(file, "%d ", pr->borrow);
		fprintf(file, "\n");
		pr = pr->next;
	}
	fclose(file);
	return 0;
}

// Find books in three different ways
void lookupbook()
{
	int choice;
	Book *pr = head;
	char name[20], author[20];
	unsigned int year1;
	if (pr == NULL)
	{
		printf("There is no book in the library\n");
		return;
	}
	printf("Please select how to find books:\n1:Search by book name\n2:Find by author name\n3:Find by year\n0:Exit\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("Please enter the title of the book you want to find\n");
		scanf("%s", name);
		find_book_by_title(name);
		break;
	case 2:
		printf("Please enter the author name you want to find\n");
		scanf("%s", author);
		find_book_by_author(author);
		break;
	case 3:
		printf("Please enter the year of publication of the book\n");
		scanf("%u", &year1);
		find_book_by_year(year1);
		break;
	case 0:
		main1();
		break;
	default:
		printf("Illegal input\n");
		break;
	}
}

// Borrow books
void borrowbook()
{
	long id;
	int num, have;
	Book *pr = head;
	if (pr == NULL)
	{
		printf("There are no books in the library\n");
		return;
	}
	printbook();
	printf("Please enter the ID of the book you want to borrow:\n");
	scanf("%ld", &id);
	if (!(id >= 0 && id <= 999999))
	{
		printf("Illegal input\n");
		main1();
	}
	while (pr->next != NULL)
	{
		if (pr->id == id)
		{
			if (pr->borrow >= pr->copies)
			{
				printf("Sorry, the book has been borrowed\n");
				main1();
			}
			break;
		}
		if (pr == NULL)
		{
			printf("The library doesn't have this book\n");
			main1();
		}
		pr = pr->next;
	}

	printf("Please enter the number of books to borrow:\n");
	scanf("%d", &num);
	if (num < 1)
	{
		printf("Illegal input");
		main1();
	}
	have = (pr->copies) - (pr->borrow);
	if (num > have)
	{
		printf("Sorry, there are not enough books in the library at present\n");
		main1();
	}
	pr->borrow += num;
	printf("Borrowing succeeded\n");
}

// Return books
void returnbook()
{
	long id;
	int num;
	Book *pr = head;
	if (pr == NULL)
	{
		printf("There are no books in the library\n");
		main1();
	}
	printf("Please enter the ID of the book you want to return:\n");
	scanf("%ld", &id);
	if (!(id >= 0 && id <= 999999))
	{
		printf("Illegal input\n");
		main1();
	}
	while (1)
	{
		if (pr->id == id)
		{
			if (pr->borrow == 0)
			{
				printf("You didn't borrow this book\n");
				main1();
			}
			else
			{
				break;
			}
		}
		else if (pr->next == NULL)
		{
			printf("There is no such book which ID is %ld!! (&!&)\n", id);
			main1();
		}
		pr = pr->next;
	}
	printf("Please enter the number of books returned:\n");
	scanf("%d", &num);
	if (num > pr->borrow)
	{
		printf("Sorry, you returned more books than you borrowed\n");
		main1();
	}
	pr->borrow -= num;
	printf("Return successful\n");
}

// Check your borrowing status
void viewbook()
{
	Book *pr = head;
	if (pr == NULL)
	{
		printf("There are no books in the library\n");
		main1();
	}
	printf("*******************************Borrowed book information*******************************\n");
	while (pr != NULL)
	{
		if (pr->borrow > 0)
		{
			printf("ID:%u\tTITLE:%s\tAUTHOR:%s\tYEAR OF PUBLICATION:%u\tNUMBER OF COPIES:%u\tLENDING QUANTITY:%u\n", pr->id, pr->title, pr->authors, pr->year, pr->copies, pr->borrow);
		}
		pr = pr->next;
	}
	printf("*******************************************************************************\n");
}

// Delete existing books
int remove_book(Book book)
{
	long delid;
	Book *pr = head, *p = head;
	if (head == NULL)
	{
		printf("There are no books in the library\n");
		main2();
	}
	printf("Please enter the book ID you want to delete:");
	scanf("%ld", &delid);
	if (!(delid >= 0 && delid <= 999999))
	{
		printf("Illegal input\n");
		main2();
	}
	while (delid != p->id && p->next != NULL)
	{
		pr = p;
		p = p->next;
	}
	if (delid == p->id)
	{
		if (p == head)
		{
			head = p->next;
		}
		else
		{
			pr->next = p->next;
		}
		free(p);
		printf("Successfully delete the book whose ID is %ld\n", delid);
		return 0;
	}
	else
	{
		printf("There is no such book whose ID is %ld!!\n", delid);
		return 0;
	}
}

// lookup the book by the title
BookList find_book_by_title(const char *title)
{
	Book *pr = head;
	BookList x;
	x.length = 0;
	x.list = NULL;
	if (strlen(title) > 20)
	{
		printf("Illegal input\n");
		main1();
	}
	printf("******************************Result********************************\n");
	while (pr != NULL)
	{
		if (strcmp(pr->title, title) == 0)
		{
			printf("ID:%u\tTITLE:%s\tAUTHOR:%s\tYEAR OF PUBLICATION:%u\tNUMBER OF COPIES:%u\tLENDING QUANTITY:%u\n", pr->id, pr->title, pr->authors, pr->year, pr->copies, pr->borrow);
		}
		pr = pr->next;
	}
	printf("********************************************************************************\n");
	return x;
}

// lookup the book by the author
BookList find_book_by_author(const char *author)
{
	Book *pr = head;
	BookList y;
	y.length = 0;
	y.list = NULL;
	if (strlen(author) > 20)
	{
		printf("Illegal input\n");
		lookupbook();
	}
	printf("******************************Result********************************\n");
	while (pr != NULL)
	{
		if (strcmp(pr->authors, author) == 0)
		{
			printf("ID:%u\tTITLE:%s\tAUTHOR:%s\tYEAR OF PUBLICATION:%u\tNUMBER OF COPIES:%u\tLENDING QUANTITY:%u\n", pr->id, pr->title, pr->authors, pr->year, pr->copies, pr->borrow);
		}
		pr = pr->next;
	}
	printf("********************************************************************************\n");
	return y;
}

// lookup the book by the year the book published
BookList find_book_by_year(unsigned int year)
{
	Book *pr = head;
	BookList z;
	z.length = 0;
	z.list = NULL;
	if (year < 1 || year > 2022)
	{
		printf("Illegal input\n");
		lookupbook();
	}
	printf("******************************Result********************************\n");
	while (pr != NULL)
	{
		if (year == pr->year)
		{
			printf("ID:%u\tTITLE:%s\tAUTHOR:%s\tYEAR OF PUBLICATION:%u\tNUMBER OF COPIES:%u\tLENDING QUANTITY:%u\n", pr->id, pr->title, pr->authors, pr->year, pr->copies, pr->borrow);
		}
		pr = pr->next;
	}
	printf("********************************************************************************\n");
	return z;
}