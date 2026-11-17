#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char date[15];
    float amount;
    char category[30];
    char type[10];
} Transaction;

typedef struct {
    char category[30];
    float limit;
} Budget;

Transaction *transactions = NULL;
int transaction_count = 0;
int transaction_capacity = 0;

Budget budgets[50];
int budget_count = 0;

void addTransaction();
void setBudget();
void generateMonthlySummary();
void trendReports();
void exportToCSV();
void freeMemory();

int main() {
    int choice;

    do {
        printf("\n====================================\n");
        printf("   PERSONAL FINANCE TRACKER\n");
        printf("====================================\n");
        printf("1. Add Transaction\n");
        printf("2. Set Category Budget\n");
        printf("3. Monthly Summary and Alerts\n");
        printf("4. Trend Reports\n");
        printf("5. Export to CSV\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                addTransaction();
                break;

            case 2:
                setBudget();
                break;

            case 3:
                generateMonthlySummary();
                break;

            case 4:
                trendReports();
                break;

            case 5:
                exportToCSV();
                break;

            case 6:
                freeMemory();
                printf("Exiting application.\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}

void addTransaction() {
    if (transaction_count >= transaction_capacity) {
        int newCapacity;

        if (transaction_capacity == 0)
            newCapacity = 10;
        else
            newCapacity = transaction_capacity * 2;

        Transaction *temp = realloc(
            transactions, (size_t)newCapacity * sizeof(Transaction)
        );

        if (temp == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }

        transactions = temp;
        transaction_capacity = newCapacity;
    }

    Transaction t;

    printf("Enter date (YYYY-MM-DD): ");
    if (scanf("%14s", t.date) != 1)
        return;

    printf("Enter amount: ");
    if (scanf("%f", &t.amount) != 1 || t.amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    printf("Enter category (Food, Rent, Salary): ");
    if (scanf("%29s", t.category) != 1)
        return;

    printf("Enter type (Income/Expense): ");
    if (scanf("%9s", t.type) != 1)
        return;

    if (strcmp(t.type, "Income") != 0 &&
        strcmp(t.type, "Expense") != 0) {
        printf("Enter Income or Expense only!\n");
        return;
    }

    transactions[transaction_count] = t;
    transaction_count++;

    printf("Transaction added successfully!\n");
}

void setBudget() {
    char cat[30];
    float limit;

    printf("Enter category name: ");
    if (scanf("%29s", cat) != 1)
        return;

    printf("Enter monthly budget limit: ");
    if (scanf("%f", &limit) != 1 || limit < 0) {
        printf("Invalid budget amount!\n");
        return;
    }

    for (int i = 0; i < budget_count; i++) {
        if (strcmp(budgets[i].category, cat) == 0) {
            budgets[i].limit = limit;
            printf("Budget updated successfully!\n");
            return;
        }
    }

    if (budget_count < 50) {
        strcpy(budgets[budget_count].category, cat);
        budgets[budget_count].limit = limit;
        budget_count++;

        printf("Budget set successfully!\n");
    } else {
        printf("Budget list is full!\n");
    }
}

void generateMonthlySummary() {
    char month[8];

    printf("Enter month (YYYY-MM): ");
    if (scanf("%7s", month) != 1)
        return;

    float income = 0, expense = 0;

    char categories[50][30];
    float spending[50] = {0};
    int count = 0;

    for (int i = 0; i < transaction_count; i++) {
        if (strncmp(transactions[i].date, month, 7) == 0) {

            if (strcmp(transactions[i].type, "Income") == 0) {
                income += transactions[i].amount;
            }

            else if (strcmp(transactions[i].type, "Expense") == 0) {
                expense += transactions[i].amount;

                int found = 0;

                for (int j = 0; j < count; j++) {
                    if (strcmp(categories[j],
                               transactions[i].category) == 0) {
                        spending[j] += transactions[i].amount;
                        found = 1;
                        break;
                    }
                }

                if (!found && count < 50) {
                    strcpy(categories[count],
                           transactions[i].category);
                    spending[count] = transactions[i].amount;
                    count++;
                }
            }
        }
    }

    printf("\n--- Monthly Summary: %s ---\n", month);
    printf("Total Income: %.2f\n", income);
    printf("Total Expense: %.2f\n", expense);
    printf("Net Savings: %.2f\n", income - expense);

    printf("\nCategory-wise Spending:\n");

    for (int i = 0; i < count; i++) {
        printf("%s: %.2f", categories[i], spending[i]);

        int found = 0;

        for (int j = 0; j < budget_count; j++) {
            if (strcmp(categories[i], budgets[j].category) == 0) {
                found = 1;

                printf(" | Budget: %.2f", budgets[j].limit);

                if (spending[i] > budgets[j].limit) {
                    printf(" | ALERT: Budget exceeded by %.2f",
                           spending[i] - budgets[j].limit);
                } else {
                    printf(" | Within Budget");
                }

                break;
            }
        }

        if (!found)
            printf(" | No Budget Set");

        printf("\n");
    }
}

void trendReports() {
    int n;

    printf("Enter number of months to analyze: ");

    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of months!\n");
        return;
    }

    if (transaction_count == 0) {
        printf("No transactions available!\n");
        return;
    }

    char (*months)[8] = malloc(
        (size_t)transaction_count * sizeof(*months)
    );

    if (months == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    int monthCount = 0;

    for (int i = 0; i < transaction_count; i++) {
        char month[8];

        strncpy(month, transactions[i].date, 7);
        month[7] = '\0';

        int found = 0;

        for (int j = 0; j < monthCount; j++) {
            if (strcmp(months[j], month) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(months[monthCount], month);
            monthCount++;
        }
    }

    // Sort months from newest to oldest.
    for (int i = 0; i < monthCount - 1; i++) {
        for (int j = i + 1; j < monthCount; j++) {
            if (strcmp(months[i], months[j]) < 0) {
                char temp[8];

                strcpy(temp, months[i]);
                strcpy(months[i], months[j]);
                strcpy(months[j], temp);
            }
        }
    }

    if (n > monthCount)
        n = monthCount;

    printf("\n--- Monthly Trend Report ---\n");

    for (int m = 0; m < n; m++) {
        float income = 0, expense = 0;

        for (int i = 0; i < transaction_count; i++) {
            if (strncmp(transactions[i].date, months[m], 7) == 0) {
                if (strcmp(transactions[i].type, "Income") == 0)
                    income += transactions[i].amount;
                else if (strcmp(transactions[i].type, "Expense") == 0)
                    expense += transactions[i].amount;
            }
        }

        printf("\nMonth: %s\n", months[m]);
        printf("Income: %.2f\n", income);
        printf("Expense: %.2f\n", expense);
        printf("Savings: %.2f\n", income - expense);
    }

    free(months);
}

void exportToCSV() {
    FILE *file = fopen("transactions_export.csv", "w");

    if (file == NULL) {
        printf("Unable to create CSV file!\n");
        return;
    }

    fprintf(file, "Date,Amount,Category,Type\n");

    for (int i = 0; i < transaction_count; i++) {
        fprintf(file, "%s,%.2f,%s,%s\n",
                transactions[i].date,
                transactions[i].amount,
                transactions[i].category,
                transactions[i].type);
    }

    fclose(file);

    printf("Transactions exported to transactions_export.csv\n");
}

void freeMemory() {
    free(transactions);
    transactions = NULL;
    transaction_count = 0;
    transaction_capacity = 0;
}