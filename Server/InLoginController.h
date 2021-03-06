/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InLoginController.h
 * Author: admin
 *
 * Created on 2017년 5월 28일 (일), 오후 8:05
 */

#ifndef INLOGINCONTROLLER_H
#define INLOGINCONTROLLER_H
#include "protocol.h"

#include<iostream>
#include<cstdio>
#include"Communicator.h"
#include"DBConnect.h"

class InLoginController {
public:
    InLoginController();
    InLoginController(const InLoginController& orig);
    virtual ~InLoginController();

    static S_PROTOCOL_LOGIN_ACK loginRequest(S_PROTOCOL_LOGIN_REQ*, int sockno);
    static int signUpRequest(S_PROTOCOL_JOIN_REQ*);
    
private:

};

#endif /* INLOGINCONTROLLER_H */

