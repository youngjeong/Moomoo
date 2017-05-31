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
#include<cstdio>
#include<cstdlib>
using namespace std;

class Room {
public:
    Room(int room_no, const char * room_name);
    Room();
    Room(Room *);
    Room(const Room& orig);
    virtual ~Room();
    char* GetRoomName() {
        return roomName;
    }

    void SetRoomName(char* roomName) {
        strcpy(this->roomName,roomName);
    }

    map<char*, User>* GetUsers() const {
        return users;
    }

    void SetUsers(map<char*, User>* users) {
        this->users = users;
    }
    
    int GetRoom_no() const {
        return room_no;
    }

    void SetRoom_no(int room_no) {
        this->room_no = room_no;
    }
    
    void addUser(User * user);
    

private:
    int room_no;
    char  roomName[50];
    map<char *,User> *users;
    User * roomMaster;

};

#endif /* ROOM_H */

