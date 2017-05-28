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

class InLoginController {
public:
    InLoginController();
    InLoginController(const InLoginController& orig);
    virtual ~InLoginController();
    static void loginRequest();
    static void signUpRequest();
    
private:

};

#endif /* INLOGINCONTROLLER_H */

