#include <iostream>
#include <vector>

#include "Admin.hpp"
#include "User.hpp"
#include "FunctionHub.hpp"
#include "Mainmenu.hpp"

std::string login()
{
  std::string accNum="",password="";
  std::cout << "Account number: ";
  std::cin >> accNum;
  std::cout << "Account password: ";
  std::cin >> password;
  std::vector<std::string> account,adminaccount;
  account=getData("account.txt");
  adminaccount=getData("adminaccount.txt");
  bool checkaccount;
  checkaccount=false;
  for(int i=0;i<account.size();i+=2)
  {
    if(account.at(i)==accNum)
    {
      checkaccount=true;
      if(account.at(i+1)==password)
      {
        system("clear");
        return accNum;
      }
      else
      {
        system("clear");
        std::cout << "Your password is incorrect, Please try again" << '\n';
        return "login";
      }
    }
  }
  if(checkaccount==false)
  {
    for(int i=0;i<adminaccount.size();i+=2)
    {
      if(adminaccount.at(i)==accNum)
      {
        if(adminaccount.at(i+1)==password)
        {
          system("clear");
          return "admin";
        }
        else
        {
          system("clear");
          std::cout << "Password is incorrect, try again" << '\n';
          return "login";
        }
      }
    }
  }
  else
  {
    std::cout << "Your account number is incorrect, Please try again" << '\n';
    return "login";
  }
    system("clear");
    std::cout << "Your Account isn't registered, Please contact admin" << '\n';
    return "login";
}

std::string admingate() // For admin successfully login
{
  Admin admin;
  int num=0;
  num=adminmenus();
  if(num==1)
  {
    system("clear");
    admin.createAcc();
    return "admin";
  }
  else if(num==2)
  {
    system("clear");
    std::string accNum="";
    std::cout << "---Viewing user's balance---" << '\n' << '\n';
    std::cout << "User's account number : ";
    std::cin >> accNum;
    while(checkaccNum(accNum)==false)
    {
      if(accNum=="0"){ system("clear"); return admingate(); }
      system("clear");
      std::cout << "---Viewing user's balance---" << '\n' << '\n';
      std::cout << "Account number's incorrect" << '\n';
      std::cout << "User's account number : ";
      std::cin >> accNum;
    }
    system("clear");
    admin.viewBal(accNum);
    return "admin";
  }
  else if(num==3)
  {
    system("clear");
    admin.closeAcc();
    return "admin";
  }
  else if(num==4)
  {
    system("clear");
    std::string accNum="";
    std::cout << "---Viewing user's transactions---" << '\n' << '\n';
    std::cout << "User's account number : ";
    std::cin >> accNum;
    while(checkaccNum(accNum)==false)
    {
      if(accNum=="0"){ system("clear"); return admingate(); }
      system("clear");
      std::cout << "---Viewing user's transactions---" << '\n' << '\n';
      std::cout << "Account number's incorrect" << '\n';
      std::cout << "User's account number : ";
      std::cin >> accNum;
    }
    system("clear");
    admin.viewTransactions(accNum);
    return "admin";
  }
  else if(num==5)
  {
    system("clear");
    admin.transfer();
    return "admin";
  }
  else if(num==6)
  {
    system("clear");
    std::string accNum="";
    std::cout << "User's account number : ";
    std::cin >> accNum;
    while(checkaccNum(accNum)==false)
    {
      std::cout << "Account number's incorrect" << '\n';
      std::cout << "User's account number : ";
      std::cin >> accNum;
    }
    std::string password="";
    char ans='N';
    while(ans!='Y')
    {
      std::cout << "New password: ";
      std::cin >> password;
      std::cout << "Are you sure? (Y,N): ";
      std::cin >> ans;
    }
    if(ans=='Y')
    {
      admin.changePassword(password,accNum);
    }
    return "admin";
  }
  else if(num==7)
  {
    system("clear");
    return "login";
  }
  else if(num==8)
  {
    system("clear");
    return "close";
  }
  return "0";
}
int adminmenus()
{
  int num=0;
  std::cout << "---Admin menus---" << '\n' << '\n';
  std::cout << "1 : Create user's account" << '\n';
  std::cout << "2 : View user's balance" << '\n';
  std::cout << "3 : Close user's account" << '\n';
  std::cout << "4 : View user's transactions" << '\n';
  std::cout << "5 : Transfer user's account to another user's account" << '\n';
  std::cout << "6 : Change user's password" << '\n' << '\n';
  std::cout << "7 : Logout" << '\n' << '\n';
  std::cout << "8 : Out of service (for admin only)" << '\n' << '\n';
  std::cout << "Pick any of this number: ";
  std::cin >> num;
  while(num < 1 | num > 8)
  {
    std::cout << "Please type correct number" << '\n';
    std::cout << "Pick any of this number: ";
    std::cin >> num;
  }
  return num;
}

std::string usergate(std::string& accNum) // For user successfully login
{
  User acc(accNum);
  std::cout << "\033[92m\e[1m---Welcome " << acc.getfirstName() << " " << acc.getlastName() << "---" << '\n' << '\n' << "\033[95m";
  int num=usermenus(acc);
  if(num==1)
  {
    system("clear");
    acc.viewBal();
    return accNum;
  }
  else if(num==2)
  {
    system("clear");
    acc.deposit();
    return accNum;
  }
  else if(num==3)
  {
    system("clear");
    acc.withdraw();
    return accNum;
  }
  else if(num==4)
  {
    system("clear");
    acc.viewTransactions();
    return accNum;
  }
  else if(num==5)
  {
    system("clear");
    acc.transfer();
    return accNum;
  }
  else if(num==6)
  {
    system("clear");
    std::string password="";
    char ans='N';
    while(ans!='Y')
    {
      std::cout << "Your new password: ";
      std::cin >> password;
      std::cout << "Are you sure? (Y,N): ";
      std::cin >> ans;
      system("clear");
    }
    if(ans=='Y')
    {
      acc.changePassword(password);
    }
    return accNum;
  }
  else if(num==7)
  {
    system("clear");
    return "login";
  }
  return "0";
}
int usermenus(User& acc)
{
  int num=0;
  std::cout << "1 : View Balance" << '\n';
  std::cout << "2 : Deposit" << '\n';
  std::cout << "3 : Withdraw" << '\n';
  std::cout << "4 : View transactions" << '\n';
  std::cout << "5 : Transfer to another account" << '\n';
  std::cout << "6 : Change password" << '\n' << '\n';
  std::cout << "\e[31m7 : Logout\e[0m" << '\n' << '\n';
  std::cout << "Pick any of this number: ";
  std::cin >> num;
  while(num < 1 | num > 7)
  {
    std::cout << "Please type correct number" << '\n';
    std::cout << "Pick any of this number: ";
    std::cin >> num;
  }
  return num;
}
