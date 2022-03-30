#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include "Interface.h"
#include "users.h"
#include "book_management.h"
#include "librarian.h"
#define LEN sizeof(struct book)
#define LEN1 sizeof(struct reader)
#define LEN2 sizeof(struct account)
void account();
void new_account();
int match(char m[20], char a[20]);
int onoff = 1;

// Login function for entering account password
void account() 
{
    FILE *fp;
    char ac[20];
    char password[20];
    int i = 2, j, k, n;
    printf("\nPlease enter your username:\n");
    scanf("%s", ac);
    printf("\nPlease enter your password:\n");
    scanf("%s", password);
    i = match(ac, password);
    if (i == 2)
    {
        printf("Librarian Login succeeded!\n");
        if (onoff == 1)
        {
            load_books(fp);
            onoff = 0;
        }
        main2();
    }
    if (i == 1)
    {
        printf("Login succeeded!\n");
        if (onoff == 1)
        {
            load_books(fp);
            onoff = 0;
        }
        main1();
    }
    else
    {
        if (i == -1)
        {
            printf("Wrong password!\n");
            account();
        }
        if (i == 0)
            printf("This user does not exist\n");
            Login();
    }
}

// Match the saved account and password
int match(char m[20], char a[20]) 
{
    FILE *fp;
    int n = 0, i = 0;
    char ac[20];
    char password[20], names[20];

    if ((fp = fopen("account.txt", "r")) == NULL)
    {
        printf("\n The user does not exist, please create a new account\n");
        Login();
    }
    for (; !feof(fp);)
	{
        if (strcmp(m, "Leeds") == 0){
            if (strcmp(a, "Leeds") == 0){
                return 2;
            }
        }
		fscanf(fp, "%s%s", ac, password);
		if (strcmp(m, ac) == 0)
		{
			if (strcmp(a, password) == 0)
				return 1;
			else
			{
				return -1;
			}
		}
	}
    return 0;
}

// New account
void new_account()
{
    FILE *fp;
    char ac[20];
    char password[20];
    if ((fp = fopen("account.txt", "r")) == NULL)
    {
        fp = fopen("account.txt", "w");
        fclose(fp);
    }
    fp = fopen("account.txt", "a");
    printf("\nPlease enter your account in the following format:\nUsername Password\n");
    printf("Please enter:");
    scanf("%s %s", ac, password);
    fprintf(fp, "%s %s\n", ac, password);
    fclose(fp);
    printf("Created successfully!\n");
    Login();
}