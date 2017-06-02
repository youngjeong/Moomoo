/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Room.cpp
 * Author: admin
 * 
 * Created on 2017년 5월 28일 (일), 오후 8:08
 */

#include "Room.h"

Room::Room() {

}


Room::Room(int room_no, const  char* room_name) {
    this->m_room_no=room_no;
    strcpy(this->m_roomName,room_name);
    
}

void Room::addUser(User user) {
    
    this->m_users.push_back(user);
    cout<<"addUser after m_users count : "<<this->m_users.size()<<"\n";
   // this->m_users.insert(make_pair(m_users.size(),user));

}

int Room::getRoomUserCount() {
    return this->m_users.size();
}

bool Room::isRoomFull() {

    if(this->m_users.size()<4)
        return false;
    else if(this->m_users.size()==4)
        return true;
}

Room::~Room() {
    puts("destroyer of Room Instance");
    
}
