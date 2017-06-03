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

User::User() {

}


User::User(int sockNum, int userno, char *username, char *nickname) {
    m_sockNum = sockNum;
    m_userno = userno;
    strcpy(m_id, username);
    strcpy(m_nickname, nickname);
}

User::~User() {
}


int User::getSockNum() {
    return m_sockNum;
}

int User::getuserno(){
    return m_userno;
}
char* User::getId() {
    return m_id;
}

char* User::getNickname() {
    return m_nickname;
}

int User::getRoomNo() {
    return m_roomNumber;
}

int User::setRoomNo(int roomno){
    m_roomNumber = roomno;
}
int User::getStatus() {
    return m_state;
}

bool User::getReady() {
    return m_ready;
}
void User::changeReady(int readyStatus){    
    m_ready = readyStatus;
}

void User::changeStatus(int status){
    m_state = status;
}