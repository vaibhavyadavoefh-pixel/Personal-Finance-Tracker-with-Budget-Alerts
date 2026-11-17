# 💰 Personal Finance Tracker & Alerts

A simple console-based Personal Finance Tracker developed using **C programming**. This application helps users manage their daily financial transactions, set monthly category budgets, monitor expenses, generate monthly summaries, and analyze spending trends.

It also provides budget alerts when expenses exceed the defined limits.

## 🚀 Features

### 1. Add Transaction
- Record income and expenses.
- Store transaction date, amount, category, and type.
- Supports dynamic memory allocation to store transactions.

### 2. Category Budget Management
- Set monthly spending limits for different categories.
- Update existing category budgets.
- Maintain up to 50 different category budgets.

### 3. Monthly Summary & Alerts
- Generate financial summaries for a specific month.
- Calculate:
  - Total Income
  - Total Expenses
  - Net Savings
- Display category-wise spending.
- Alert users when spending exceeds the allocated budget.

### 4. Trend Reports
- Analyze financial activity across multiple months.
- Display monthly income, expenses, and savings.
- Automatically sort months from newest to oldest.

### 5. Export to CSV
- Export all recorded transactions into a CSV file.
- Generated file: `transactions_export.csv`
- CSV files can be opened using Microsoft Excel or Google Sheets.

## 🛠️ Technologies Used

- **Programming Language:** C
- **Compiler:** GCC
- **Libraries:**
  - `stdio.h` – Input and output operations.
  - `stdlib.h` – Dynamic memory allocation.
  - `string.h` – String manipulation and comparison.

## 📚 C Programming Concepts Used

This project demonstrates the practical implementation of:

- Structures (`struct`)
- Functions and modular programming
- Pointers
- Dynamic Memory Allocation (`malloc`, `realloc`, `free`)
- Arrays and strings
- Loops and conditional statements
- File Handling (`fopen`, `fprintf`, `fclose`)
- String functions (`strcmp`, `strcpy`, `strncmp`)

## 💻 How to Run

### Prerequisites
- GCC Compiler installed.
- A C-compatible IDE or code editor (VS Code recommended).

### Step 1: Clone the Repository

```bash
git clone https://github.com/your-username/personal-finance-tracker.git
```

### Step 2: Navigate to the Project Folder

```bash
cd personal-finance-tracker
```

### Step 3: Compile the Program

```bash
gcc main.c -o finance_tracker
```

### Step 4: Run the Application

**Windows:**
```bash
finance_tracker.exe
```

**Linux/macOS:**
```bash
./finance_tracker
```

## 📋 Application Menu

```text
====================================
   PERSONAL FINANCE TRACKER
====================================
1. Add Transaction
2. Set Category Budget
3. Monthly Summary and Alerts
4. Trend Reports
5. Export to CSV
6. Exit
Enter your choice:
```

## 📁 Project Structure

```text
Personal-Finance-Tracker/
│
├── main.c
└── README.md
```

After exporting transactions, the following file will also be generated:

```text
transactions_export.csv
```

## ⚠️ Current Limitations

- Transaction data is stored in memory and is lost when the application exits.
- Budgets are limited to 50 categories.
- Monthly summaries use the budgets currently configured for each category.
- Category names and transaction types are entered as single words.
- CSV export currently supports basic transaction data.

## 🔮 Future Improvements

- Permanent storage using file handling.
- User authentication and separate financial accounts.
- Graphical representation of spending trends.
- Custom date-range reports.
- Improved input validation.
- Automatic monthly budget notifications.

## 👨‍💻 Author

**Vaibhav Yadav**
B.Tech – Computer Science Engineering
Chandigarh University

---

⭐ If you find this project useful, consider giving the repository a star!
