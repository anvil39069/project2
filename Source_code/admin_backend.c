#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include"books.h"
void sales();
void addbook();
void available_books();

struct books b;
void addbook()
{
    char ans;
    FILE *fp = fopen("book_list.txt", "a+"); // Open in append+read mode
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    int serialNumber = 1; // Default serial number

    // Check if file is empty (to add the header)
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) // If file size is 0, write the header
    {
        fprintf(fp, "%-5s | %-20s | %-20s | %-70s | %-10s\n", "No.", "Book Name", "Author", "Genre", "Price");
        fprintf(fp, "-------------------------------------------------------------\n");
    }
    else
    {
        // Count the number of books already in the file
        rewind(fp); // Move pointer to the beginning of the file
        char line[256];
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            if (isdigit(line[0])) // Check if the first character is a number
            {
                serialNumber++;
            }
        }
    }

    // Move to the end of the file before writing new entry
    fseek(fp, 0, SEEK_END);

    // Take input
    do
    {
        serialNumber++;
        printf("\nEnter book name: ");
        scanf(" %[^\n]", b.book);

        printf("Enter author's name: ");
        scanf(" %[^\n]", b.author);

        printf("Enter book genre: ");
        scanf(" %[^\n]", b.genre);

        printf("Enter price: ");
        scanf("%d", &b.price);

        // Write book details with serial number
        fprintf(fp, "%-5d | %-20s | %-20s | %-70s | RS %-10d\n", serialNumber, b.book, b.author, b.genre, b.price);
        printf("\nDo you wish to add more data[Y/N]   ");
        getchar();
        scanf("%c", &ans);
        ans = toupper(ans);
    } while (ans == 'Y');

    fclose(fp);

    printf("\nBook added successfully!\n");
}
void available_books()
{
    FILE *file = fopen("book_list.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file or file does not exist.\n");
        return;
    }

    char line;
    while ((line = fgetc(file)) != EOF)
    {
        putchar(line);
    }

    fclose(file);
}

void sales()
{
    FILE *fp;
    fp = fopen("Sales_report.txt", "r");
    if (fp == NULL)
    {
        printf("Error!!!!!\n");
        exit(EXIT_FAILURE);
    }
    char line;
    while (line = fgetc(fp) != EOF)
    {
        putchar(line);
    }
    fclose(fp);
}
