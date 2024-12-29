#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "accounts.txt"

typedef struct {
    int account_number;
    char name[50];
    double balance;
} Account;

void create_account();
void deposit_withdraw(int is_deposit);
void display_account();
void delete_account();

void create_account() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    Account acc;
    printf("Enter Account Number: ");
    scanf("%d", &acc.account_number);
    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);  // Read full name with spaces
    printf("Enter Initial Balance: ");
    scanf("%lf", &acc.balance);

    fprintf(file, "%d %s %.2lf\n", acc.account_number, acc.name, acc.balance);
    fclose(file);

    printf("Account created successfully!\n");
}

void deposit_withdraw(int is_deposit) {
    int acc_no;
    double amount;
    Account acc;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &acc_no);

    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        perror("Unable to open file");
        return;
    }

    while (fscanf(file, "%d %s %lf", &acc.account_number, acc.name, &acc.balance) != EOF) {
        if (acc.account_number == acc_no) {
            found = 1;
            printf("Enter amount to %s: ", is_deposit ? "deposit" : "withdraw");
            scanf("%lf", &amount);

            if (!is_deposit && amount > acc.balance) {
                printf("Insufficient balance!\n");
            } else {
                acc.balance += is_deposit ? amount : -amount;
                printf("Transaction successful! New balance: %.2lf\n", acc.balance);
            }
        }
        fprintf(temp, "%d %s %.2lf\n", acc.account_number, acc.name, acc.balance);
    }

    fclose(file);
    fclose(temp);

    if (!found) {
        printf("Account not found!\n");
    } else {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
    }
}

void display_account() {
    int acc_no;
    Account acc;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &acc_no);

    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    while (fscanf(file, "%d %s %lf", &acc.account_number, acc.name, &acc.balance) != EOF) {
        if (acc.account_number == acc_no) {
            printf("Name: %s\n", acc.name);
            printf("Balance: %.2lf\n", acc.balance);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Account not found!\n");
    }
}

void delete_account() {
    int acc_no;
    Account acc;
    int found = 0;

    printf("Enter Account Number to delete: ");
    scanf("%d", &acc_no);

    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        perror("Unable to open file");
        return;
    }

    while (fscanf(file, "%d %s %lf", &acc.account_number, acc.name, &acc.balance) != EOF) {
        if (acc.account_number == acc_no) {
            found = 1;
            printf("Account deleted successfully!\n");
        } else {
            fprintf(temp, "%d %s %.2lf\n", acc.account_number, acc.name, acc.balance);
        }
    }

    fclose(file);
    fclose(temp);

    if (!found) {
        printf("Account not found!\n");
    } else {
        remove(FILENAME);
        rename("temp.txt", FILENAME);
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nBank Management System\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Display Account Information\n");
        printf("5. Delete Account\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                deposit_withdraw(1);
                break;n
            case 3:
                deposit_withdraw(0);
                break;
            case 4:
                display_account();
                break;
            case 5:
                delete_account();
                break;
            case 6:
                printf("Exiting program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

