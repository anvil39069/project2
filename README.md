# Bookstore Management System

## Overview

The **Bookstore Management System** is a console-based application written in **C** that allows admins to manage books, track sales, and check inventory. Customers can search for books, sell second-hand books, and manage their shopping cart.

## Features

### Admin Panel

- **Admin Login**: Secure access to admin functionalities using the following credentials:
  - **Username**: admin  
  - **Password**: admin  
- **Add Book**: Add new books to the store inventory.
- **View Total Sales**: Check total sales and revenue generated.
- **View Available Books**: List all available books in stock.

### Customer Panel

- **Search Books**: Customers can search for books based on:
  - **Genre**
  - **Author**
  - **Title**
- **Sell Second-Hand Book**: Customers can sell used books to the store.
- **Exit Cart**: Allows customers to leave the shopping session.

### Member Panel

- **Not yet implemented**, but planned for future updates.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/project2.git
   ```
2. Navigate to the project directory:
   ```bash
   cd project2
   ```
3. Compile the C program:
   ```bash
   gcc BSM_main.c -o BSM_main
   ```
4. Run the executable:
   ```bash
   ./BSM_main
   ```

## Usage

1. Run the application and choose between **Admin** and **Customer** modes.
2. If you are an **admin**, enter the login credentials (**Username: admin, Password: admin**) and perform inventory management tasks.
3. If you are a **customer**, search for books, purchase them, or sell second-hand books.
4. Exit the program after completing your session.

## Code Structure

- `projectalpha.c`: Main source file containing all functionalities.
- `backend.c`: Handles backend related  operations.
- `admin_backend.c`: Handles admin-related operations.
- `customer_backend.c`: Manages customer functionalities.
- `book_list.txt`: Stores book records.
- `sales_list.txt`: Stores  sales data.

## Future Enhancements

- Implement **Member Login** with additional functionalities such as borrowing history.
- Add a **Graphical User Interface (GUI)** for better user experience.
- Introduce a **database system (MySQL or SQLite)** for persistent storage.
- Implement **book recommendations** based on customer preferences.
- Enhance **security measures** for login credentials.

## Contributing

Contributions are welcome! Fork the repository, make changes, and submit a pull request. If you find any issues, report them on the issue tracker.

---
Developed as part of a learning project to enhance **C programming** skills and **software development** practices.

## Developed By

- [**Alok Sharma**](https://github.com/alok-9898) - **Campus Roll Number: THA081BEI004**
- [**Anvil Shakya**](https://github.com/anvil39069) - **Campus Roll Number: THA081BEI006**
- [**Aviyan Sharma**](https://github.com/abhi-yang) - **Campus Roll Number: THA081BEI008**
- [**Nishan Parajuli**](https://github.com/nishanparajuli) - **Campus Roll Number: THA081BEI023**




