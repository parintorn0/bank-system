#ifndef MAINMENU.HPP
#define MAINMENU.HPP

#include <iostream>

#include "User.hpp"

std::string login();

std::string admingate();
int adminmenus();

std::string usergate(std::string& accNum);
int usermenus(User& acc);

#endif //MAINMENU.HPP
