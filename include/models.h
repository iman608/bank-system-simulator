#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>

class Account {
protected:
    std::string Name;
    std::string phone_number;
    std::string ID_number;   // national ID
    std::string Balance;
    std::string password;
    std::string Account_num; // 6 digits

    int date_create_account[3];

public:
    // getters
    std::string getAccount_num() const;
    std::string getName() const;
    std::string getphone_number() const;
    std::string getpassword() const;
    std::string getBalance() const;
    std::string getID() const;

    // setters
    void setAccount_num(std::string);
    void setName(std::string);
    void setphone_number(std::string);
    void setpassword(std::string);
    void setBalance(std::string);
    void setID(std::string);

    void makeAccNum(void);
    void changBalance(double, char);
    double double_balance(void);
};

class Card : protected Account {
public:
    double C_number; // card number
    double S_number; // shaba number

protected:
    int cvv2;
    int date[3];
    int PIN;
};

#endif
