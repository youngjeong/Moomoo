/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   roomManger.cpp
 * Author: admin
 * 
 * Created on 2017년 5월 28일 (일), 오후 7:45
 */

#include "roomManger.h"

roomManger * roomManger::instance=NULL;

roomManger::roomManger() {
}

roomManger::roomManger(const roomManger& orig) {
}

roomManger* roomManger::getInstance() {

    if(instance ==NULL)
    {
        instance = new roomManger();
        return instance;
    }
    else
        return instance;
}


roomManger::~roomManger() {
}

