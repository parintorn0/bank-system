#include <iostream>

#include "Mainmenu.hpp"

// Admin: run -> admingate (in file Mainmenu) -> select options //
// User: run -> usergate (in file Mainmenu) -> select options //

// All user accounts store in account.txt
// All admin accounts store in adminaccount.txt
// For User data store in infodata.txt
// All user transactions store in transaction.txt

int main() {
  system("clear");
  std::string prompt="login";
  while(prompt!="close")
  {
    if(prompt=="login") { prompt = login(); }
    else if(prompt=="admin") { prompt = admingate(); }
    else if(prompt.length()==6) { prompt = usergate(prompt); }
  }
  std::cout << "Out of service"; // option 8 of admin
  return 0;
}
