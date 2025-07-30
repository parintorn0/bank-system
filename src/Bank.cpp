#include <iostream>

#include "Bank.hpp"
#include "User.hpp"
#include "FunctionHub.hpp"
#include "Mainmenu.hpp"


Bank::Bank():
m_bankname("Any bank name")
{}

std::string Bank::getBankname(){ return m_bankname; }

void Bank::deposit(){}
void Bank::withdraw(){}
void Bank::viewBal(){}
void Bank::transfer(){}
void Bank::viewTransactions(){}
void Bank::changePassword(){}
