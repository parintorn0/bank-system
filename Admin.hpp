#ifndef ADMIN.HPP
#define ADMIN.HPP

#include "Bank.hpp"

class Admin : public Bank
{
public:
  Admin();

  void createAcc();
  void closeAcc();

  void deposit(std::string& accNum);
  void withdraw(std::string& accNum);
  void viewBal(std::string& accNum);
  void transfer();
  void viewTransactions(std::string& accNum);
  void changePassword(std::string& password,std::string& accNum);
};

#endif //ADMIN.HPP
