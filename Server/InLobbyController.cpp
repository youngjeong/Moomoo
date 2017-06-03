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
    
    puts("log1");
    map<int, Room> rooms=roomMapInstance->getRooms();
    puts("log2");
    
    map<int, Room>::iterator roomIter= rooms.find(req->room_no);
    printf("req->room_no : %d\n",req->room_no);
    puts("log3");
    
    Room selectedRoom=roomIter->second;
    puts("log4");
    
    if(roomIter->first!=req->room_no)
    {
        printf("join failed\n");
        printf("request room_no : %d found room_no : %d\n",req->room_no,roomIter->first);
        res->header.result=JOIN_TO_ROOM_DENIED;
        return;
    }
    
    printf("InLobbyController::joinToRoom  roomno : %d roomname : %s\n",selectedRoom.GetRoom_no(),selectedRoom.GetRoomName());
    
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
    
    printf("selectedRoom.getRoomUserCount() : %d\n",selectedRoom.getRoomUserCount());
    
    
    roomMapInstance->setRoomInPosition(req->room_no,selectedRoom);
    puts("log5");
            
    
    strcpy(res->room_name,selectedRoom.GetRoomName());
      puts("log6");
            
    res->header.result=SUCCESS;
      puts("log7");
            
}

void InLobbyController::makeRoom(S_PROTOCOL_LOBBY_MAKE_ROOM_REQ *req, S_PROTOCOL_LOBBY_MAKE_ROOM_ACK *res) {
    
    
    printf("InLobbyController::makeRoom req->room_name : %s\n",req->room_name);
    
    printf("InLobbyController::makeRoom req->header.userno : %d\n",req->header.userno);
    UserMap *usermapInstance = UserMap::getInstance();
    map<int, User> allUsers=usermapInstance->getMap();
    auto userIter = allUsers.find(req->header.userno);
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
    printf("room name : %s\n", newRoom.GetRoomName());
    newRoom.addUser(user);
    newRoom.SetRoomMaster(user);
    
    roommapInstance->addRoom(req->header.userno,newRoom);
    
   
    
    res->header.result=SUCCESS;
    strcpy(res->room_name,req->room_name);
    
    
    
    
}


void InLobbyController::getAllRooms(S_PROTOCOL_LOBBY_ROOMLIST_REQ *roomRequest,S_PROTOCOL_LOBBY_ROOMLIST_ACK * roomAck) {

    int i;
    roomAck->header=roomRequest->header;
    roomAck->header.protocolID=PROTOCOL_LOBBY_ROOMLIST_ACK;
    
    
    RoomMap * instance = RoomMap::getInstance();
    
    map<int, Room> roomMap =instance->getRooms();
    map<int, Room>::iterator it = roomMap.begin();
   
    //roomAck->count=roomMap.size();
    
 
    for(i=0,it = roomMap.begin(); it != roomMap.end() ;i++)
    {//return room size 16 fix;
        if(it!=roomMap.end()){
        strcpy(roomAck->rooms[i].roomName,  it->second.GetRoomName());
        roomAck->rooms[i].room_no=it->first;
        it++;
        
        }
        
        printf("InLobbyController::getAllRooms room_no : %d roomName : %s\n",
                roomAck->rooms[i].room_no,roomAck->rooms[i].roomName);
    
    }
    
    for ( ; i < 16 ; i ++ ) {
        memset(roomAck->rooms[i].roomName, 0, sizeof(roomAck->rooms[i].roomName));
            roomAck->rooms[i].room_no=0;
      printf("InLobbyController::getAllRooms room_no : %d roomName : %s\n",
                roomAck->rooms[i].room_no,roomAck->rooms[i].roomName);
    
    }
   
}

