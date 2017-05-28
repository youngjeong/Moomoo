/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.cpp
 * Author: admin
 * 
 * Created on 2017년 5월 28일 (일), 오후 6:03
 */

#include "User.h"

User::User() {
    
    username=(char *)malloc(sizeof(char )*16);
    nickname=(char *)malloc(sizeof(char )*16);
    accessToken=(char *)malloc(sizeof(char )*16);
    ready=false;
}

User::User(const User& orig) {
}

User::~User() {
}

