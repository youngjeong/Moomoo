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
#include "protocol.h"
#include "Communicator.h"
#include "UserMap.h"
#include "RoomMap.h"

void InRoomController::changeReadyStatus(int userno, int status) {
    UserMap *usermap_instance = UserMap::getInstance();
    auto usermap = usermap_instance->getMap();
    User current_user = usermap.find(userno)->second;
    
    RoomMap *roommap_instance = RoomMap::getInstance();
    auto roommap = roommap_instance->getRooms();
    Room current_room = roommap.find(current_user.getRoomNo())->second;
    
    current_user.changeReady(status);
    vector<int> user_socklist;
    auto userlist = current_room.GetUsers();
    for(int i=0;i<userlist.size();i++){
        user_socklist.push_back(userlist[i].getSockNum());
    }
    S_PROTOCOL_PLAYER_CHANGE_READY_STATUS_ACK ack_msg;
    ack_msg.changed_user_no = userno;
    ack_msg.status = status;
    ack_msg.header.protocolID = PROTOCOL_PLAYER_CHANGE_READY_STATUS_ACK;
    Communicator::writeMultiClient(user_socklist, ack_msg);
}

void InRoomController::chatRoom(S_PROTOCOL_CHAT_REQ req_msg){
    int userno = req_msg.header.userno;
    UserMap *usermap_instance = UserMap::getInstance();
    auto usermap = usermap_instance->getMap();
    User current_user = usermap.find(userno)->second;
    
    RoomMap *roommap_instance = RoomMap::getInstance();
    auto roommap = roommap_instance->getRooms();
    Room current_room = roommap.find(current_user.getRoomNo())->second;
    
    vector<int> user_socklist;
    auto userlist = current_room.GetUsers();
    for(int i=0;i<userlist.size();i++){
        user_socklist.push_back(userlist[i].getSockNum());
    }
    
    S_PROTOCOL_CHAT_ACK ack_msg;
    ack_msg.header.protocolID = PROTOCOL_CHAT_ACK;
    strcpy(ack_msg.nickname, current_user.getNickname());
    strcpy(ack_msg.message, req_msg.message);
    
    Communicator::writeMultiClient(user_socklist, ack_msg);
}
void InRoomController::gameStart(S_PROTOCOL_PLAYER_CLICK_GAME_START_REQ req_msg) {
    
}

bool InRoomController::gameStartValidator(int roomno)
{
    
}


InRoomController::InRoomController() {
}

InRoomController::InRoomController(const InRoomController& orig) {
}

InRoomController::~InRoomController() {
}

