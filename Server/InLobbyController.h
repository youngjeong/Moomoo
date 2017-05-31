/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InLobbyController.h
 * Author: admin
 *
 * Created on 2017년 5월 28일 (일), 오후 8:04
 */

#ifndef INLOBBYCONTROLLER_H
#define INLOBBYCONTROLLER_H
#include "protocol.h"
#include<cstdio>
#include"RoomMap.h"
#include "Room.h"
#include <iostream>
using namespace std;

class InLobbyController {
    //Todo debugTest must be removed
    //debugTest : make room for testing
public:
    InLobbyController();
    InLobbyController(const InLobbyController& orig);
    virtual ~InLobbyController();
    static void getAllRooms(S_PROTOCOL_LOBBY_ROOMLIST_REQ* req,S_PROTOCOL_LOBBY_ROOMLIST_ACK *result);
    static void getWaitingUsers();
    static void makeRoom();
    static void joinToRoom();
    static void debugTest(int room_no, Room &room_obj);
    
private:

};

#endif /* INLOBBYCONTROLLER_H */

