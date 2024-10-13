# 🚀 SQL-Tool: C++ to PHP MySQL Query Executor

This project consists of two components: a **C++ tool (SQL-Tool)** and a **PHP script (sql.php)**. Together, they work to send MySQL queries from the C++ application to the PHP server, which processes the queries and returns the results. It's a lightweight and efficient way to interact with a MySQL database using a combination of C++ and PHP

## 🛠 Project Overview

- **SQL-Tool (C++)**: A command-line tool written in C++ that sends SQL queries to a web server.
- **PHP Script (sql.php)**: A backend PHP file that receives the query, executes it on a MySQL database, and returns the result.

This setup allows for the execution of MySQL queries remotely, providing a way to interact with databases in a cross-platform environment using HTTP requests. 

## 🎯 Features

- **Send SQL Queries from C++**: Use the SQL-Tool to send any MySQL query to the PHP server. The data from the MySQL database is stored in a PHP file, which ensures that the data will not be exposed.

## 📁 Project Structure

```plaintext
├── sql-tool.cpp        # The C++ source file for SQL-Tool
├── sql.php             # The PHP file that handles MySQL queries
└── README.md           # Project documentation
```

## 🚀 How It Works

1. **SQL-Tool (C++)**:
    - Sends an HTTP request with the SQL query to the server where `sql.php` is hosted.
    - Receives the result of the query from the server.

2. **PHP Script (sql.php)**:
    - Receives the SQL query via an HTTP request from the C++ application.
    - Executes the query on a MySQL database.
    - Sends the results back to the C++ application as a response.

### Example Workflow

1. **C++ Tool (SQL-Tool)** sends the following SQL query:
    ```sql
    SELECT * FROM users WHERE id = 1;
    ```

2. **PHP Script (sql.php)** processes the request, runs the query on the MySQL server, and returns the result:
    ```json
    {
      "id": 1,
      "name": "John Doe",
      "email": "john.doe@example.com"
    }
    ```

## 📥 Installation & Setup

### 1. C++ Tool (SQL-Tool)
- Make sure you have a working C++ compiler (e.g., `g++` or `clang++`).
- Compile the `sql-tool.cpp` file:

    ```bash
    g++ -o sql-tool sql-tool.cpp
    ```

- Run the tool:

    ```bash
    ./sql-tool
    ```

### 2. PHP Script (sql.php)
- Place `sql.php` on your web server.
- Ensure you have a MySQL server running and properly configured.
- Modify `sql.php` to include your MySQL database credentials.

```php
$servername = "host";
$username = "username";
$password = "password";
$dbname = "database";
```

## ⚙️ Usage

1. **SQL-Tool**: Send a query from the C++ application. The SQL query is passed as a string argument, converted to Base64 format, and then sent via HTTP to the server hosting `sql.php`.

    ```cpp
    // Example: Sending a SQL query
    SQL sql; // Create an instance of the SQL class to work with queries
    std::string request = "SELECT * FROM users WHERE 1;"; // Define the SQL query as a string
    std::string response = sql.SendRequest(request); // Send the request to the server and receive the response
    ```

2. **PHP Script**: `sql.php` receives the query, executes it, and returns the result. 
   ![fARPlwF1vI](https://github.com/user-attachments/assets/e82c7dea-b8bc-4e34-93d2-7335d6d531cf)


## 🧰 Requirements

- **C++ Compiler**: g++, clang++, or any C++ compiler.
- **PHP**: PHP 7.0+ with MySQLi extension.
- **MySQL**: A MySQL server to execute the queries.
- **Web Server**: Apache or any server capable of running PHP scripts.

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for more details.

---

> May the force be with You!
