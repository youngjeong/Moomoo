/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InRoomController.cpp
 * Author: admin
 * 
 * Created on 2017년 5월 28일 (일), 오후 8:05
 */

#include "InRoomController.h"
#include "UserMap.h"
#include "RoomMap.h"

void InRoomController::changeReadyStatus(int userno, int status) {
    UserMap *usermap_instance = UserMap::getInstance();
    auto usermap = usermap_instance->getMap();
    User current_user = usermap.find(userno)->second;
    
    RoomMap *roommap_instance = RoomMap::getInstance();
    auto roommap = roommap_instance->getRooms();
    Room current_room = roommap.find(current_user.getRoomNo())->second;
    
    //current_user.changeReady(status);
    auto users = current_room.GetUsers();
    for(int i=0;i<users.size();i++)
    {
    }
}

void InRoomController::gameStart() {

}


InRoomController::InRoomController() {
}

InRoomController::InRoomController(const InRoomController& orig) {
}

InRoomController::~InRoomController() {
}

