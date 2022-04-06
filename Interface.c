#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Interface.h"
#include "users.h"
#include "book_management.h"
#define LEN sizeof(struct book)
#define LEN1 sizeof(struct reader)
#define LEN2 sizeof(struct account)
void Menu();
void Login();


// Login selections
void Login()
{
	FILE *fp = NULL;
	void account();
	void new_account();
	char choose;
	Menu();
	scanf(" %c",&choose);
	switch(choose)
  {
	  case'1':
	    account();
	    break;
	  case'2':
	  	new_account();
	  	break;
	  case'3':
	    store_books(fp);
	  	exit(1);
	  default:
	  	printf("Wrong input\n");
		Login();
		break;
  }
}

// Main interface of library management system
void Menu()
{
	printf("**********************************************");
	printf("\n\n\t    Welcome to the library\n\n");
	printf("**********************************************");
	printf("\n\n\t\t1.Login system\n\n");
	printf("\n\n\t\t2.Create account\n\n");
	printf("\n\n\t\t3.Exit systemn\n");
	printf("**********************************************\n");
	return ;
}


