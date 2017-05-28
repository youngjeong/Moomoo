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

class InLobbyController {
public:
    InLobbyController();
    InLobbyController(const InLobbyController& orig);
    virtual ~InLobbyController();
    static void getRooms();
    static void getWaitingUsers();
private:

};

#endif /* INLOBBYCONTROLLER_H */

