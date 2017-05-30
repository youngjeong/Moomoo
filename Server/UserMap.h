/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   usermap.h
 * Author: eldkq
 *
 * Created on 2017년 5월 30일 (화), 오후 5:09
 */

#ifndef USERMAP_H
#define USERMAP_H

#include<map>
#include<string.h>
#include "User.h"
using namespace std;

class UserMap{ // In Lobby
private:
    UserMap(){};
    static bool UserMapFlag;
    static UserMap* instance;
    std::map<int, User> usermap;
    
public:
    static UserMap* getInstance();
    
    virtual ~UserMap(){
        UserMapFlag=false;
    };
    int getSize();
    void addUser(int, User);
    void delUser(int);
    map<int, User> getMap();
};

#endif /* USERMAP_H */

