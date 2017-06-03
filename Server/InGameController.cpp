/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InGameController.cpp
 * Author: admin
 * 
 * Created on 2017년 5월 28일 (일), 오후 8:05
 */

#include<unistd.h>
#include "InGameController.h"
#include "UserMap.h"
#include "RoomMap.h"

InGameController::InGameController() {
}

InGameController::InGameController(const InGameController& orig) {
}

void InGameController::changePlayerStatus(S_PROTOCOL_PLAYER_STATUS_CHANGED_REQ req_msg){
    S_PROTOCOL_PLAYER_STATUS_CHANGED_ACK ack_msg;
    auto usermap_instance = UserMap::getInstance();
    auto usermap = usermap_instance->getMap();
    User current_user = usermap.find(req_msg.header.userno)->second;
    
    auto roommap_instance = RoomMap::getInstance();
    auto roommap = roommap_instance->getRooms();
    auto current_room = roommap.find(req_msg.header.userno)->second;
    auto userlist = current_room.GetUsers();
    
    ack_msg.userID = req_msg.header.userno;
    ack_msg.x_coord = req_msg.x_coord;
    ack_msg.y_coord = req_msg.y_coord;
    ack_msg.direction = req_msg.direction;
    
    for(int i=0;i<userlist.size();i++){
        write(userlist[i].getSockNum(), &ack_msg, sizeof(ack_msg));
    }
}

void InGameController::endGame(S_PROTOCOL_GAME_END_REQ req_msg){
    S_PROTOCOL_GAME_END_ACK ack_msg;
    auto usermap_instance = UserMap::getInstance();
    auto usermap = usermap_instance->getMap();
    User current_user = usermap.find(req_msg.header.userno)->second;
    
    auto roommap_instance = RoomMap::getInstance();
    auto roommap = roommap_instance->getRooms();
    auto current_room = roommap.find(req_msg.header.userno)->second;
    auto userlist = current_room.GetUsers();
    
    for(int i=0;i<userlist.size();i++){
        userlist[i].changeStatus(INLOBBY);
        userlist[i].changeReady(NOT_READY);
    }
    roommap_instance->updateRoomUsers(current_user.getuserno(), userlist);
    ack_msg.header.protocolID = PROTOCOL_GAME_END_ACK;
    ack_msg.win_userID = req_msg.header.userno;
    for(int i=0;i<userlist.size();i++){
        write(userlist[i].getSockNum(), &ack_msg, sizeof(ack_msg));
    }
    
    
}
InGameController::~InGameController() {
}

