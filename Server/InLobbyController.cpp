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
#include "errorcode.h"
InLobbyController::InLobbyController() {
}

InLobbyController::InLobbyController(const InLobbyController& orig) {
}

InLobbyController::~InLobbyController() {
}

void InLobbyController::getWaitingUsers() {

    
}

void InLobbyController::joinToRoom(S_PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ *req, S_PROTOCOL_LOBBY_JOIN_TO_ROOM_ACK *res) {
    //find req->room_no, move user to usermap in room Instance,change user status
    
    RoomMap *roomMapInstance = RoomMap::getInstance();
    map<int, Room> rooms=roomMapInstance->getRooms();

    
    
    map<int, Room>::iterator roomIter= rooms.find(req->room_no);
    Room selectedRoom=roomIter->second;
    printf("InLobbyController::joinToRoom  roomno : %d roomname : %s",selectedRoom.GetRoom_no(),selectedRoom.GetRoomName());
    
   
    
    UserMap *userMapInstance = UserMap::getInstance();
    map<int, User > allUsers= userMapInstance->getMap();
    map<int, User>::iterator userIter;
    
    //map<int, User*> usersInRoom = selectedRoom->GetUsers();
    //vector<User> usersInRoom = selectedRoom->GetUsers();
    
    
    //printf("InLobbyController::joinToRoom  selectedRoom member count%d\n",usersInRoom.size());
    
    if(selectedRoom.isRoomFull()){
        res->header.result=JOIN_TO_ROOM_DENIED;
        return;
    }
    
    userIter=allUsers.find(req->header.userno);
    //int room_member_num=rooms.size();
    User newUser(userIter->second.getSockNum(),userIter->second.getId(),userIter->second.getNickname());
    
    userIter->second.changeStatus(INROOM);
    
    
    
    selectedRoom.addUser(newUser);
    res->header.result=JOIN_TO_ROOM_OK;
    
}

void InLobbyController::makeRoom(S_PROTOCOL_LOBBY_MAKE_ROOM_REQ *req, S_PROTOCOL_LOBBY_MAKE_ROOM_ACK *res) {
    
    
    printf("InLobbyController::makeRoom req->room_name : %s\n",req->room_name);
    
    printf("InLobbyController::makeRoom req->header.userno : %d\n",req->header.userno);
    UserMap *usermapInstance = UserMap::getInstance();
    map<int, User> allUsers=usermapInstance->getMap();
    map<int, User>::iterator userIter;
    userIter = allUsers.find(req->header.userno);
    userIter->second.changeStatus(INROOM);
   
    
    User user(userIter->second.getSockNum(),userIter->second.getId(),userIter->second.getNickname());
    user.changeStatus(INROOM);//same user info, different user instance;
    
    
    RoomMap *roommapInstance = RoomMap::getInstance();
    map<int, Room> allRooms = roommapInstance->getRooms();
    map<int, Room>::iterator roomIter = allRooms.begin();
    
    Room cursor;
    for(;roomIter!=allRooms.end();roomIter++)
    {
        cursor=roomIter->second;
        if(strcmp(cursor.GetRoomName(),req->room_name)==0)
        {
            res->header.result=ROOM_ALREADY_EXISTING_NAME;
            return;
        }
    }
     
    
//    
//    Room *newRoom=new Room(req->header.userno,req->room_name);
//    newRoom->addUser(&user);//roomMaster & first joined user;
//    newRoom->SetRoomMaster(&user);//roomMaster
//    
    
    Room newRoom(req->header.userno,req->room_name);
    newRoom.addUser(user);
    newRoom.SetRoomMaster(&user);
    
    
    roommapInstance->addRoom(req->header.userno,newRoom);
    res->header.result=ROOM_MAKE_SUCCESSFULLY;
    
    
    
    
}

void InLobbyController::debugTest(int room_no, Room &room_obj) {
    //Todo : debugTest must be removed
    //debugTest adds room for testing
     RoomMap * instance = RoomMap::getInstance();
     
     
     //instance->addRoom(room_no,room_obj);

        
}


void InLobbyController::getAllRooms(S_PROTOCOL_LOBBY_ROOMLIST_REQ *roomRequest,S_PROTOCOL_LOBBY_ROOMLIST_ACK * roomAck) {

    int i;
    roomAck->header=roomRequest->header;
    roomAck->header.protocolID=PROTOCOL_LOBBY_ROOMLIST_ACK;
    
    
    RoomMap * instance = RoomMap::getInstance();
    
    map<int, Room> roomMap =instance->getRooms();
    map<int, Room>::iterator it = roomMap.begin();
    
    
    
    roomAck->count=roomMap.size();
    
 
    for(i=0,it = roomMap.begin();it!=roomMap.end();it++,i++)
    {
        strcpy(roomAck->rooms[i].roomName,  it->second.GetRoomName());
        roomAck->rooms[i].room_no=it->first;
        printf("InLobbyController::getAllRooms room_no : %d roomName : %s\n",
                roomAck->rooms[i].room_no,roomAck->rooms[i].roomName);
    }        
   
}

