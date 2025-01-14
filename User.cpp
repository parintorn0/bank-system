#include <iostream>
#include <vector>

#include "User.hpp"
#include "FunctionHub.hpp"

User::User(std::string& accNum):
m_firstname(""),m_lastname(""),m_accNum(""),m_password(""),m_balance(0.0f)
{
  std::string firstname="",lastname="",password="";
  float balance=0.0f;
  std::vector<std::string> account,infodata;
  account=getData("account.txt");
  infodata=getData("infodata.txt");
  for(int i=0;i<account.size(); i+=2)
  {
    if(account.at(i)==accNum)
    {
      password=account.at(i+1);
      break;
    }
  }
  for(int i=0;i<infodata.size(); i+=4)
  {
    if(infodata.at(i)==accNum)
    {
      firstname=infodata.at(i+1);
      lastname=infodata.at(i+2);
      balance=std::stof(infodata.at(i+3));
      break;
    }
  }
  setinfo(firstname,lastname,accNum,password,balance);
}

std::string User::getfirstName(){ return m_firstname; }
std::string User::getlastName() { return m_lastname; }
std::string User::getaccNum(){ return m_accNum; }
std::string User::getPassword() { return m_password; }
float User::getBal(){ return m_balance; }

void User::setBal(float& balance)
{
  m_balance= balance;
  return;
}
void User::setinfo(std::string& firstname,std::string& lastname,std::string& accNum,std::string& password,float& balance)
{
  m_firstname=firstname;
  m_lastname=lastname;
  m_accNum=accNum;
  m_password=password;
  m_balance=balance;
  return;
}

void User::deposit()
{
  float amount=0.0f;
  std::cout << "---Depositing---" << '\n' << '\n';
  std::cout << "Deposit: $";
  amount=inputAmount();
  if(amount==0){ system("clear"); }
  else
  {
    float balance0=getBal()+amount;
    setBal(balance0);
    updateinfoData(getaccNum(),getBal());
    updateTransaction(getaccNum(),amount,'d');
    std::string balance1="";

    // Printing balance but only 2 decimal place
    for(int i=0;i<std::to_string(getBal()).length();i++)
    {
      balance1 += std::to_string(getBal())[i];
      if(std::to_string(getBal())[i]=='.')
      {
        balance1 += std::to_string(getBal())[i+1];
        balance1 += std::to_string(getBal())[i+2];
        system("clear");
        std::cout << "Now " << getfirstName() << " " << getlastName() << " has $" << balance1 << '\n' << '\n' << '\n';
        break;
      }
    }
  }
  return;
}
void User::withdraw()
{
  float amount=0.0f;
  std::cout << "---Withdrawing---" << '\n' << '\n';
  std::cout << "Withdraw: $";
  amount=inputAmount();
  if(amount>m_balance)
  {
    system("clear");
    std::cout << "---Withdrawing---" << '\n' << '\n';
    std::cout << "Insufficient amount, please try again: $";
    amount=inputAmount();
  }
  if(amount==0){ system("clear"); }
  else
  {
    float balance0=getBal()-amount;
    setBal(balance0);
    updateinfoData(getaccNum(),getBal());
    updateTransaction(getaccNum(),amount,'w');
    std::string balance1="";
    
    // Printing balance but only 2 decimal place
    for(int i=0;i<std::to_string(getBal()).length();i++)
    {
      balance1 += std::to_string(getBal())[i];
      if(std::to_string(getBal())[i]=='.')
      {
        balance1 += std::to_string(getBal())[i+1];
        balance1 += std::to_string(getBal())[i+2];
        system("clear");
        std::cout << "Now " << getfirstName() << " " << getlastName() << " has $" << balance1 << '\n' << '\n' << '\n';
        break;
      }
    }
  }
  return;
}
void User::viewBal()
{
  std::string balance="";

  // Printing balance but only 2 decimal place
  for(int i=0;i<sizeof(std::to_string(getBal()));i++)
  {
    balance += std::to_string(getBal())[i];
    if(std::to_string(getBal())[i]=='.')
    {
      balance += std::to_string(getBal())[i+1];
      balance += std::to_string(getBal())[i+2];
      std::cout << getfirstName() << " " << getlastName() << " has $" << balance << " in the account" << '\n' << '\n' << '\n';
      break;
    }
  }
}
void User::transfer()
{
  std::string accNum="";
  float amount;
  std::cout << "---Transfering---" << '\n' << '\n';
  std::cout << "Transfer to account number: ";
  std::cin >> accNum;
  while(checkaccNum(accNum)==false || accNum==getaccNum())
  {
    if(accNum=="0"){ system("clear"); return; }
    system("clear");
    std::cout << "---Transfering---" << '\n' << '\n';
    if(accNum==getaccNum())
    {
      std::cout << "Cannot transfer to your own account" << '\n';
    }
    else
    {
      std::cout << "Cannot find this account, try again" << '\n';
    }
    std::cout << "Transfer to account number: ";
    std::cin >> accNum;
  }
  std::cout << "How much: $";
  amount=inputAmount();
  if(amount==0){ system("clear"); return; }
  while(amount>getBal())
  {
    system("clear");
    std::cout << "---Transfering---" << '\n' << '\n';
    std::cout << "Insufficient amount, please try again: $";
    amount=inputAmount();
    if(amount==0)
    {
      system("clear");
      return;
    }
  }
  User acc(accNum);
  float balance0=getBal()-amount;
  setBal(balance0);
  float balance1=acc.getBal()+amount;
  acc.setBal(balance1);
  updateinfoData(getaccNum(),getBal());
  updateinfoData(acc.getaccNum(),acc.getBal());
  updateTransaction(getaccNum(),amount,'t',acc.getaccNum());
  updateTransaction(acc.getaccNum(),amount,'r',getaccNum());
  system("clear");
  std::cout << "Transfer completed" << '\n' << '\n' << '\n';
  return;
}
void User::viewTransactions()
{
  std::vector<std::string> transaction;
  transaction=getData("transaction.txt");
  std::cout << "---" << getfirstName() << " " << getlastName() << " transactions---" << '\n' << '\n';
  std::cout << "-Sorted by recent-" << '\n';
  for(int i=0;i<transaction.size();i++)
  {
    if(transaction.at(i)==getaccNum())
    {
      if(i+1>=transaction.size())
      {
        system("clear");
        std::cout << getfirstName() << " " << getlastName() << " has no transaction yet" << '\n' << '\n' << '\n';
        return;
      }
      for(int k=1;true;k++)
      {
        if(i+1>=transaction.size()) // prevent transaction out of range (vector)
        {
          std::cout << '\n' << '\n';
          return;
        }
        std::string amount="";
        if(k==1 & transaction.at(i+1).length()==6) // check if second vector index is other account number
        {
          system("clear");
          std::cout << getfirstName() << " " << getlastName() << " has no transaction yet" << '\n' << '\n' << '\n';
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
void User::changePassword(std::string& password)
{
  system("clear");
  std::cout << "Password changed" << '\n' << '\n' << '\n';
  return updateaccData(getaccNum(),password);
}
