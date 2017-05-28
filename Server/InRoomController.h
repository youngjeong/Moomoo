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

class InRoomController {
public:
    InRoomController();
    InRoomController(const InRoomController& orig);
    virtual ~InRoomController();
    static void checkReadyState();
    static void gameStart();
private:

};

#endif /* INROOMCONTROLLER_H */

