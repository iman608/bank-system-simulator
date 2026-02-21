#include "models.h"
#include "funcs.h"

#include <string>

using namespace std;

string Account::getAccount_num() const { return Account_num; }
string Account::getName() const { return Name; }
string Account::getphone_number() const { return phone_number; }
string Account::getpassword() const { return password; }
string Account::getBalance() const { return Balance; }
string Account::getID() const { return ID_number; }

void Account::setAccount_num(string _Acount_num) { Account_num = _Acount_num; }
void Account::setName(string _Name) { Name = _Name; }
void Account::setphone_number(string _phone_number) { phone_number = _phone_number; }
void Account::setpassword(string _password) { password = _password; }
void Account::setBalance(string _Balance) { Balance = _Balance; }
void Account::setID(string _ID) { ID_number = _ID; }

void Account::makeAccNum() {
    Account_num = RandomNumber(6);
}

void Account::changBalance(double in, char op) {
    double bal = stod(Balance);

    if (op == '+') bal += in;
    else if (op == '-') bal -= in;

    Balance = to_string(bal);
}

double Account::double_balance() {
    return string_to_double(Balance);
}
