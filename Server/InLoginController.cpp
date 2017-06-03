/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InLoginController.cpp
 * Author: admin
 * 
 * Created on 2017년 5월 28일 (일), 오후 8:05

 *  */
#include <stdio.h>
#include "InLoginController.h"
#include "User.h"
#include "DBConnect.h"
#include "UserMap.h"
#include "errorcode.h"

InLoginController::InLoginController() {
}


/* 
 * loginRequest
 * Parameter : S_PROTOCOL_LOGIN_REQ
 * Return Type : S_PROTOCOL_LOGIN_ACK
 * Return Value : Login result ( 1 = Success 0 = Fail )
 */
S_PROTOCOL_LOGIN_ACK InLoginController::loginRequest(S_PROTOCOL_LOGIN_REQ *msg, int sockno) {
    printf("Recevied ID : %s\n", msg->id);
    printf("Recevied PW : %s\n", msg->password);
    
    S_PROTOCOL_LOGIN_ACK ack_msg;
    DBConnect db;
    int login_result =  db.login(msg->id, msg->password);
    ack_msg.header.protocolID = PROTOCOL_LOGIN_ACK;
    ack_msg.header.result = login_result;
    
    if(login_result == SUCCESS)
    {
        UserMap *usermap_instance = UserMap::getInstance();
        userinfo info;
        db.searchUserInfo(msg->id, &info);
        int userno=db.getUserKeyWithId(info.id);
        User user(sockno, userno, info.id, info.nickname);
        //int userno = usermap_instance->getLastno();
        //userno should be primary key of DB
        
        printf("InLoginController::loginRequest userno : %d\n",userno);
        usermap_instance->addUser(userno, user);
        ack_msg.header.userno = userno;
    }
    
    return ack_msg;
}

/* 
 * signUpRequest
 * Parameter : S_PROTOCOL_JOIN_REQ
 * Return Type : int
 * Return Value : Join result ( 1 = Success 0 = Fail )
 */
int InLoginController::signUpRequest(S_PROTOCOL_JOIN_REQ *msg) {
    printf("Received ID : %s\n", msg->id);
    printf("Received PW : %s\n", msg->password);
    printf("Received Nick : %s\n", msg->nickname);
    DBConnect db;
    return db.signUp(msg->id, msg->password, msg->nickname);
}

InLoginController::InLoginController(const InLoginController& orig) {
}

InLoginController::~InLoginController() {
}

