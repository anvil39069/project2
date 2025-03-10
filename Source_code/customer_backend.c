#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "books.h"

struct books b;
void searchby();
void searchbybook();
void searchbyauthor();
void searchbygenre();
void cart();
void sellbook();

void searchby()
{
    int opt;
    printf("\n----------------------------------------\n\tHow would you like to search:\n");
    printf("\t1.Search by Book name:\n");
    printf("\t2.Search by Author name:\n");
    printf("\t3.Search by Genre\n");
    printf("\n\tInput:   ");
    scanf("%d", &opt);
    switch (opt)
    {
    case 1:
        searchbybook();
        break;
    case 2:
        searchbyauthor();
        break;

    case 3:
        searchbygenre();
        break;
    default:
        system("cls");
        printf("\n\n<-----INVALID INPUT--------->");
        break;
    }
}

void searchbybook()
{
    system("cls");
    FILE *fp;
    int serialnumber;
    char book_name[200], line[200];

    printf("\nEnter the book you want to search: ");
    getchar(); // consume the enter input
    scanf("%[^\n]", book_name);

    fp = fopen("book_list.txt", "r");
    if (fp == NULL)
    {
        printf("\nError opening the file");
        exit(EXIT_FAILURE);
    }

    int match = 0;
    int header = 0;

    // Convert book_name to uppercase
    char book_name_upper[200];
    strcpy(book_name_upper, book_name);
    for (int i = 0; book_name_upper[i]; i++)
    {
        book_name_upper[i] = toupper(book_name_upper[i]);
    }

    // Search for the book name in the file
    while (fgets(line, sizeof(line), fp))
    {
        // Convert the line from the file to uppercase
        char line_upper[200];
        strcpy(line_upper, line);
        for (int i = 0; line_upper[i]; i++)
        {
            line_upper[i] = toupper(line_upper[i]);
        }

        // If the book name is found in the line, print it
        if (strstr(line_upper, book_name_upper) != NULL)
        {
            if (!header)
            {
                // Print the header once
                printf("%-5s | %-20s | %-20s | %-70s | %-10s\n", "No.", "Book Name", "Author", "Genre", "Price");
                printf("-------------------------------------------------------------\n");
                header = 1;
            }
            // Print the matched line
            printf("%s", line);
            match = 1;
        }
    }

    if (!match)
    {
        printf("\n---- Book not found -----");
    }

    fclose(fp); // Close the file after processing
}

void searchbyauthor()
{
    system("cls"); // Clear the console (only works in Windows)
    FILE *fp;
    char author_name[200], line[200];

    printf("\nEnter the author's name you want to search: ");
    getchar(); // Consume any leftover newline from previous input
    scanf("%[^\n]", author_name);

    fp = fopen("book_list.txt", "r");
    if (fp == NULL)
    {
        printf("\nError opening the file");
        exit(EXIT_FAILURE);
    }

    int match = 0;
    int header = 0;

    // Convert author_name to uppercase for case-insensitive search
    char author_name_upper[200];
    strcpy(author_name_upper, author_name);
    for (int i = 0; author_name_upper[i]; i++)
    {
        author_name_upper[i] = toupper(author_name_upper[i]);
    }

    // Search for the author's name in the file
    while (fgets(line, sizeof(line), fp))
    {
        // Convert the line from the file to uppercase
        char line_upper[200];
        strcpy(line_upper, line);
        for (int i = 0; line_upper[i]; i++)
        {
            line_upper[i] = toupper(line_upper[i]);
        }

        // If the author's name is found in the line, print it
        if (strstr(line_upper, author_name_upper) != NULL)
        {
            if (!header)
            {
                // Print the header once
                printf("\n%-5s | %-20s | %-20s | %-30s | %-10s\n", "No.", "Book Name", "Author", "Genre", "Price");
                printf("-------------------------------------------------------------------------------\n");
                header = 1;
            }
            // Print the matched line
            printf("%s", line);
            match = 1;
        }
    }

    if (!match)
    {
        printf("\n---- No books found by this author -----\n");
    }

    fclose(fp); // Close the file after processing
}

void searchbygenre()

{
    system("cls"); // Clear the console (only works in Windows)
    FILE *fp;
    char genre_name[200], line[200];

    printf("\nEnter the genre  you want to search: ");
    getchar(); // Consume any leftover newline from previous input
    scanf("%[^\n]", genre_name);

    fp = fopen("book_list.txt", "r");
    if (fp == NULL)
    {
        printf("\nError opening the file");

        exit(EXIT_FAILURE);
    }

    int match = 0;
    int header = 0;

    // Convert author_name to uppercase for case-insensitive search
    char genre_name_upper[200];
    strcpy(genre_name_upper, genre_name);
    for (int i = 0; genre_name_upper[i]; i++)
    {
        genre_name_upper[i] = toupper(genre_name_upper[i]);
    }

    // Search for the author's name in the file
    while (fgets(line, sizeof(line), fp))
    {
        // Convert the line from the file to uppercase
        char line_upper[200];
        strcpy(line_upper, line);
        for (int i = 0; line_upper[i]; i++)
        {
            line_upper[i] = toupper(line_upper[i]);
        }

        // If the author's name is found in the line, print it
        if (strstr(line_upper, genre_name_upper) != NULL)
        {
            if (!header)
            {
                // Print the header once
                printf("\n%-5s | %-20s | %-20s | %-30s | %-10s\n", "No.", "Book Name", "Author", "Genre", "Price");
                printf("-------------------------------------------------------------------------------\n");
                header = 1;
            }
            // Print the matched line
            printf("%s", line);
            match = 1;
        }
    }

    if (!match)
    {
        printf("\n---- No books found of this genre -----\n");
    }

    fclose(fp); // Close the file after processing
}

void cart()
{
    system("cls");
    FILE *fp;
    FILE *fpcart;
    int serialnumber;
    char book_name[200], line[200];

    printf("\nEnter the book you want to search: ");
    getchar();  //consume the enter input
    scanf("%[^\n]", book_name);

    fp = fopen("book_list.txt", "r");
    fpcart = fopen("cart.txt","w+");
    if (fp == NULL || fpcart == NULL) {
        printf("\nError opening the file");
        exit(EXIT_FAILURE);
    }

    int match = 0;
    int header = 0;

    // Convert book_name to uppercase 
    char book_name_upper[200];
    strcpy(book_name_upper, book_name);
    for (int i = 0; book_name_upper[i]; i++) {
        book_name_upper[i] = toupper(book_name_upper[i]);
    }

    // Search for the book name in the file
    while (fgets(line, sizeof(line), fp)) {
        // Convert the line from the file to uppercase
        char line_upper[200];
        strcpy(line_upper, line);
        for (int i = 0; line_upper[i]; i++) {
            line_upper[i] = toupper(line_upper[i]);
        }

        // If the book name is found in the line, write it to the cart
        if (strstr(line_upper, book_name_upper) != NULL) {
            //write the book name to the cart file
            fprintf(fpcart,"%s",line);
            if (!header) {
                // Print the header once
                fprintf(fpcart,"%-5s | %-20s | %-20s | %-70s | %-10s\n", "No.", "Book Name", "Author", "Genre", "Price");
                fprintf(fpcart,"-------------------------------------------------------------\n");
                header = 1;
                
            }
            // Print the matched line
            fprintf(fpcart,"%s", line);
            match = 1;
        }
        rewind(fpcart);

        if (strstr(line_upper, book_name_upper) != NULL) {
            fscanf(fp,"%s",line);

            printf("The books in the cart are as below:\n\n");
            if (!header) {
                // Print the header once
                fprintf(fpcart,"%-5s | %-20s | %-20s | %-70s | %-10s\n", "No.", "Book Name", "Author", "Genre", "Price");
                fprintf(fpcart,"-------------------------------------------------------------\n");
                header = 1;
                
            }
            // Print the matched line
            fprintf(fpcart,"%s", line);
            match = 1;
        }
        fclose(fpcart);
        fclose(fp);

}
}

void sellbook()
{
    char ans;
    FILE *fp = fopen("book_list.txt", "a+");
    FILE *fpp = fopen("Second_hand.txt", "a+");
    if (fp == NULL || fpp == NULL)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    int serialNumber = 1; // Default serial number
    int num = 1;          // Default num for second-hand books

    // Check if file is empty (to add the header)
    fseek(fp, 0, SEEK_END);
    fseek(fpp, 0, SEEK_END);

    if (ftell(fp) == 0)
    { // If file size is 0, write the header
        fprintf(fp, "%-5s | %-20s | %-20s | %-70s | %-10s\n", "No.", "Book Name", "Author", "Genre", "Price");
        fprintf(fp, "-------------------------------------------------------------\n");
    }
    if (ftell(fpp) == 0)
    {
        fprintf(fpp, "%-5s | %-20s | %-20s | %-70s | %-10s\n", "No.", "Book Name", "Author", "Genre", "Price");
        fprintf(fpp, "-------------------------------------------------------------\n");
    }
    else
    {
        // Count the number of books already in the file
        rewind(fp);
        char line[256];
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            if (isdigit(line[0]))
            { // Check if the first character is a number
                serialNumber++;
            }
        }

        rewind(fpp);
        char sent[256];
        while (fgets(sent, sizeof(sent), fpp) != NULL)
        {
            if (isdigit(sent[0]))
            {
                num++; // Only increment num for second-hand file
            }
        }
    }

    // Move to the end of the file before writing new entry
    fseek(fp, 0, SEEK_END);
    fseek(fpp, 0, SEEK_END);

    // Take input
    do
    {
        // Don't increment serialNumber and num here
        printf("\nEnter book name: ");
        scanf(" %[^\n]", b.book);

        printf("Enter author's name: ");
        scanf(" %[^\n]", b.author);

        printf("Enter book genre: ");
        scanf(" %[^\n]", b.genre);

        printf("Enter price: ");
        scanf("%d", &b.price);

        fprintf(fp, "%-5d | %-20s | %-20s | %-70s | RS %-10d\n", serialNumber, b.book, b.author, b.genre, b.price);
        fprintf(fpp, "%-5d | %-20s | %-20s | %-70s | RS %-10d\n", num, b.book, b.author, b.genre, b.price);

        printf("\nDo you wish to add more data [Y/N]: ");
        getchar(); // To consume the newline left by the previous scanf
        scanf("%c", &ans);
        ans = toupper(ans);
    } while (ans == 'Y');

    fclose(fp);
    printf("\nBook Sold successfully!\n");
    printf("Thank you for selling the book and visiting the store\n\n\n");
}
