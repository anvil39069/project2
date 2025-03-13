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
struct Sale s;

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
        fprintf(fp, "%-5s | %-35s | %-25s | %-50s | %-10s\n", "No.", "Book Name", "Author", "Genre", "Price");
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
        fprintf(fp, "%-5d | %-35s | %-25s | %-50s | RS %-10d\n", serialNumber, b.book, b.author, b.genre, b.price);
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
    double total_sales = 0.0;

    // Open files
    fp = fopen("Sales_report.txt", "w");  // Open in write mode to overwrite
    fc = fopen("cart.txt", "r");
    if (fp == NULL || fc == NULL) {
        printf("Error opening file(s)!\n");
        exit(EXIT_FAILURE);
    }

    printf("Calculating sales report...\n");

    // Array to store monthly sales (12 months)
    double monthly_sales[12] = {0};  // Initialize all months to 0

    // Read each line from cart.txt
    while (fgets(line, sizeof(line), fc)) {
        int no;
        char book_name[100], author[100], genre[100], price_str[20], purchase_date[30];
        double price;

        // Parse the line: Format is "No. | Book Name | Author | Genre | Price | Date of Purchase"
        if (sscanf(line, "%d | %[^|] | %[^|] | %[^|] | %[^|] | Date of Purchase: %[^\n]", 
                   &no, book_name, author, genre, price_str, purchase_date) == 6) {

            // Extract the price, removing the "RS" prefix
            sscanf(price_str, "RS %lf", &price);

            // Extract the month from the purchase date (assume format "YYYY-MM-DD HH:MM:SS")
            int year, month, day, hour, minute, second;
            sscanf(purchase_date, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);

            // Add the price to the corresponding month's sales
            if (month >= 1 && month <= 12) {
                monthly_sales[month - 1] += price;  // Months are 0-indexed in the array
            }

            // Add to total sales
            total_sales += price;
        }
    }

    // Write the updated sales report to Sales_report.txt
    fprintf(fp, "Sales Report:\n");
    fprintf(fp, "----------------------\n");
    fprintf(fp, "Monthly Sales Breakdown:\n");

    // Print sales for each month
    for (int i = 0; i < 12; i++) {
        if (monthly_sales[i] > 0) {  // Only print months with sales
            fprintf(fp, "Month %02d: RS %.2f\n", i + 1, monthly_sales[i]);
        }
    }

    fprintf(fp, "----------------------\n");
    fprintf(fp, "Total Cumulative Sales: RS %.2f\n", total_sales);

    // Print sales data to console
    printf("Sales Report Updated Successfully!\n");
    printf("Monthly Sales Breakdown:\n");
    for (int i = 0; i < 12; i++) {
        if (monthly_sales[i] > 0) {
            printf("Month %02d: RS %.2f\n", i + 1, monthly_sales[i]);
        }
    }
    printf("Total Cumulative Sales: RS %.2f\n", total_sales);

    // Close files
    fclose(fp);
    fclose(fc);
}