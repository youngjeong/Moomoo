/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   userManger.h
 * Author: admin
 *
 * Created on 2017년 5월 28일 (일), 오후 7:42
 */

#ifndef USERMANGER_H
#define USERMANGER_H
#include "User.h"
#include<iostream>
#include<cstring>
#include <map>
using namespace std;
class userManger {
public:
    
    
    virtual ~userManger();
    static userManger* getInstance();
    std::map<char*, User>* getUsers() const {
        return users;
    }

    void setUsers(std::map<char*, User>* users) {
        this->users = users;
    }

private:
    std::map<char *,User> *users;
    
    static userManger *instance;
    userManger();
    userManger(const userManger& orig);
};

#endif /* USERMANGER_H */

