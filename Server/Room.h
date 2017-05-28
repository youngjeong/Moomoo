/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Room.h
 * Author: admin
 *
 * Created on 2017년 5월 28일 (일), 오후 8:08
 */

#ifndef ROOM_H
#define ROOM_H
#include<map>
#include<vector>
#include"User.h"
using namespace std;

class Room {
public:
    Room();
    Room(const Room& orig);
    virtual ~Room();
    char* GetRoomName() const {
        return roomName;
    }

    void SetRoomName(char* roomName) {
        this->roomName = roomName;
    }

    map<char*, User>* GetUsers() const {
        return users;
    }

    void SetUsers(map<char*, User>* users) {
        this->users = users;
    }

private:
    char * roomName;
    map<char *,User> *users;
    User * roomMaster;

};

#endif /* ROOM_H */

