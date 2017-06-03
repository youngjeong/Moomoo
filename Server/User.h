/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.h
 * Author: admin
 *
 * Created on 2017년 5월 28일 (일), 오후 6:03
 */

#ifndef USER_H
#define USER_H
#include<iostream>
#include<cstring>
#include<cstdlib>
class User {
public:
    User(int, char*, char*); 
    virtual ~User();
    User();
    
    int getSockNum();
    char *getId();
    char *getNickname();
    int getRoomNo();
    int getStatus();
    bool getReady();
    void changeReady(int);
    void changeStatus(int);
  
private:  
    int m_sockNum;
    bool m_ready;
    char m_id[16];
    char m_nickname[16];
    int m_roomNumber;
    int m_state;//in lobby : 1 in room : 2 in game : 3
    
};

#endif /* USER_H */

