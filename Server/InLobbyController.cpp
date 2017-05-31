/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InLobbyController.cpp
 * Author: admin
 * 
 * Created on 2017년 5월 28일 (일), 오후 8:04
 */

#include <cstdlib>

#include "InLobbyController.h"
#include "protocol.h"

InLobbyController::InLobbyController() {
}

InLobbyController::InLobbyController(const InLobbyController& orig) {
}

InLobbyController::~InLobbyController() {
}

void InLobbyController::getWaitingUsers() {

    
}

void InLobbyController::joinToRoom() {

}

void InLobbyController::makeRoom() {

}

void InLobbyController::debugTest(int room_no, Room &room_obj) {

    RoomMap *instance = RoomMap::getInstance();
    map<int,Room> map=instance->getRooms();
    map.insert(pair<int,Room>(room_no,room_obj));


}


void InLobbyController::getAllRooms(S_PROTOCOL_LOBBY_ROOMLIST_REQ *roomRequest,S_PROTOCOL_LOBBY_ROOMLIST_ACK * roomAck) {

    int i;
    roomAck->header=roomRequest->header;
    roomAck->header.protocolID=PROTOCOL_LOBBY_ROOMLIST_ACK;
    
    
    //todo result에 어떤 값 들어가야?
    
    RoomMap * instance = RoomMap::getInstance();
    
    map<int, Room> roomMap =instance->getRooms();
    map<int, Room>::iterator it = roomMap.begin();
    
    
    
    roomAck->count=roomMap.size();
 
    for(i=0,it = roomMap.begin();it!=roomMap.end();++it,i++)
    {
        strcpy(roomAck->rooms[i].roomName,  it->second.GetRoomName());
        roomAck->rooms[i].room_no=it->first;
        
        
    }        
    
    
    
    
}

