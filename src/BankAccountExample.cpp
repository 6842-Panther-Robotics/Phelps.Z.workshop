#include "main.h"

BankAccount::BankAccount() {
  balance = 0;
}

BankAccount::BankAccount(double amount) {
  balance = amount;
}

void BankAccount::deposit(double amount) {
  //balance = balance + amount;
  balance += amount;
}

void BankAccount::withdraw(double amount) {
  balance -= amount;
}

double BankAccount::getBalance() {
  return balance;
}
