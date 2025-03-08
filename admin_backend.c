#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "books.h"
#include "sales.h"

void seesales();
void salesreport();
void addbook();
void available_books();
void addemployee_list();

struct employee1{
    char name[100];
    char address[100];
    char post[100];
    long int phoneno;
    int salary;
};
//adding a new thing
//structure area
struct salesrep sales;
struct employee1 emp;
struct books b;

//append mode for easier access to both read and write without loss of data
void salesreport()
{
    FILE *fs=fopen("Sales_report.txt","a+");
    if (fs==NULL)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }
    int serialNumber = 1; // Default serial number

    // Check if file is empty (to add the header)
    fseek(fs, 0, SEEK_END);
    if (ftell(fs) == 0) // If file size is 0, write the header
    {
        fprintf(fs, "%-5s | %-20s\n", "No.", "Month", "Monthly Sales");
        fprintf(fs, "-------------------------------------------\n");
    }
    else
    {
        // Count the number of books already in the file
        rewind(fs); // Move pointer to the beginning of the file
        char line[256];
        while (fgets(line, sizeof(line), fs) != NULL)
        {
            if (isdigit(line[0])) // Check if the first character is a number
            {
                serialNumber++;
            }
        }
    }

    // Move to the end of the file before writing new entry
    fseek(fs, 0, SEEK_END);

    // Take input
    char ans;
    do
    {
        printf("\nEnter month: ");
        scanf(" %[^\n]", sales.month);

        printf("Enter sales for the month: ");
        scanf(" %[^\n]", sales.sales);

        // Write monthly sales details with serial number
        fprintf(fs, "%-5d | %-20s | %-20d \n", serialNumber, sales.month, sales.sales);
        printf("\nDo you wish to add more data[Y/N]   ");
        getchar();
        scanf("%c", &ans);
        ans = toupper(ans);
    } while (ans == 'Y');

    fclose(fs);

    printf("\nSalesadded successfully!\n");

}

void seesales()//to show the  sales report
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

void addbook()//to add books 
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

void available_books()//to search for available books
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

void addemployee_list()//to add the employee that is in the store
{
    FILE *fe=fopen("Employee_report.txt","a+"); //also opened in append mode
    char ans;
    if (fe == NULL)
    {
        printf("Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    int serialNumber = 1; // Default serial number

    // Check if file is empty (to add the header)
    fseek(fe, 0, SEEK_END);
    if (ftell(fe) == 0) // If file size is 0, write the header
    {
        fprintf(fe, "%-5s | %-20s | %-20s | %-20s | %-30s| %-30d\n", "No.", "Employee Name", "Post","Address","Salary","Phone number");
        fprintf(fe, "-------------------------------------------------------------\n");
    }
    else
    {
        // Count the number of emplooyes already in the file
        rewind(fe); // Move pointer to the beginning of the file
        char line[256];
        while (fgets(line, sizeof(line), fe) != NULL)
        {
            if (isdigit(line[0])) // Check if the first character is a number
            {
                serialNumber++;
            }
        }
    }

    // Move to the end of the file before writing new entry
    fseek(fe, 0, SEEK_END);

    // Take input
    do{
    printf("\nEnter Employee Name: ");
    scanf(" %[^\n]", emp.name);

    printf("Enter Employee's Post: ");
    scanf(" %[^\n]", emp.post);

    printf("Enter Employee's Post ");
    scanf(" %[^\n]", emp.address);

    printf("Enter Employee's Salary: ");
    scanf("%d", &emp.salary);

    printf("Enter Employee's Phone number");
    scanf("%d",&emp.phoneno);
    

    // Write book details with serial number
    fprintf(fe, "%-5d | %-20s | %-20s | %-20s | RS %-30d | %-30d\n", serialNumber, emp.name,emp.post,emp.address,emp.salary,emp.phoneno);
    printf("\nDo you wish to add more data[Y/N]   ");
    getchar();
    scanf("%c",&ans);
    ans=toupper(ans);
    }while(ans=='Y');
    
    fclose(fe);
    

    printf("\nEmployee added successfully!\n");
}


