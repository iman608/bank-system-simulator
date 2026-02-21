#include <iostream>
#include <cstdlib>

#include "views.h"
#include "models.h"
#include "funcs.h"

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wellcom() {
    cout << "_ _ _ _ _ Hello, welcome to your bank. _ _ _ _ _ " << endl
         << "..." << endl
         << "..." << endl
         << "..." << endl;
}

int main_menu() {
    cout << "choose an option." << endl
         << "1. sign up." << endl
         << "2. log in." << endl
         << "3. leave." << endl;

    while (true) {
        cout << "enter number of list: ";
        int option = safeInputInt();

        if (option >= 1 && option <= 3) {
            return option;
        }

        cout << "wrong value, try again." << endl;
    }
}

int login_menu(string accName) {
    cout << "welcome " << accName << endl
         << "what do you want to do?" << endl
         << "1. see and change Private information." << endl
         << "2. see balance." << endl
         << "3. Money transfer." << endl
         << "4. increase balance" << endl
         << "5. change password." << endl;

    while (true) {
        cout << "enter a number in the list: ";
        int option = safeInputInt();

        if (option >= 1 && option <= 5) {
            return option;
        }

        cout << "wrong value, try again." << endl;
    }
}

bool previous_menu() {
    while (true) {
        cout << "if you want to change your information enter 1, "
             << "and if you want to return to previous menu enter 0." << endl
             << "::: ";

        int chose = safeInputInt();

        if (chose == 1 || chose == 0) {
            return (chose == 1);
        }

        cout << "your input number is not between 0 and 1, please try again." << endl;
    }
}

void Goodbye() {
    clearScreen();

    cout << "=============================\n";
    cout << "     Thank you for using     \n";
    cout << "         Our Program!        \n";
    cout << "   We appreciate your time.  \n";
    cout << "        Goodbye! 👋          \n";
    cout << "=============================\n";

    exit(0);
}
