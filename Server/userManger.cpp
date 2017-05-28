/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   userManger.cpp
 * Author: admin
 * 
 * Created on 2017년 5월 28일 (일), 오후 7:42
 */

#include "userManger.h"
userManger* userManger::instance = NULL;
map<char *, User> *users;

userManger::userManger() {
}

userManger::userManger(const userManger& orig) {
}

userManger::~userManger() {
}

userManger* userManger::getInstance()
{
    if(instance==NULL)
    {
        instance= new userManger();
        return instance;
    }
    else
        return instance;
}

