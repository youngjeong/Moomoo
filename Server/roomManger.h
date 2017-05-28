/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   roomManger.h
 * Author: admin
 *
 * Created on 2017년 5월 28일 (일), 오후 7:45
 */

#ifndef ROOMMANGER_H
#define ROOMMANGER_H

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<map>

using namespace std;

class roomManger {
public:
   
    virtual ~roomManger();
    static roomManger* getInstance();
private:
    
    
    static roomManger *instance;
    roomManger();
    
    roomManger(const roomManger& orig);
};

#endif /* ROOMMANGER_H */

