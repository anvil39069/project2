#include <stdio.h>
#include <conio.h>
#include "backend.c"

int main(void)

{

    printf("\t-------MAIIN MENU-------\n\tWelcome to the Store\n");
    int opt;

    printf("\n\tYou Are:---\n\t1.Admin Login\n\t2.Member Login\n\t3.Customer\n");
again:

    printf("Login:  ");
    scanf("%d", &opt);

    switch (opt)
    {
    case 1:
        adminlogin();
        break;
    case 2:
        // memeberlogin();
        break;
    case 3:
        customer_menu();
        break;

    default:
        printf("Invalid input\n");
        system("cls");
        goto again;
        break;
    }
    return 0;
}
