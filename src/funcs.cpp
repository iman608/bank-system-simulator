#include "funcs.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "models.h"
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h> // for remove_if in search_InFile func.
#include <limits>       // for numeric_limits
#include <algorithm>
#include <cctype>
#include <cstdlib>

using namespace std;

// ✅ path updated
const string AccFile = "data/Accounts.csv";

bool Number_check(string x){
    string sr_x = x;

    for (char ch : sr_x){
        if (ch >= '0' && ch <= '9'){continue;}
        else{return false;}
    }
    return true;
}

bool Number_check(string x, int digit) {
    int count_digits = 0;

    for (char ch : x) {
        if (ch >= '0' && ch <= '9') {
            count_digits++;
        }
        else{
            return false;
        }
    }

    return (count_digits == digit);
}

string getDate() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    stringstream ss;
    ss << put_time(localTime, "%Y-%m-%d");
    return ss.str();
}

string getTime() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    stringstream ss;
    ss << put_time(localTime, "%H:%M:%S");
    return ss.str();
}

bool password_check(string& accNum,string accpass){
    if (AccountNum_check(accNum)){
        return (search_InFile(accNum, accpass));
    }
    else return 0;
}

bool login(string accNum, string accPass){
    if (AccountNum_check(accNum) && password_check(accNum, accPass)) {
        return true;
    }
    return false;
}

void saveToFile(const Account& acc, const string fileName) {
    // ✅ path updated
    ofstream outFile(string("data/") + fileName + ".csv");
    if (!outFile) {
        cerr << "file not found." <<endl;
        exit(1);
    }

    outFile
        << "# user profile" << endl
        << "\t_Field,Value_" <<endl
        << "Name," << acc.getName() <<endl
        << "Pass," << acc.getpassword()<<endl
        << "Phone number," << acc.getphone_number() <<endl
        << "ID number," << acc.getID() <<endl<<endl<<endl
        << "# Account Info" <<endl
        << "Account number,"<<acc.getAccount_num()<<endl
        <<  "Currency,USD" <<endl
        << "Balance," <<acc.getBalance() << endl<<endl<<endl
        << "# Transaction History" <<endl
        << "Date,Time,type,Account Number,Amount" <<endl;

    outFile.close();
}

void saveTransfers(Account acc,Account Tacc, double Amount){
    // ✅ path updated
    ofstream file(string("data/") + acc.getID() + ".csv", ios::app);
    if(!file){
        cerr << "file not found.";
        exit(1);
    }

    file << getDate() << "," << getTime() << "," << "Withdrawal" << ","
         << Tacc.getAccount_num() << "," << Amount <<endl;

    file.close();

    // ✅ path updated
    ofstream Tfile(string("data/") + Tacc.getID() + ".csv", ios::app);
    if(!Tfile){
        cerr << "file not found.";
        exit(1);
    }

    Tfile << getDate() << "," << getTime() << "," << "Deposit" << ","
          << acc.getAccount_num() << "," << Amount <<endl;

    Tfile.close();
}

void updateFile(Account acc, string& cheng, const string value) {
    // ✅ path updated
    const string userPath = string("data/") + acc.getID() + ".csv";
    const string tmpPath  = string("data/temp.csv");

    ifstream inFile(userPath);
    ofstream outFile(tmpPath);

    string line;
    bool update = false;
    vector<string> spl;

    while (getline(inFile, line)) {
        if (!update) {
            spl = split(line, ',');

            if (!spl.empty() && spl[0] == cheng){
                if (spl.size() > 1) spl[1] = value;
                update = true;
            }

            string chengline = "";
            for (int i = 0; i < (int)spl.size(); i++) {
                chengline += spl[i];
                if (chengline == ""){continue;}
                if (i != ((int)spl.size()-1)) chengline += ",";
            }
            outFile << chengline << endl;
        }
        else{
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove(userPath.c_str());
    rename(tmpPath.c_str(), userPath.c_str());
}

void appendToFile(const Account& acc, const string& fileName) {
    // ✅ path updated
    ofstream outFile(string("data/") + fileName + ".csv", ios::app);
    if (!outFile) {
        cerr << "file not found." << endl;
        exit(1);
    }

    outFile << acc.getAccount_num() << ","
            << acc.getpassword()<< ","
            << acc.getName() << ","
            << acc.getBalance() << endl;

    outFile.close();
}

Account find_AccountInFile(const string& fileName) {
    // ✅ path updated
    ifstream inFile(string("data/") + fileName + ".csv");
    if (!inFile) {
        cerr << "File not found: " << fileName << ".csv" << endl;
        return Account();
    }

    string line;
    Account acc;
    while (getline(inFile, line)) {
        vector<string> sepline = split(line, ',');
        if (sepline.size() < 2) continue;

        string key = sepline[0];
        string value = sepline[1];

        key.erase(key.begin(), std::find_if(key.begin(), key.end(),
            [](unsigned char ch) { return !std::isspace(ch); }));
        key.erase(std::find_if(key.rbegin(), key.rend(),
            [](unsigned char ch) { return !std::isspace(ch); }).base(), key.end());

        if (key == "Name") {
            acc.setName(value);
        } else if (key == "Pass" || key == "pass") {
            acc.setpassword(value);
        } else if (key == "Phone number" || key == "phone number") {
            acc.setphone_number(value);
        } else if (key == "ID number"){
            acc.setID(value);
        } else if (key == "Account number") {
            acc.setAccount_num(value);
        } else if (key == "Balance") {
            acc.setBalance(value);
            cout << "DEBUG: Balance read from file: " << value << endl;
        }
    }
    return acc;
}

bool AccountNum_check(string& Account_num){
    bool verify = false;

    if (Number_check(Account_num)){
        ifstream inFile(AccFile);

        if(inFile.is_open()){
            string line;
            vector<string> accNum;

            while(getline(inFile, line)){
                accNum = split(line , ',');
                if (!accNum.empty() && Account_num == accNum[0]){verify = true;}
            }
        }
        else {cerr<<"file cant open!";}
    }
    return verify;
}

string findID(string accNum){
    ifstream file(AccFile);
    string line;
    vector<string> info;

    while(getline(file, line)){
        info = split(line , ',');
        if (!info.empty() && accNum == info[0]){
            break;
        }
    }
    if (info.size() >= 3) return info[2];
    return "";
}

bool search_InFile(string& Account_num, string password){
    ifstream inFile(AccFile);
    if (!inFile) {
        cerr << "file not found." << endl;
        exit(1);
    }
    string line;
    while (getline(inFile, line)) {
        vector<string> sepline = split(line, ',');
        if (sepline.size() < 2) continue;
        string accNum = sepline[0];
        string accPass = sepline[1];

        accNum.erase(remove_if(accNum.begin(), accNum.end(), ::isspace), accNum.end());
        accPass.erase(remove_if(accPass.begin(), accPass.end(), ::isspace), accPass.end());

        if (Account_num == accNum && password == accPass) {
            return true;
        }
    }
    return false;
}

string RandomNumber(int digits) {
    std::string number = "";
    for (int i = 0; i < digits; ++i) {
        number += std::to_string(rand() % 10);
    }
    return number;
}

string capitalize(string text) {
    if (!text.empty()) {
        text[0] = toupper(text[0]);
    }
    return text;
}

string casefold(string txt) {
    if (txt.empty()) return txt;
    for (auto& ch : txt) {
        ch = tolower(ch);
    }

    txt[0] = toupper(txt[0]);

    for (size_t i = 1; i < txt.size(); ++i) {
        if (txt[i - 1] == ' ') {
            txt[i] = toupper(txt[i]);
        }
    }
    return txt;
}

vector<string> split(const string& str, const char delimiter) {
    vector<string> result;
    string temp;
    for (char ch : str) {
        if (ch == delimiter) {
            temp.erase(0, temp.find_first_not_of(" \t\n\r\f\v"));
            temp.erase(temp.find_last_not_of(" \t\n\r\f\v") + 1);
            result.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    temp.erase(0, temp.find_first_not_of(" \t\n\r\f\v"));
    temp.erase(temp.find_last_not_of(" \t\n\r\f\v") + 1);
    result.push_back(temp);
    return result;
}

double getSafeDouble() {
    double x;
    while (!(cin >> x)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return x;
}

int safeInputInt() {
    int val;
    while (!(cin >> val)) {
        cout << "Invalid input. Enter an integer: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return val;
}

bool isValidNumber(const string& s) {
    if (s.empty()) return false;
    char* endptr = nullptr;
    strtod(s.c_str(), &endptr);
    return (*endptr == '\0');
}

bool safeStod(const std::string& input, double& output) {
    std::string trimmed = input;

    trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r\f\v"));
    trimmed.erase(trimmed.find_last_not_of(" \t\n\r\f\v") + 1);

    if (trimmed.empty()) return false;

    try {
        size_t idx;
        output = stod(trimmed, &idx);
        if (idx != trimmed.length()) return false;
        return true;
    } catch (...) {
        return false;
    }
}

double string_to_double(string line){
    try {
        return stod(line);
    } catch (...) {
        return -1;
    }
}

bool check_name(string name){
    for (char ch : name){
        int int_ch = ch;
        if (60 < int_ch || int_ch < 122 || int_ch == 32){
            continue;
        }
        else {return false;}
    }
    return true;
}
