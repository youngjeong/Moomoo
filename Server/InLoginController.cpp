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
#include "DBConnect.h"

InLoginController::InLoginController() {
}


/* 
 * loginRequest
 * Parameter : S_PROTOCOL_LOGIN_REQ
 * Return Type : int
 * Return Value : Login result ( 1 = Success 0 = Fail )
 */
int InLoginController::loginRequest(S_PROTOCOL_LOGIN_REQ *msg) {
    printf("Recevied ID : %s\n", msg->id);
    printf("Recevied PW : %s\n", msg->password);
    
    DBConnect db;
    if(db.login(msg->id, msg->password)){
        printf("login error at server\n");
        return 0;
    }
    
    // Todo : print to log file
    printf("login success\n");
    return 1;
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

