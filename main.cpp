#include "User.h"
#include "Bank.h"

//create new user

void createNewUser(Bank b){
    
    std::cout <<"Enter username: \n";
    std::string user;
    std::cin >> user;
    std::cin.clear();
    std::cout <<"Enter password: \n";
    std::string pass;
    std::cin >> pass;
    if(!b.createUser(user,pass)){
        std::cout << user <<" was not added" << std::endl;
        return;
    }
    
    std::cout << user <<" was added" << std::endl;

}

void removeUser(Bank b){
    std::cout <<"Enter username: \n";
    std::string username;
    std::cin >>username;

    if(!b.deleteUser(username)){
        std::cout << username<< " could not be removed"<< std::endl;
    }
    std::cout << username << " was removed"<< std::endl;
}

void listUsers(Bank b){
    b.printUsers();
}

void printTotal(Bank b){
    b.printTotal();
    std::cout<<std::endl;
}

void deposit(Bank b){
    std::cout <<"Enter username: \n";
    std::string username;
    std::cin >>username;

    std::cout <<"Enter password: \n";
    std::string pass;
    std::cin >> pass;

    std::cout <<"Enter enter amount: R\n";
    double amount;
    std::cin >>amount;
    
    b.deposit(username, pass, amount);
}

void withdraw(Bank b){
    std::cout <<"Enter username: \n";
    std::string username;
    std::cin >>username;

    std::cout <<"Enter password: \n";
    std::string pass;
    std::cin >> pass;

    std::cout <<"Enter enter amount: R\n";
    double amount;
    std::cin >>amount;
    
    b.withdraw(username, pass, amount);
}

void displayMenu(){
    std::cout << "0. Exit"<<std::endl;
    std::cout << "1. Print Total Money In Bank"<<std::endl;
    std::cout << "2. Create user\n";
    std::cout << "3. Delete user\n";
    std::cout << "4. List users\n";
    std::cout << "5. Deposit amount\n";
    std::cout << "6. Withdraw amount\n";
}

int main(){
    int choice = 0;
    Bank b;

    do{
        displayMenu();
        std::cin >> choice;

        switch(choice){
            case 0:
                break;
            case 1:
                printTotal(b);
                break;

            case 2:
                createNewUser(b);
                break;

            case 3:
                removeUser(b);
                break;

            case 4:
                listUsers(b);
                break;
            case 5:
                deposit(b);
                break;
            case 6:
                withdraw(b);
                break;

            default:
            exit(1);
        }

    }while(choice != 0);
    return 0;
}