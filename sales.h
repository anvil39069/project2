#ifndef SALES_H
#define SALES_H

#include <time.h>  // Include time.h for struct tm

// Define the Sale structure
struct Sale {
    double amount;            // Sale amount
    struct tm date;           // Date of the sale(month for now)
};

#endif // SALES_H