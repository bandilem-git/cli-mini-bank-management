#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <dirent.h>
#include "User.h"

class Bank{
    private:
        std::vector<User> users;
    public:
        std::vector<std::string> fileData(std::string file){
            std::ifstream f(file);

            std::string line;
            std::vector<std::string> toReturn;
            while(getline(f,line)){
                toReturn.push_back(line);
            }
            return toReturn;

        }
        
        bool isTxt(std::string x){
            if (x.empty()) return false;

            for(int i = 0; i < x.length() ; i++){
                if(x[i] == '.'){
                    std::string sub = x.substr(i+1,3);
                    if(sub == "txt"){
                        
                        return true;
                    }
                    return false;
                }
            }
            return false;
        }

        Bank(){

            DIR* directory ;
            struct dirent *en;
            directory = opendir(".");
            if(directory){
                while((en = readdir(directory))!= NULL){
                    std::string file = en->d_name;
                    if(isTxt(file)){ 
                        // std::cout<< "adding file: " << file;
                        std::string sub = file.substr(0,file.length()-4);
                        // std::cout <<"substring without .txt:  " <<sub<<std::endl;
                        users.push_back(User::loadUser(sub));
                    }
                }
                int is_closed = closedir(directory);
            }
        }

        std::string findUserByName(std::string n){
            for(int i = 0; i < users.size(); i++){
                if(users[i].getUserName() == n){
                    return users[i].getUserId();
                }
            }
            return "";
        }

        User loadUser(std::string x){
            return User::loadUser(findUserByName(x));
        }
        
        bool createUser(std::string username, std::string password){
            for(int i = 0; i < users.size(); i++){
                if(users[i].getUserName() == username){
                    return false;
                }
            }
            users.push_back(User(password,username));
            return true;
        }

        bool deleteUser(std::string username){
            std::string x ="";
            std::string id = findUserByName(username);
            x.append(id);
            x.append(".txt");
            for(std::vector<User>::iterator x = users.begin(); x != users.end()++; x++){
                User rem = *x.base();
                if(rem.getUserName() == username){
                    users.erase(x);
                }
            }
            int size = x.length();
            char* f = new char[size];

            for(int i = 0; i < size; i++){
                f[i] = x[i];
            }

            int wasRemoved = std::remove(f);

            delete[] f;
            f = nullptr;

            return wasRemoved;
        }
    
        void printUsers(){
            for(int i = 0; i < users.size(); i++){
                std::cout <<i+1 <<" : "<<users[i].getUserName();
                if(i != users.size()-1){
                    std::cout << " -> ";

                }
                std::cout<<std::endl;
            }
        }

        void printTotal(){
            double toReturn = 0.0;
            for(User x: users){
                toReturn+=x.getTotal();
            }
            std::cout << "R: "<< toReturn <<std::endl;
        }
    
        void deposit(std::string username,std::string pass, double amount){
            for(User x : users){
                if(x.getUserName() == username && x.getUserPassword() == pass){
                    x.deposit(amount);
                    return;
                }
            }
            std::cout <<"username or password may be wrong"<<std::endl;
        }

        void withdraw(std::string username, std::string pass, double amount){
            for(User x : users){
                if(x.getUserName() == username && x.getUserPassword() == pass){
                    x.withdraw(amount);
                    return;
                }

            }
            
            std::cout <<"username or password may be wrong"<<std::endl;

        }
    };

#endif