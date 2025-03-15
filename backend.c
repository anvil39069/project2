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
    char choice;
    do{
    system("cls");
    printf("\n-------Welcome to admin page:-------\n\t1.Add new book\n\t2.Available Books\n\t3.Total sales\n\t4.Update book list\n\t5. Log out");
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
    case 5:
        printf("Logging out");
        return;
    case 4:
        updatebook();
        break;   
    default:
        printf("Invalid Input");
        break;
    }
    //ask admin to continue or not
    printf("\nDo you want to continue?(Y?N)");
    while((getchar()!='\n'));//to clear input buffer
    scanf("%c",&choice);
    } while(toupper(choice)=='Y');
    printf("Thank you!");

}

void customer_menu()
{
    int opt;
    char choice;
    do{
    system("cls");
    printf("------Book store------");
    printf("\n\tWelcome to our book store");
    printf("\n\tHow Can we Help you:");
    printf("\n\t1.Search book\n\t2.Sell book\n\t3.Cart\n\t4.Log out");
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
    case 4:
        printf("Logging out");
        return;
    default:
        printf("Incorrect Input");
        break;
    }
    printf("\nDo you want to continue?(Y?N)");
    while((getchar()!='\n'));//to clear input buffer
    scanf("%c",&choice);
    } while(toupper(choice)=='Y');
    printf("Thank you!");
}
