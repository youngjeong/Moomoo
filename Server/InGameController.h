/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InGameController.h
 * Author: admin
 *
 * Created on 2017년 5월 28일 (일), 오후 8:05
 */

#ifndef INGAMECONTROLLER_H
#define INGAMECONTROLLER_H

#include "protocol.h"

class InGameController {
public:
    InGameController();
    InGameController(const InGameController& orig);
    static void changePlayerStatus(S_PROTOCOL_PLAYER_STATUS_CHANGED_REQ);
    static void endGame(S_PROTOCOL_GAME_END_REQ);
    virtual ~InGameController();
private:

};

#endif /* INGAMECONTROLLER_H */

