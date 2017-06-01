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

Room::Room(int room_no, const char* room_name) {
    this->m_room_no=room_no;
    strcpy(this->m_roomName,room_name);
}

Room::Room(const Room& orig) {
}

void Room::addUser(User* user) {
    UserMap *userMapInstance= UserMap::getInstance();
    

}


Room::~Room() {
    puts("destroyer of Room Instance");
    
}
