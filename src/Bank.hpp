#ifndef BANK.HPP
#define BANK.HPP

#include <iostream>


class Bank
{
private:
  std::string m_bankname;
public:
  Bank();

  std::string getBankname();

  void deposit();
  void withdraw();
  void viewBal();
  void transfer();
  void viewTransactions();
  void changePassword();
};

#endif //BANK.HPP
