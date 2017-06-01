/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InRoomController.h
 * Author: admin
 *
 * Created on 2017년 5월 28일 (일), 오후 8:05
 */

#ifndef INROOMCONTROLLER_H
#define INROOMCONTROLLER_H

#include "protocol.h"

class InRoomController {
public:
    InRoomController();
    InRoomController(const InRoomController& orig);
    virtual ~InRoomController();
    static void changeReadyStatus(int, int);
    static void chatRoom(S_PROTOCOL_CHAT_REQ);
    static void gameStart();
private:
    static bool gameStartValidator(int);
};

#endif /* INROOMCONTROLLER_H */

