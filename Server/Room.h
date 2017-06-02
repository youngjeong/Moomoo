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
#include "UserMap.h"
#include<cstdio>
#include<cstdlib>
#include <iostream>
using namespace std;

class Room {
public:
    Room(int room_no, const char * room_name);
    Room();
    Room(const Room& orig);
    virtual ~Room();
    char* GetRoomName() {
        return m_roomName;
    }

    void SetRoomName(char* roomName) {
        strcpy(this->m_roomName,roomName);
    }

    vector<User> GetUsers()  {
        return m_users;
    }

    void SetUsers(vector<User> users) {
        this->m_users = users;
    }
    
    int GetRoom_no() {
        return m_room_no;
    }

    void SetRoom_no(int room_no) {
        this->m_room_no = room_no;
    }
    
    void addUser(User user);
  
    
      User* GetRoomMaster()  {
        return roomMaster;
    }

    void SetRoomMaster(User* roomMaster) {
        this->roomMaster = roomMaster;
    }

    bool isRoomFull();
    
    int getRoomUserCount();
private:
    
    int m_room_no;//room_no is roomMaster's user_no
    
    char  m_roomName[50];
    vector<User> m_users;
    User * roomMaster;

};

#endif /* ROOM_H */

