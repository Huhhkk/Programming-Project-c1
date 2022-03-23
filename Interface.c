#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include "Interface.h"
#include "users.h"
#define LEN sizeof(struct book)
#define LEN1 sizeof(struct reader)
#define LEN2 sizeof(struct account)
void Menu();
void Login();



void Login()
{
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
	  	break;
	  default:
	  	printf("Wrong input");
		break;
  }
}

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


