#ifndef USER.HPP
#define USER.HPP

#include <iostream>

#include "Bank.hpp"

class User : public Bank
{
private:
  std::string m_firstname,m_lastname,m_accNum,m_password;
  float m_balance;
public:
  User(std::string& accNum);

  std::string getfirstName();
  std::string getlastName();
  std::string getaccNum();
  std::string getPassword();
  float getBal();

  void setBal(float& balance);
  void setinfo(std::string& firstname,std::string& lastname,std::string& accNum,std::string& password,float& balance);

  void deposit();
  void withdraw();
  void viewBal();
  void transfer();
  void viewTransactions();
  void changePassword(std::string& password);
};

#endif //USER.HPP
