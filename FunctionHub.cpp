#include "FunctionHub.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


char numbers[]={'0','1','2','3','4','5','6','7','8','9','.'}; // array of allowed character
bool checkaccNum(std::string& accNum) // check if account number exist
{
  std::vector<std::string> accountdata;
  accountdata=getData("account.txt");
  for(int i=0;i<accountdata.size();i+=2)
  {
    if(accountdata.at(i)==accNum) // if found accNum in accountdata vector so its break
    {
      return true;
    }
  }
  return false;
}

float inputAmount() // check amount inputed and return input amount
{
  bool checkAmount=false,onedot=false;
  std::string amount="";
  while(true)
  {
    std::cin >> amount;
    onedot=false;
    for(int i=0;i<amount.length();i++)
    {
      checkAmount=false;
      for(int j=0;j<11;j++)
      {
        if(amount[i]==numbers[j]) //if char in numbers
        {
          checkAmount=true;
          if(onedot==true & amount[i]=='.'){ onedot=false,checkAmount=false; } // found second dot
          if(amount[i]=='.'){ onedot=true; } //check first dot
          break; // break j
        }
      }
      if(checkAmount==false){
        system("clear");
        std::cout << "Invalid amount, please try again: $";
        break; // break i
      }
    }
    if(checkAmount==true){ return round(std::stof(amount)*100.0)/100.0; } // return round version
  }
}

std::vector<std::string> getData(std::string txtfile)
{
  std::vector<std::string> vec;
  std::string info;
  std::ifstream file(txtfile);
  if(file.is_open())
  {
    while(std::getline(file, info))
    {
      vec.push_back(info);
    }
  }
  file.close();
  return vec;
}
void saveData(std::vector<std::string>& vec, std::string txtfile)
{
  std::ofstream file(txtfile);
  for(int i=0;i<vec.size();i++)
  {
    file << vec.at(i) << '\n';
  }
  file.close();
  return;
}

void addaccData(std::string accNum,std::string password)
{
  std::vector<std::string> accountdata;
  accountdata=getData("account.txt");
  accountdata.push_back(accNum);
  accountdata.push_back(password);
  return saveData(accountdata,"account.txt");
}
void addinfoData(std::string accNum, std::string firstname, std::string lastname)
{
  std::vector<std::string> bankdata;
  bankdata=getData("infodata.txt");
  bankdata.push_back(accNum);
  bankdata.push_back(firstname);
  bankdata.push_back(lastname);
  bankdata.push_back(std::to_string(0.0f));
  return saveData(bankdata,"infodata.txt");
}
void addTransaction(std::string accNum)
{
  std::vector<std::string> transactiondata;
  transactiondata=getData("transaction.txt");
  transactiondata.push_back(accNum);
  return saveData(transactiondata,"transaction.txt");
}
void addAcc(std::string accNum, std::string password, std::string firstname, std::string lastname)
{
  addaccData(accNum,password);
  addinfoData(accNum,firstname,lastname);
  addTransaction(accNum);
  return;
}


void deleteaccData(std::string& accNum)
{
  std::vector<std::string> account;
  account=getData("account.txt");
  for(int i=0;i<account.size();i+=2)
  {
    if(account.at(i)==accNum)
    {
      account.erase(account.begin()+i);
      account.erase(account.begin()+i);
      return saveData(account,"account.txt");
    }
  }
  return;
}
void deleteinfoData(std::string& accNum)
{
  std::vector<std::string> infodata;
  infodata=getData("infodata.txt");
  for(int i=0;i<infodata.size();i+=4)
  {
    if(infodata.at(i)==accNum)
    {
      for(int j=0;j<4;j++)
      {
        infodata.erase(infodata.begin()+i);
      }
      return saveData(infodata,"infodata.txt");
    }
  }
  return;
}
void deleteTransaction(std::string& accNum)
{
  std::vector<std::string> transaction;
  transaction=getData("transaction.txt");
  for(int i=0;i<=transaction.size();i++)
  {
    if(transaction.at(i)==accNum)
    {
      transaction.erase(transaction.begin()+i);
      while(i<transaction.size())
      {
        if(transaction.at(i)[0]=='w' | transaction.at(i)[0]=='d' | transaction.at(i)[6]=='r' | transaction.at(i)[6]=='t')
        {
          transaction.erase(transaction.begin()+i);
        }
        else { break; }
      }
      return saveData(transaction,"transaction.txt");
    }
  }
  return;
}
void deleteAcc(std::string accNum)
{
  deleteaccData(accNum);
  deleteinfoData(accNum);
  deleteTransaction(accNum);
  return;
}

void updateaccData(std::string accNum,std::string password)
{
  std::vector<std::string> account;
  account=getData("account.txt");
  for(int i=0;i<account.size();i+=2)
  {
    if(account.at(i)==accNum)
    {
      account.at(i+1)=password;
      return saveData(account,"account.txt");
    }
  }
  return;
}
void updateinfoData(std::string accNum, float balance)
{
  std::vector<std::string> infodata;
  infodata=getData("infodata.txt");
  for(int i=0;i<infodata.size();i+=4)
  {
    if(infodata.at(i)==accNum)
    {
      infodata.at(i+3)=std::to_string(balance);
      return saveData(infodata,"infodata.txt");
    }
  }
  return;
}
void updateTransaction(std::string accNum0, float amount, char activity, std::string accNum1)
{
  std::vector<std::string> transactiondata;
  transactiondata=getData("transaction.txt");
  for(int i=0;i<transactiondata.size();i++)
  {
    if(transactiondata.at(i)==accNum0)
    {
      transactiondata.insert(transactiondata.begin()+i+1,accNum1+activity+std::to_string((round(amount)*100.0)/100.0));
      return saveData(transactiondata,"transaction.txt");
    }
  }
  return;
}
