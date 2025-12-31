#ifndef USER_H
#define USER_H
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>

class User{
    private:
        std::string userId;
        std::string password;
        std::string userName;
        double total;

    public:
        /**
         * use to create new person
         */
        User(std::string password, std::string userName){
            this->userId = generateId();
            this->password = password;
            this->userName = userName;
            total = 0.0;
            saveUser();
        }
        
        void saveUser(){
            //USERID
            //PASSWORD
            //USERNAME
            //CURRNET TOTAL
            std::string x = userId;
            x.append(".txt");
            std::ofstream file(x);
            std::string y = userId;
            y.append("\n")
            .append(password)
            .append("\n")
            .append(userName)
            .append("\n")
            .append(std::to_string(total));
            file << y;
            file.close();
        }

        /**
         * use to load person
         */
        User(std::string userId, std::string password, std::string userName, double total){
            this->userId = userId;
            this->password = password;
            this->userName = userName;
            this->total = total;
        }
        std::string getUserName(){
            return userName;
        }

        

        static User loadUser(std::string username){
            std::string txt = username+=(".txt");
            std::ifstream file(txt);
            if(!file.is_open()){
                exit(1);
            }
            std::string line;
            int i = 0;
            std::vector<std::string> data;
            while(getline(file,line)){
                data.push_back(line);
            }
            return User(data[0],data[1],data[2],std::stod(data[3]));
        }
       
        void deposit(double t){
            if(t <=0 ){
                return;
            }
            else{
                total+=t;
            }
            saveUser();

        }

        void withdraw(double t){
            if(t <=0 ){
                return;
            }
            else if(t <= total){
                total-=t;
            }
            else{
                std::cout << "Insufficient Funds" << std::endl;
            }
            saveUser();
        }

        void printBalance(){
            std::cout << "My total balance today: R" << total <<std::endl;
        }

        double getTotal(){
            return total;
        }

        std::string generateId(){
            std::string lettersAndASCII =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQSTUVWXYZ0987654321";
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(0,lettersAndASCII.length());
            char* str = new char[4];
            for(int i = 0; i < 4; i++){
                std::uniform_int_distribution<int> dist(0,lettersAndASCII.length());
                int x = dist(mt);
                str[i] = lettersAndASCII[x];                
            }
            return str;
        }
    
        std::string getUserId(){
            return userId;
        }
        
        std::string getUserPassword(){
            return password;
        }
    };

#endif