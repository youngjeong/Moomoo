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

void RoomMap::addRoom(int room_no, Room room_obj) {

    rooms.insert({room_no,room_obj});
}

void RoomMap::delRoom(int room_no, Room room_obj) {
    auto it = rooms.find(room_no);
    if(it=rooms.end())
        return;
    else
        rooms.erase(it);
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

std::map<char*, Room> RoomMap::getRooms() {

    if(instance==NULL)
        return NULL;
    else
        return rooms;
}


RoomMap::RoomMap(const RoomMap& orig) {
}

RoomMap::~RoomMap() {
}
