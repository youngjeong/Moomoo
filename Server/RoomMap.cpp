/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RoomMap.cpp
 * Author: admin
 * 
 * Created on 2017년 5월 30일 (화), 오후 8:58
 */

#include "RoomMap.h"

RoomMap * RoomMap::instance = NULL;

RoomMap::RoomMap() {
    
}

void RoomMap::setRoomInPosition(int pos, Room room_obj) {
    this->rooms[pos]=room_obj;
}

void RoomMap::addRoom(int room_no, Room room_obj) {

   
    rooms.insert(make_pair(room_no, room_obj));
    
  
}

void RoomMap::delRoom(int room_no, Room room_obj) {
    
    map<int, Room>::iterator iter = rooms.begin();
    
    iter = rooms.find(room_no);
   
    if(iter==rooms.end())
        return;
    else
        rooms.erase(iter);
}

RoomMap* RoomMap::getInstance() {

    if(instance==NULL)
    {
        instance= new RoomMap();
        return instance;
    }
    else
        return instance;
}

int RoomMap::getRoomSize() {
    if(instance==NULL)
        return -1;
    else
       return rooms.size();
}
void RoomMap::updateRoomUsers(int room_no, vector<User> users){
    auto it = rooms.begin();
    for(;it!=rooms.end();it++){
        if(it->first == room_no){
            it->second.SetUsers(users);
        }
    }
}
std::map<int, Room> RoomMap::getRooms() {

        return rooms;
}


RoomMap::RoomMap(const RoomMap& orig) {
}

RoomMap::~RoomMap() {
}
