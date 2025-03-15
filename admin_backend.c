#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include<time.h>
#include "books.h"
#include "sales.h"
void sales();
void addbook();
void updatebook();
void available_books();
void trim();

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

// Function to remove the spaces
void trim(char *str) {
    // Remove leading spaces
    int i = 0;
    while (isspace(str[i])) {
        i++;
    }
    if (i > 0) {
        memmove(str, str + i, strlen(str) - i + 1);
    }

    // Remove trailing spaces
    i = strlen(str) - 1;
    while (i >= 0 && isspace(str[i])) {
        i--;
    }
    str[i + 1] = '\0';
}


// Function to update book records based on book name
void updatebook() {
    FILE *fp = fopen("book_list.txt", "r"); // Open file in read mode
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct books b[1000]; // Array to store books
    int serialNumbers[1000]; // Array to store serial numbers
    int count = 0; // Number of books read from the file

    // Read and skip the header and separator lines
    char line[256];
    fgets(line, sizeof(line), fp); // Read header
    fgets(line, sizeof(line), fp); // Read separator

    // Read book details from the file
    while (fgets(line, sizeof(line), fp)) {
        // Parse each line according to the file structure
        if (sscanf(line, "%d | %[^|] | %[^|] | %[^|] | RS %d",
                   &serialNumbers[count], b[count].book, b[count].author, b[count].genre, &b[count].price) == 5) {
            // Trim leading and trailing spaces from strings (if necessary)
            trim(b[count].book);
            trim(b[count].author);
            trim(b[count].genre);
            // You can use the TRIM macro or strtok() here if needed
            count++;
        } else {
            printf("Error parsing line: %s\n", line);
        }
    }
    fclose(fp);

    if (count == 0) {
        printf("No books found in the inventory.\n");
        return;
    }

    // Display all books
    printf("\nCurrent Book List:\n");
    printf("%-5s | %-35s | %-25s | %-50s | %-10s\n", "No.", "Book Name", "Author", "Genre", "Price");
    for (int i = 0; i < count; i++) {
        printf("%-5d | %-35s | %-25s | %-50s | RS %-10d\n",
               serialNumbers[i], b[i].book, b[i].author, b[i].genre, b[i].price);
    }

    // Ask the admin which book to update
    char bookName[100];
    printf("\nEnter the name of the book to update: ");
    scanf(" %[^\n]", bookName);

    // Clear the input buffer
    while (getchar() != '\n');

    // Find the book with the given name (case-insensitive search)
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (strcasecmp(b[i].book, bookName) == 0) { // Case-insensitive comparison
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Book with name '%s' not found.\n", bookName);
        return;
    }

    // Display the selected book's details
    printf("\nSelected Book:\n");
    printf("%-5d | %-35s | %-25s | %-50s | RS %-10d\n",
           serialNumbers[index], b[index].book, b[index].author, b[index].genre, b[index].price);

    // Ask for new details
    printf("\nEnter new details for the book:\n");
    printf("Book Name: ");
    scanf(" %[^\n]", b[index].book);

    printf("Author: ");
    scanf(" %[^\n]", b[index].author);

    printf("Genre: ");
    scanf(" %[^\n]", b[index].genre);

    printf("Price: ");
    scanf("%d", &b[index].price);

    // Clear the input buffer
    while (getchar() != '\n');

    // Write the updated data back to the file
    fp = fopen("book_list.txt", "w"); // Open file in write mode (overwrite)
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write the header and separator
    fprintf(fp, "No.   | Book Name                               | Author                        | Genre                                                                 | Price     \n");
    fprintf(fp, "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Write all books back to the file
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%-5d | %-35s | %-25s | %-50s | RS %-10d\n",
                serialNumbers[i], b[i].book, b[i].author, b[i].genre, b[i].price);
    }

    fclose(fp);

    printf("\nBook updated successfully!\n");
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