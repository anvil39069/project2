#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "admin_backend.c"
#include "customer_backend.c"

void adminlogin(); // function to call the login page
void adminmenu();

void adminlogin() // admin login page
{
    char username[10];
    char password[10];
    char a;
top:
    printf("         Username: ");
    scanf("%s", username);
    printf("         Password: ");
    scanf("%s", password);
    if ((strcmp(username, "admin") == 0) && (strcmp(password, "admin") == 0))
    {
        adminmenu();
    }
    else
    {
        printf("----------Wrong credentials--------");
        printf("\n\tWant to try again?[Y/N]  ");
        scanf(" %c", &a);
        if (toupper(a) == 'Y')
        {
            system("cls");
            goto top;
        }
    }
}
void adminmenu() // adminmenu
{
    int opt;
    system("cls");
    printf("\n-------Welcome to admin page:-------\n\t1.Add new book\n\t2.Available Books\n\t3.Total sales");
    printf("\n\t Option:-- ");
    scanf("%d", &opt);
    switch (opt)
    {
    case 1:
        addbook();
        break;
    case 2:
        available_books();
        break;
    case 3:
        sales();
        break;
    default:
        printf("Invalid Input");
        break;
    }
}

void customer_menu()
{
    int opt;
    system("cls");
    printf("------Book store------");
    printf("\n\tWelcome to our book store");
    printf("\n\tHow Can we Help you:");
    printf("\n\t1.Search book\n\t2.Sell book\n\t3.Cart");
    printf("\n\tOption:-");
    scanf("%d", &opt);
    switch (opt)
    {
    case 1:
        searchby();
        break;
    case 2:
        sellbook();
        break;
    case 3:
        cart();
        break;

    default:
        printf("Incorrect Input");
        break;
    }
}
