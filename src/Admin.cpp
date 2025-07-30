#include <iostream>
#include <vector>

#include "Admin.hpp"
#include "User.hpp"
#include "FunctionHub.hpp"
#include "Mainmenu.hpp"

Admin::Admin(){}

void Admin::createAcc()
{
  std::string firstname="",lastname="",password="",accNum="";
  float balance=0.0f;
  srand(time(NULL));
  accNum=(std::to_string(rand())).substr(0,6);
  std::vector<std::string> infodata;
  infodata=getData("infodata.txt");
  while(checkaccNum(accNum)==true)
  {
    accNum=(std::to_string(rand())).substr(0,6);
  }
  std::cout << "---Creating an account for user---" << '\n' << '\n';
  std::cout << "User's first name : ";
  std::cin >> firstname;
  if(firstname=="0") { system("clear"); return; }
  std::cout << "User's last name : ";
  std::cin >> lastname;
  if(lastname=="0") { system("clear"); return; }
  std::cout << "User's password : ";
  std::cin >> password;
  if(password=="0") { system("clear"); return; }
  system("clear");
  User acc(accNum);
  acc.setinfo(firstname,lastname,accNum,password,balance);
  addAcc(accNum,password,firstname,lastname);
  std::cout << accNum << " " << firstname << " " << lastname << " account has created" << '\n' << '\n' << '\n';
  return;
}
void Admin::closeAcc()
{
  std::string accNum="";
  std::cout << "---Closing an account for user---" << '\n' << '\n';
  std::cout << "User's account number : ";
  std::cin >> accNum;
  while(checkaccNum(accNum)==false)
  {
    if(accNum=="0") { system("clear"); return; }
    system("clear");
    std::cout << "---Closing an account for user---" << '\n' << '\n';
    std::cout << "Account number's incorrect" << '\n';
    std::cout << "User's account number : ";
    std::cin >> accNum;
  }
  User acc(accNum);
  deleteAcc(acc.getaccNum());
  system("clear");
  std::cout << acc.getaccNum() << " has been closed" << '\n' << '\n' << '\n';
  return;
}

void Admin::deposit(std::string& accNum)
{
  User acc(accNum);
  float amount=0.0f;
  std::cout << "Deposit: $";
  amount=inputAmount();
  if(amount==0){ system("clear"); }
  else
  {
    float balance0=acc.getBal()+amount;
    acc.setBal(balance0);
    updateinfoData(acc.getaccNum(),acc.getBal());
    updateTransaction(acc.getaccNum(),amount,'d');
    std::string balance1="";
    for(int i=0;i<std::to_string(acc.getBal()).length();i++)
    {
      balance1 += std::to_string(acc.getBal())[i];
      if(std::to_string(acc.getBal())[i]=='.')
      {
        balance1 += std::to_string(acc.getBal())[i+1];
        balance1 += std::to_string(acc.getBal())[i+2];
        system("clear");
        std::cout << "Now " << acc.getfirstName() << " " << acc.getlastName() << " has $" << acc.getBal() << '\n' << '\n' << '\n';
        break;
      }
    }
  }
  return;
}
void Admin::withdraw(std::string& accNum)
{
  User acc(accNum);
  float amount=0.0f;
  std::cout << "Withdraw: $";
  amount=inputAmount();
  if(amount==0){ system("clear"); }
  else
  {
    float balance0=acc.getBal()-amount;
    acc.setBal(balance0);
    updateinfoData(acc.getaccNum(),acc.getBal());
    updateTransaction(acc.getaccNum(),amount,'w');
    std::string balance1="";
    for(int i=0;i<std::to_string(acc.getBal()).length();i++)
    {
      balance1 += std::to_string(acc.getBal())[i];
      if(std::to_string(acc.getBal())[i]=='.')
      {
        balance1 += std::to_string(acc.getBal())[i+1];
        balance1 += std::to_string(acc.getBal())[i+2];
        system("clear");
        std::cout << "Now " << acc.getfirstName() << " " << acc.getlastName() << " has $" << acc.getBal() << '\n' << '\n' << '\n';
        break;
      }
    }
  }
  return;
}
void Admin::viewBal(std::string& accNum)
{
  User acc(accNum); // admin access
  std::string balance="";
  for(int i=0;i<sizeof(std::to_string(acc.getBal()));i++)
  {
    balance += std::to_string(acc.getBal())[i];
    if(std::to_string(acc.getBal())[i]=='.')
    {
      balance += std::to_string(acc.getBal())[i+1];
      balance += std::to_string(acc.getBal())[i+2];
      std::cout << acc.getfirstName() << " " << acc.getlastName() << " has $" << balance << " in the account" << '\n' << '\n' << '\n';
      break;
    }
  }
}
void Admin::transfer()
{
  std::string accNum="",accNum1="";
  float amount=0.0f;
  std::cout << "---Transfering---" << '\n' << '\n';
  std::cout << "Transfer from account number: ";
  std::cin >> accNum;
  if(accNum=="0"){ system("clear"); return; }
  while(checkaccNum(accNum)==false)
  {
    system("clear");
    std::cout << "---Transfering---" << '\n' << '\n';
    std::cout << "Cannot find this account, try again" << '\n';
    std::cout << "Transfer from account number: ";
    std::cin >> accNum;
    if(accNum=="0"){ system("clear"); return; }
  }
  std::cout << "To account number: ";
  std::cin >> accNum1;
  bool firstcin=false;
  if(accNum1=="0"){ system("clear"); return; }
  while(checkaccNum(accNum1)==false || accNum1==accNum)
  {
    firstcin=false;
    system("clear");
    std::cout << "---Transfering---" << '\n' << '\n';
    if(accNum==accNum1)
    {
      std::cout << "Cannot transfer to same account" << '\n';
    }
    else
    {
      std::cout << "Cannot find this account, try again" << '\n';
    }
    std::cout << "To account number: ";
    std::cin >> accNum1;
    if(accNum1=="0"){ system("clear"); return; }
  }
  User acc1(accNum);
  std::cout << "How much: $";
  amount=inputAmount();
  if(amount==0){ system("clear"); return; }
  while(amount>acc1.getBal())
  {
    system("clear");
    std::cout << "---Transfering---" << '\n' << '\n';
    std::cout << "Insufficient amount, please try again: $";
    amount=inputAmount();
    if(amount==0){ system("clear"); return; }
  }
  User acc2(accNum1);
  float balance1=acc1.getBal()-amount;
  float balance2=acc2.getBal()+amount;
  acc1.setBal(balance1);
  acc2.setBal(balance2);
  updateinfoData(acc1.getaccNum(),balance1);
  updateinfoData(acc2.getaccNum(),balance2);
  updateTransaction(acc1.getaccNum(),amount,'t',acc2.getaccNum());
  updateTransaction(acc2.getaccNum(),amount,'r',acc1.getaccNum());
  system("clear");
  std::cout << "Transfer completed" << '\n' << '\n' << '\n';
  return;
}
void Admin::viewTransactions(std::string& accNum)
{
  User acc(accNum);
  std::vector<std::string> transaction;
  transaction=getData("transaction.txt");
  std::cout << "---" << acc.getfirstName() << " " << acc.getlastName() << " transactions---" << '\n' << '\n';
  std::cout << "-Sorted by recent-" << '\n';
  for(int i=0;i<transaction.size();i++)
  {
    if(transaction.at(i)==accNum)
    {
      if(i+1>=transaction.size())
      {
        system("clear");
        std::cout << acc.getfirstName() << " " << acc.getlastName() << " has no transaction yet" << '\n' << '\n' << '\n';
        return;
      }
      for(int k=1;true;k++)
      {
        if(i+1>=transaction.size())
        {
          std::cout << '\n' << '\n';
          return;
        }
        std::string amount="";
        if(k==1 & transaction.at(i+1).length()==6) 
        {
          system("clear");
          std::cout << acc.getfirstName() << " " << acc.getlastName() << " has no transaction yet" << '\n' << '\n' << '\n';
          return;
        }
        if(transaction.at(i+1)[0]=='d')
        {
          for(int j=1;j<sizeof(transaction.at(i+1));j++)
          {
            amount += transaction.at(i+1)[j];
            if(transaction.at(i+1)[j]=='.')
            {
              amount += transaction.at(i+1)[j+1];
              amount += transaction.at(i+1)[j+2];
              std::cout << k << " - Deposited $" << amount << '\n';
              break;
            }
          }
        }
        else if(transaction.at(i+1)[0]=='w')
        {
          for(int j=1;j<sizeof(transaction.at(i+1));j++)
          {
            amount += transaction.at(i+1)[j];
            if(transaction.at(i+1)[j]=='.')
            {
              amount += transaction.at(i+1)[j+1];
              amount += transaction.at(i+1)[j+2];
              std::cout << k << " - Withdrew $" << amount << '\n';
              break;
            }
          }
        }
        else if(transaction.at(i+1)[6]=='r')
        {
          for(int j=7;j<sizeof(transaction.at(i+1));j++)
          {
            amount += transaction.at(i+1)[j];
            if(transaction.at(i+1)[j]=='.')
            {
              amount += transaction.at(i+1)[j+1];
              amount += transaction.at(i+1)[j+2];
              std::cout << k << " - Received $" << amount << " from account " << std::stof((transaction.at(i+1)).substr(0,6)) << '\n';
              break;
            }
          }
        }
        else if(transaction.at(i+1)[6]=='t')
        {
          for(int j=7;j<sizeof(transaction.at(i+1));j++)
          {
            amount += transaction.at(i+1)[j];
            if(transaction.at(i+1)[j]=='.')
            {
              amount += transaction.at(i+1)[j+1];
              amount += transaction.at(i+1)[j+2];
              std::cout << k << " - Transfered $" << amount << " to account " << std::stof((transaction.at(i+1)).substr(0,6)) << '\n';
              break;
            }
          }
        }
        else
        {
          break;
        }
        i++;
      }
    }
  }
  std::cout << '\n' << '\n';
  return;
}

void Admin::changePassword(std::string& password,std::string& accNum)
{
  system("clear");
  std::cout << "Password changed" << '\n' << '\n' << '\n';
  return updateaccData(accNum,password);
}
