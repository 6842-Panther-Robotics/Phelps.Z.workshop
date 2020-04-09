
class BankAccount {

  private:

    double balance;

  public:

    BankAccount();
    
    BankAccount(double amount);

    void deposit(double amount);

    void withdraw(double amount);

    double getBalance();

};
