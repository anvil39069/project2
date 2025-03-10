#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include<time.h>
#include "books.h"
#include "sales.h"
void sales();
void addbook();
void available_books();

//struct areas
struct books b;
struct sale s;

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
    char line, sent;
    FILE *file = fopen("book_list.txt", "r");
    FILE *fpp = fopen("Second_hand.txt", "r");
    if (file == NULL || fpp == NULL)
    {
        printf("Error opening file or file does not exist.\n");
        exit(EXIT_FAILURE);
    }

    int option;
    printf("\n\t1. All Books\n\t2. Second hand books\n");
    printf("\n\tEnter your option: ");
    getchar(); // Consume any leftover newline from previous input
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        printf("\nDisplaying All Books:\n");
        while ((line = fgetc(file)) != EOF)
        {
            putchar(line);
        }
        fclose(file);
        break;

    case 2:
        printf("\nDisplaying Second-hand Books:\n");
        while ((sent = fgetc(fpp)) != EOF)
        {
            putchar(sent);
        }
        fclose(fpp);
        break;

    default:
        printf("\n\t--------- Invalid INPUT ---------");
        break;
    }
}

void sales() {
    FILE *fp;  // File pointer for Sales_report.txt
    FILE *fc;  // File pointer for Cart.txt
    char line[256];
    char month[3];
    double monthly_sales = 0.0;
    double total_sales = 0.0;

    // Open files
    fp = fopen("Sales_report.txt", "a+");
    fc = fopen("Cart.txt", "r");
    if (fp == NULL || fc == NULL) {
        printf("Error opening file(s)!\n");
        exit(EXIT_FAILURE);
    }

    printf("Calculating monthly sales...\n");

    // Read each line from cart.txt
    while (fgets(line, sizeof(line), fc)) {
        char book_name[100], purchase_date[20];
        double price;

        // Parse the line: Assume format is "Book | Author | Genre | Price | Date"
        if (sscanf(line, "%*[^|]|%*[^|]|%*[^|]|%lf| Date of Purchase: %s", &price, purchase_date) == 2) {
            // Extract the month from the purchase date (assume format "YYYY-MM-DD")
            strncpy(month, &purchase_date[5], 2);
            month[2] = '\0';  // Null-terminate the string

            // Check if it's the current month
            time_t now = time(NULL);
            struct tm *current_time = localtime(&now);
            char current_month[3];
            snprintf(current_month, sizeof(current_month), "%02d", current_time->tm_mon + 1);

            if (strcmp(month, current_month) == 0) {
                monthly_sales += price;  // Add to monthly sales total
            }

            total_sales += price;  // Add to total sales
        }
    }

    // Write the monthly sales report to Sales_report.txt
    fprintf(fp, "Monthly Sales Report:\n");
    fprintf(fp, "----------------------\n");
    fprintf(fp, "Total sales for the current month: %.2f\n", monthly_sales);
    fprintf(fp, "Cumulative sales: %.2f\n", total_sales);

    printf("Monthly sales: %.2f\n", monthly_sales);
    printf("Cumulative sales: %.2f\n", total_sales);

    // Close files
    fclose(fp);
    fclose(fc);
}