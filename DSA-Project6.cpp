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
    {
        accountNumber = accNum;
        accountHolderName = accName;
        balance = initialBalance;
    }

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
};
class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:
    SavingsAccount(int accNum, string accName, double initialBalance, double rate)
        : BankAccount(accNum, accName, initialBalance), interestRate(rate) {}

    void calculateInterest() const
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

    void withdraw(double amount)
    {
        if (amount > 0 && amount <= getBalance() + overdraftLimit)
        {
            double newBalance = getBalance() - amount;
            deposit(-amount);
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

    SavingsAccount sa(101, "Sakshi", 5000, 4);
    CheckingAccount ca(102, "Prachi", 10000, 500);
    FixedDepositAccount fda(103, "Palak", 20000, 6, 8);

    BankAccount *accounts[] = {&sa, &ca, &fda};
    int choice, accTypes;
    double amount;

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
                accounts[accTypes]-> deposit(amount);
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