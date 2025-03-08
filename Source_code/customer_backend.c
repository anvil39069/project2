#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include"books.h"

struct books b;
void searchby();
void searchbybook();
void searchbyauthor();
void searchbygenre();

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


void searchbybook() {
    system("cls");
    FILE *fp;
    int serialnumber;
    char book_name[200], line[200];

    printf("\nEnter the book you want to search: ");
    getchar();  // Consume any leftover newline from previous input
    scanf("%[^\n]", book_name);

    fp = fopen("book_list.txt", "r");
    if (fp == NULL) {
        printf("\nError opening the file");
        exit(EXIT_FAILURE);
    }

    int match = 0;
    int header = 0;

    // Convert book_name to uppercase for case-insensitive search
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

        // If the book name is found in the line, print it
        if (strstr(line_upper, book_name_upper) != NULL) {
            if (!header) {
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

    if (!match) {
        printf("\n---- Book not found -----");
    }

    fclose(fp); // Close the file after processing
}


void searchbyauthor()
{
    system("cls");  // Clear the console (only works in Windows)
    FILE *fp;
    char author_name[200], line[200];

    printf("\nEnter the author's name you want to search: ");
    getchar();  // Consume any leftover newline from previous input
    scanf("%[^\n]", author_name);

    fp = fopen("book_list.txt", "r");
    if (fp == NULL) {
        printf("\nError opening the file");
        exit(EXIT_FAILURE);
    }

    int match = 0;
    int header = 0;

    // Convert author_name to uppercase for case-insensitive search
    char author_name_upper[200];
    strcpy(author_name_upper, author_name);
    for (int i = 0; author_name_upper[i]; i++) {
        author_name_upper[i] = toupper(author_name_upper[i]);
    }

    // Search for the author's name in the file
    while (fgets(line, sizeof(line), fp)) {
        // Convert the line from the file to uppercase
        char line_upper[200];
        strcpy(line_upper, line);
        for (int i = 0; line_upper[i]; i++) {
            line_upper[i] = toupper(line_upper[i]);
        }

        // If the author's name is found in the line, print it
        if (strstr(line_upper, author_name_upper) != NULL) {
            if (!header) {
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

    if (!match) {
        printf("\n---- No books found by this author -----\n");
    }

    fclose(fp); // Close the file after processing
}

void searchbygenre()

{
    system("cls");  // Clear the console (only works in Windows)
    FILE *fp;
    char genre_name[200], line[200];

    printf("\nEnter the genre  you want to search: ");
    getchar();  // Consume any leftover newline from previous input
    scanf("%[^\n]", genre_name);

    fp = fopen("book_list.txt", "r");
    if (fp == NULL) {
        printf("\nError opening the file");
        exit(EXIT_FAILURE);
    }

    int match = 0;
    int header = 0;

    // Convert author_name to uppercase for case-insensitive search
    char genre_name_upper[200];
    strcpy(genre_name_upper, genre_name);
    for (int i = 0; genre_name_upper[i]; i++) {
        genre_name_upper[i] = toupper(genre_name_upper[i]);
    }

    // Search for the author's name in the file
    while (fgets(line, sizeof(line), fp)) {
        // Convert the line from the file to uppercase
        char line_upper[200];
        strcpy(line_upper, line);
        for (int i = 0; line_upper[i]; i++) {
            line_upper[i] = toupper(line_upper[i]);
        }

        // If the author's name is found in the line, print it
        if (strstr(line_upper, genre_name_upper) != NULL) {
            if (!header) {
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

    if (!match) {
        printf("\n---- No books found of this genre -----\n");
    }

    fclose(fp); // Close the file after processing
}
