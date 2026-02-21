#include "funcs.h"
#include <iostream>
#include <string>
#include <vector>
#include "views.h"
#include "models.h"
#include <fstream>
#include <cstdlib>
#include <ctime> 
#include <limits>
#include <limits> // برای numeric_limits


using namespace std;




int main(){
    srand(time(0));
    
    Account acc;

    wellcom();

    int  chose = main_menu();



    switch (chose)
    {
    case 1:{//sign up


        acc.makeAccNum();
        clearScreen();
        
        {
            string name;
            while(1){
                cout<<"enter your full name:";
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                getline(cin, name);

                if(check_name(name)){
                    break;
                }
                else {cout<< "the name must be just char."<<endl;}
            }

            acc.setName(name);
        }
        
        clearScreen();

        
        while(1) {
            cout<<"enter your phone number:";
            string num;
            cin>>num;

            if (Number_check(num, 11)){ 
                acc.setphone_number(num);
                break;}

            cout<<"\nthe phone number must have a 11 digits and make sure enter just number."<<endl;
            
        }
        clearScreen();
        string Idnumber;
        while(1){
            cout<<"enter your ID number:";
            
            cin>>Idnumber;

            // ✅ path updated
            ifstream inFile("data/Accounts.csv");

            string line;
            vector<string> sepline;
            bool verify = true;

            if(Number_check(Idnumber, 10)){            
                while(getline(inFile, line)){//for cheek the id is uniq for name a file.
                    sepline = split(line, ',');
                
                    if(sepline[2] == Idnumber){
                        verify = false;
                        cout<<"this id number been useed."<<endl;
                        break;
                    }
                }
            }

            if(verify){break;}


            else {cout<<"\nthe Id number must have 10 digits and make sure enter just number,."<<endl;}
        }
        acc.setID(Idnumber);
        clearScreen();

        string pass;
        cout<<"enter a password:";
        cin>> pass;

        while(1){
            string Rpass;
            cout<<"enter an password again:";
            cin>>Rpass;
            
            if(pass == Rpass){
                break;
            }

            cout<<"make sure you enter the pass true"<<endl;
        }

        acc.setpassword(pass);

        //save a accnumber and pass in the Accounts file.
        // ✅ path updated
        ofstream Pfile("data/Accounts.csv", ios::app);

        if (!Pfile){
            cerr<< "file not found."<<endl;
            exit(1);
        }

        Pfile << acc.getAccount_num()<<","
              << acc.getpassword()<<","
              << acc.getID()<<endl;

        Pfile.close();

        acc.setBalance("0.0");
        
        // make a file for user.
        saveToFile(acc, acc.getID());

        cout<< "your account make seccssfly."<<endl<< "hear is your information:" <<endl;
        
        cout<<"your Account with number "<<acc.getAccount_num()<<endl
            <<"1.name:" << acc.getName()<<endl
            <<"2.phone number:"<< acc.getphone_number()<<endl
            <<"3.ID number:" << acc.getID()<<endl<<endl;

            cin.get();

        break;
    }
        

    case 2:{//log in    
       
        string accNum;
        string accPass;
        int chose;

        while(1){//while for get the true account number and password.

            cout<<"Enter your Account number:";
            cin >> accNum;
            //acc.setAccount_num(accNum);
            
            cout<<endl<<"Enter your password:";
            cin>>accPass; 
            //acc.setpassword(accPass);

            clearScreen();
            
            
            if(login(accNum, accPass)){
                break;
            }
            else {
                cout<<endl<<"your account number or password is not correct, pless try again."<<endl;
                continue;
            }
        }
        string id = findID(accNum);

        acc = find_AccountInFile(id);
        break;
    }
    
    case 3:{//leave.
        Goodbye();
        break;
        }
    } 
    
    
    while(1){
        chose = login_menu(acc.getName());
        
        clearScreen();

        switch (chose)
        {
        case 1:{//see and chang privet information.
            cout<<"your Account with number of "<<acc.getAccount_num()<<endl
                <<"1.name:" << acc.getName()<<endl
                <<"2.phone number:"<< acc.getphone_number()<<endl
                <<"3.ID number:" << acc.getID()<<endl<<endl
                <<"if you want to chang any thing enter 0."<<endl
                <<"and if you want back to Previous menu enter 1 "<<endl;

            int op;

            cin>>op;

            if(!(op)){//user want to chang information.
                cout<< "enter the number of information you want to chang: "<<endl;
                


                while(1){
                    int in_op;
                    cin>>in_op;
                    clearScreen();
                    
                    switch (in_op)
                    {
                    case 1:{
                        cout<<"Enter your new name:";
                        string _name;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // پاک کردن ورودی باقیمانده
                        getline(cin, _name);

                        acc.setName(_name);
                        string cheng = "Name";
                        updateFile(acc, cheng, _name);
                        clearScreen();
                        break;
                    }
                    case 2:{
                        cout<<"Enter your new phone number:";
                        string _phoneNum;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, _phoneNum);

                        acc.setphone_number(_phoneNum);
                        string Pcheng = "Phone number";
                        updateFile(acc, Pcheng, _phoneNum);
                        clearScreen();
                        break;
                    }
                    case 3:
                        cout<<"you can`t change your ID number.";
                        clearScreen();

                        break;
                    
                    
                    default:
                        cout<<"you must enter a number beatwin 1 and 3, Please try again.";
                        clearScreen();
                        
                        continue;
                    }
                    break;
                }
                
            }
        
            else{//previous menu.
                continue;
            }
        break;
        }
        
        case 2:{//see balance.
            clearScreen();  
            string balnc = acc.getBalance();
            if(balnc == "" ){
                balnc = "0";
            }
            cout<<"your balance: "<<balnc<< "$" <<endl;

            cout<< "if you want to exit enter 0."<<endl
                <<"and if you want back to Previous menu enter 1. "<<endl;
            
            int op;
            cin>> op;

            if(!op){//exit from the program.
                Goodbye();
            }

            else{
                continue;
            }
        break;
        }
            
        case 3:{//Money transfer.
            while(1){
                clearScreen();

                cout<< "Enter the Account number your want to transfer money."<<endl;

                string transferAcc;
                cin>> transferAcc;
                cout<<endl;

                if(transferAcc == acc.getAccount_num()){cout<<"you must enter a Account number that is not your Account number.";continue;}
                
                if(AccountNum_check(transferAcc) && Number_check(transferAcc, 6)){
                    clearScreen();

                    while(1){
                        
                        cout<< "enter the Amount:";
                        double Amount = getSafeDouble();

                        clearScreen();

                        //save the transfer to user file.
                        string TaccID = findID(transferAcc);

                        Account Tacc = find_AccountInFile(TaccID);


                        if(Amount <= stod(acc.getBalance())){
                            clearScreen();
                            cout<<"The amount was successfully deposited."<<endl;

                            acc.changBalance(Amount, '-');
                            Tacc.changBalance(Amount, '+');
                            saveTransfers(acc, Tacc, Amount);
                            string Bcheng = "Balance";
                            updateFile(acc, Bcheng, acc.getBalance());
                            updateFile(Tacc, Bcheng, Tacc.getBalance());
                            
                            cout<<"pears enter to close to program."<<endl
                                <<"."<<endl
                                <<".."<<endl
                                <<"...";

                            cin.get();
                            Goodbye();
                        }


                        else{
                            cout<< "Your account balance is insufficient.";
                            continue;
                        }
                    }
                }

                else{
                    cout<< "the Account number is wrong, pless try again.";
                    continue;
                }
            }
            break;

        }
        

   
        case 4: {////////////////increce balance.
            string input;
            double _balance = 0;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true) {
                cout << "Please specify the amount to increase your account balance:\n";
                getline(cin, input);
    
                _balance = string_to_double(input);
                

                if (_balance != -1/*&& _balance > 0*/) {
                    cout<<"...";
                    break;
                } else {
                    cout << "Invalid amount. Please try again.\n";
                }
            }
            
            double newBalance = acc.double_balance() + _balance;
            
            acc.setBalance(to_string(newBalance));
            
            //update balance.
            string bcheng = "Balance";
            string value = acc.getBalance();
            updateFile(acc, bcheng, value);


            //save transaction.
            // ✅ path updated
            ofstream inFile(string("data/") + acc.getID() + ".csv", ios::app);

            if (!inFile) {
                cerr << "File not found.\n";
                exit(1);}
            
            inFile << getDate() << "," << getTime() << ","
                << "IncreaseBalance," << acc.getAccount_num() << ","
                << _balance << endl;

            Goodbye();
            break;
        }
        

        case 5:{//////////////////cheng password.
            string pass;
            cout<<"enter your new password."<<endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            getline(cin, pass);

            while(1){
                string Rpass;
                cout<<"enter an pass again:";
                cin>>Rpass;
                
                if(pass == Rpass){
                    break;
                }

                cout<<"make sure you enter the pass true"<<endl;
            }
            acc.setpassword(pass);

            string pcheng = "Pass";

            updateFile(acc, pcheng, acc.getpassword());

            cin.get();
            Goodbye();

            break;

                    
        }
        
        default:
            cout<< "pleas enter a number beaten 1 and 5, pleas try again."<<endl;
            continue;
        
        }

    }

}
