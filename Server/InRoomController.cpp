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

#include <unistd.h>
#include "InRoomController.h"
#include "protocol.h"
#include "Communicator.h"
#include "UserMap.h"
#include "RoomMap.h"
#include "errorcode.h"

void InRoomController::changeReadyStatus(int userno, int status) {
    UserMap *usermap_instance = UserMap::getInstance();
    auto usermap = usermap_instance->getMap();
    User current_user = usermap.find(userno)->second;
    
    RoomMap *roommap_instance = RoomMap::getInstance();
    auto roommap = roommap_instance->getRooms();
    Room current_room = roommap.find(current_user.getRoomNo())->second;
    
    current_user.changeReady(status);
    usermap_instance->updateUser(current_user.getuserno(), current_user);
    
    vector<int> user_socklist;
    auto userlist = current_room.GetUsers();
    for(int i=0;i<userlist.size();i++){
        if(userlist[i].getuserno() == userno){
            userlist[i].changeReady(status);
        }
        user_socklist.push_back(userlist[i].getSockNum());
    }
    roommap_instance->updateRoomUsers(current_user.getRoomNo(), userlist);
    S_PROTOCOL_ROOM_PLAYER_LIST_ACK ack_msg;
    ack_msg.header.protocolID = PROTOCOL_ROOM_PLAYER_LIST_ACK;
    ack_msg.count = userlist.size();
    for(int i=0;i<userlist.size();i++){
        strcpy(ack_msg.players[i].nickname, userlist[i].getNickname());
        if(userlist[i].getReady()){
            ack_msg.players[i].ready_status = 1;
        }
        else
            ack_msg.players[i].ready_status = 0;
    }
    for(int i=0;i<userlist.size();i++){
        write(userlist[i].getSockNum(), &ack_msg, sizeof(ack_msg));
    }
    
    gameStart(userno);
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

    for(int i=0;i<user_socklist.size();i++)
    {
        write(user_socklist[i], &ack_msg, sizeof(ack_msg));
    }
}
void InRoomController::gameStart(int userno) 
{
    S_PROTOCOL_PLAYER_GAME_START_ACK ack_msg;
    memset(&ack_msg,0,sizeof(ack_msg));
    auto usermap_instance = UserMap::getInstance();
    auto usermap = usermap_instance->getMap();
    User current_user = usermap.find(userno)->second;
       
    auto roommap_instance = RoomMap::getInstance();
    auto roommap = roommap_instance->getRooms();
    Room current_room = roommap.find(userno)->second;
    
    auto roomUsers = current_room.GetUsers();
    
    bool res = gameStartValidator(current_user.getRoomNo());
    ack_msg.header.protocolID = PROTOCOL_PLAYER_GAME_START_ACK;
    if(res && roomUsers.size() > 1){ // Enable to start game
        ack_msg.header.result=SUCCESS;
        
        for(int i=0;i<roomUsers.size();i++){
            write(roomUsers[i].getSockNum(), &ack_msg, sizeof(ack_msg));
        }
    }
}

bool InRoomController::gameStartValidator(int roomno)
{
    auto roommap_instance = RoomMap::getInstance();
    auto roommap = roommap_instance->getRooms();
    Room current_room = roommap.find(roomno)->second;
    
    auto roomUsers = current_room.GetUsers();
    bool ret=true;
    
    for(int i=0;i<roomUsers.size();i++){
        if(!roomUsers[i].getReady())
            ret = false;
    }
    if(ret){
         for(int i=0;i<roomUsers.size();i++){
             roomUsers[i].changeStatus(INGAME);
        }
    }
    return ret;
}

void InRoomController::getRoomUserList(S_PROTOCOL_ROOM_PLAYER_LIST_REQ req_msg){
    S_PROTOCOL_ROOM_PLAYER_LIST_ACK ack_msg;
    memset(&ack_msg,0,sizeof(ack_msg));
    auto usermap_instance = UserMap::getInstance();
    auto usermap = usermap_instance->getMap();
    User current_user = usermap.find(req_msg.header.userno)->second;
       
    auto roommap_instance = RoomMap::getInstance();
    auto roommap = roommap_instance->getRooms();
    Room current_room = roommap.find(req_msg.header.userno)->second;
   
    auto roomUsers = current_room.GetUsers();
    ack_msg.header.protocolID = PROTOCOL_ROOM_PLAYER_LIST_ACK;
    ack_msg.count = roomUsers.size();
    for(int i=0;i<roomUsers.size();i++){
        if(roomUsers[i].getReady())
            ack_msg.players[i].ready_status = 1;
        else
            ack_msg.players[i].ready_status = 0;
        
        strcpy(ack_msg.players[i].nickname, roomUsers[i].getNickname());
    }
    write(current_user.getSockNum(), &ack_msg, sizeof(ack_msg));
}

void InRoomController::exitAtRoom(S_PROTOCOL_ROOM_EXIT_REQ req_msg){
    auto usermap_instance = UserMap::getInstance();
    auto usermap = usermap_instance->getMap();
    User current_user = usermap.find(req_msg.header.userno)->second;
    int roomno = current_user.getRoomNo();   
    auto roommap_instance = RoomMap::getInstance();
    auto roommap = roommap_instance->getRooms();
    Room current_room = roommap.find(req_msg.header.userno)->second;
    auto roomUsers = current_room.GetUsers();
    
    current_user.changeStatus(INLOBBY);
    current_user.setRoomNo(0);
    usermap_instance->updateUser(current_user.getuserno(), current_user);
    
    for(int i=0;i<roomUsers.size();i++){
        if(strcmp(roomUsers[i].getId(), current_user.getId())==0){
            roomUsers.erase(roomUsers.begin()+i);
            break;
        }
    }
    roommap_instance->updateRoomUsers(roomno, roomUsers);
    
    S_PROTOCOL_ROOM_PLAYER_LIST_ACK ack_msg;
    ack_msg.header.protocolID = PROTOCOL_ROOM_PLAYER_LIST_ACK;
    ack_msg.count = roomUsers.size();
    for(int i=0;i<roomUsers.size();i++){
        strcpy(ack_msg.players[i].nickname, roomUsers[i].getNickname());
        if(roomUsers[i].getReady()){
            ack_msg.players[i].ready_status = 1;
        }
        else
            ack_msg.players[i].ready_status = 0;
    }
    for(int i=0;i<roomUsers.size();i++){
        write(roomUsers[i].getSockNum(), &ack_msg, sizeof(ack_msg));
    }
    
    S_PROTOCOL_ROOM_EXIT_ACK exit_ack;
    exit_ack.header.protocolID = PROTOCOL_ROOM_EXIT_ACK;
    write(current_user.getSockNum(), &exit_ack, sizeof(exit_ack));
}
InRoomController::InRoomController() {
}

InRoomController::InRoomController(const InRoomController& orig) {
}

InRoomController::~InRoomController() {
}

