#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include "models.h"
#include <string>
#include <vector>

bool Number_check(std::string);

bool Number_check(std::string, int);

std::string getDate(void);

std::string getTime(void);

bool password_check(std::string&, std::string);

bool login(std::string, std::string);

void saveToFile(const Account&, const std::string);

void saveTransfers(Account, Account, double);

void appendToFile(const Account&, const std::string&);

Account find_AccountInFile(const std::string&);

bool AccountNum_check(std::string&);

std::string findID(std::string);

bool search_InFile(std::string&, std::string);

void updateFile(Account, std::string&, const std::string);

std::string RandomNumber(int);

std::string capitalize(std::string);

std::string casefold(std::string);

// NOTE: this is declared but not implemented in your funcs.cpp
int count(std::string, std::string);

std::vector<std::string> split(const std::string&, const char);

double getSafeDouble(void);

int safeInputInt(void);

bool isValidNumber(const std::string&);

std::string trim(const std::string&);

bool safeStod(const std::string& input, double& output);

double string_to_double(std::string line);

bool check_name(std::string);

#endif
