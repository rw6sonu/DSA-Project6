#include <iostream>
using namespace std;
class BankAccount
{
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:

      BankAccount(int accNum, string accName, double initialBalance)
    : accountNumber(accNum), accountHolderName(accName), balance(initialBalance) {}


    virtual ~BankAccount() {}

    int getAccountNumber() const
    {
        return accountNumber;
    }
    string getAccountHolderName() const
    {
        return accountHolderName;
    }
      double getBalance() const
    {
        return balance;
    }
    

    virtual void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Deposited: " << amount << " | New Balance: " << balance << endl;
        }
        else
        {
            cout << "Invalid deposit amount!\n";
        }
    }
    virtual void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "Withdrawn: " << amount << " | New Balance: " << balance << endl;
        }
        else
        {
            cout << "Invalid withdrawal or insufficient funds!\n";
        }
    }
  

    virtual void displayAccountInfo() const
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }
    virtual void calculateInterest() const
    {
        cout << "Interest calculation not available for base account.\n";
    }
    
protected:
    // Protected function for subclasses to adjust balance directly
    void adjustBalance(double amount) {
        balance += amount;
    }
};
class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:
    SavingsAccount(int accNum, string accName, double initialBalance, double rate)
        : BankAccount(accNum, accName, initialBalance), interestRate(rate) {}

    void calculateInterest() const override
    {
        double interest = getBalance() * (interestRate / 100);
        cout << "Savings Account Interest: " << interest << endl;
    }
};
class CheckingAccount : public BankAccount
{
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNum, string accName, double initialBalance, double limit)
        : BankAccount(accNum, accName, initialBalance), overdraftLimit(limit) {}

    void withdraw(double amount)override
    {
        if (amount > 0 && amount <= getBalance() + overdraftLimit)
        {
            double newBalance = getBalance() - amount;
            adjustBalance(-amount);
             cout << "Withdrawn: " << amount << " | New Balance: " << getBalance() << endl;
        }
        else
        {
            cout << "Overdraft limit exceeded!" << endl;
        }
    }
    void calculateInterest() const
    {
        cout << "Checking accounts typically don't earn interest." << endl;
    }
};
class FixedDepositAccount : public BankAccount
{
private:
    int term;
    double interestRate;

public:
    FixedDepositAccount(int accNum, string accName, double initialBalance, int t, double rate)
        : BankAccount(accNum, accName, initialBalance), term(t), interestRate(rate) {}

    void calculateInterest() const
    {
        double interest = getBalance() * (interestRate / 100) * (term / 12.0);
        cout << "Fixed Deposit Interest (" << term << " months): " << interest << endl;
    }
};

int main()
{

   

   int accNum;
    string accName;
    double balance;

    cout << "Enter details for Savings Account:\n";
    cout << "Account Number: "; cin >> accNum;
    cout << "Account Holder Name: "; cin >> accName;
    cout << "Initial Balance: "; cin >> balance;
    double sRate;
    cout << "Interest Rate (%): "; cin >> sRate;
    SavingsAccount sa(accNum, accName, balance, sRate);

    cout << "\nEnter details for Checking Account:\n";
    cout << "Account Number: "; cin >> accNum;
    cout << "Account Holder Name: "; cin >> accName;
    cout << "Initial Balance: "; cin >> balance;
    double limit;
    cout << "Overdraft Limit: "; cin >> limit;
    CheckingAccount ca(accNum, accName, balance, limit);

    cout << "\nEnter details for Fixed Deposit Account:\n";
    cout << "Account Number: "; cin >> accNum;
    cout << "Account Holder Name: "; cin >> accName;
    cout << "Initial Balance: "; cin >> balance;
    int term; double fRate;
    cout << "Term (in months): "; cin >> term;
    cout << "Interest Rate (%): "; cin >> fRate;
    FixedDepositAccount fda(accNum, accName, balance, term, fRate);

    BankAccount* accounts[] = {&sa, &ca, &fda};
    int choice, accTypes;


    do
    {
        cout << "---- Banking System Menu ----" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Display Account Info" << endl;
        cout << "4. Calculate Interest"<<endl;
        cout<<"0. Exit"<<endl;

        cout<<" Enter your choice: ";
        cin>>choice;
        int amount;

        if(choice==0)
            break;

            cout<<"Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):";
            cin>>accTypes;

            switch(choice){
                case 1:
                cout<<"Enter amount to deposit: ";
                cin>>amount;
                accounts[accTypes]->deposit(amount);
                break;

                case 2:
                cout<<"Enter amount to withdraw: ";
                cin>>amount;
                accounts[accTypes]->withdraw(amount);
                break;

                case 3:
                accounts[accTypes]-> displayAccountInfo();
                break;

                case 4:
                accounts[accTypes]->calculateInterest();
                break;

                default:
                cout<<"Invalid choice"<<endl;
            
            }
    
    }while(choice!=0);

    return 0;
}
/*
Enter details for Savings Account:
Account Number: 123
Account Holder Name: sakshi
Initial Balance: 50000
Interest Rate (%): 4

Enter details for Checking Account:
Account Number: 125
Account Holder Name: prachi
Initial Balance: 50000
Overdraft Limit: 500

Enter details for Fixed Deposit Account:
Account Number: 258
Account Holder Name: palak
Initial Balance: 50000
Term (in months): 5
Interest Rate (%): 4
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 1
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):0
Enter amount to deposit: 500
Deposited: 500 | New Balance: 50500
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 1
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):1
Enter amount to deposit: 500
Deposited: 500 | New Balance: 50500
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 1
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):2
Enter amount to deposit: 500
Deposited: 500 | New Balance: 50500
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 2
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):0
Enter amount to withdraw: 500
Withdrawn: 500 | New Balance: 50000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 2
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):1
Enter amount to withdraw: 500
Withdrawn: 500 | New Balance: 50000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 2
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):2
Enter amount to withdraw: 500
Withdrawn: 500 | New Balance: 50000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 3
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):0
Account Number: 123
Account Holder: sakshi
Balance: 50000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 3
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):1
Account Number: 125
Account Holder: prachi
Balance: 50000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 3
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):2
Account Number: 258
Account Holder: palak
Balance: 50000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 4
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):0
Savings Account Interest: 2000
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 4
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):1
Checking accounts typically don't earn interest.
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 4
Select Account (0: Saving, 1: Checking, 2: Fixed Deposit):2
Fixed Deposit Interest (5 months): 833.333
---- Banking System Menu ----
1. Deposit
2. Withdraw
3. Display Account Info
4. Calculate Interest
0. Exit
 Enter your choice: 0
 */