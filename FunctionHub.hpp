#ifndef FUNCTIONHUB.HPP
#define FUNCTIONHUB.HPP

#include <iostream>
#include <vector>

float inputAmount(); // check amount inputed and return input amount
bool checkaccNum(std::string& accNum); // check if account number exist

std::vector<std::string> getData(std::string txtfile); // get vector from text file (return vector)
void saveData(std::vector<std::string>& vec, std::string txtfile); // save vector to text file (no return only save)

void addaccData(std::string accNum, std::string password);
void addinfoData(std::string accNum, std::string firstname, std::string lastname);
void addTransaction(std::string accNum);
void addAcc(std::string accNum, std::string password, std::string firstname, std::string lastname);

void deleteaccData(std::string& accNum);
void deleteinfoData(std::string& accNum);
void deleteTransaction(std::string& accNum);
void deleteAcc(std::string accNum);

//------------------------------Updating txt file------------------------------//
void updateaccData(std::string accNum,std::string password);
void updateinfoData(std::string accNum, float balance);
void updateTransaction(std::string accNum0, float amount, char activity, std::string accNum1="");
//-----------------------------------------------------------------------------//

#endif //FUNCTIONHUB.HPP
