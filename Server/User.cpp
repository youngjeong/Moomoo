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

#include <string.h>
#include "protocol.h"
#include "User.h"

User::User(int sockNum, char *username, char *nickname) {
    m_sockNum = sockNum;
    strcpy(m_username, username);
    strcpy(m_nickname, nickname);
}

User::~User() {
}

int User::getSockNum() {
    return m_sockNum;
}

char* User::getUsername() {
    return m_username;
}

char* User::getNickname() {
    return m_nickname;
}

int User::getRoomNo() {
    return m_roomNumber;
}

int User::getStatus() {
    return m_state;
}

void User::changeReady(int readyStatus){    
    m_ready = readyStatus;
}

void User::changeStatus(int status){
    m_state = status;
}