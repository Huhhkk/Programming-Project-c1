#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include "Interface.h"
#include "book_management.h"
#include "librarian.h"
void delbook();
#define LEN sizeof(struct book)
#define LEN1 sizeof(struct reader)
#define LEN2 sizeof(struct account)
void main2(){
    FILE *fp;
    printf("\n****************************Welcome to the librarian operation page****************************\n");
	printf("^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~\n"); 
    printf("\t\t\t  1:Print book information\n\t\t\t  2:Add books\n\t\t\t  3:Remove books\n\t\t\t  0:Return to the previous menu\n");
	printf("Please select:\n");
	printf("^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~\n"); 
	int num;
	scanf("%d", &num);
	if (num == 1 || num == 2 || num == 3 || num == 4 || num == 0)
	{
		switch(num){
        case 1:
            printbook();
            main2();
        case 2:
            addbook();
            store_books(fp);
            main2();
        case 3:
            delbook();
            store_books(fp);
            main2();
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

