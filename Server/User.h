/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   User.h
 * Author: admin
 *
 * Created on 2017년 5월 28일 (일), 오후 6:03
 */

#ifndef USER_H
#define USER_H
#include<iostream>
#include<cstring>
#include<cstdlib>
class User {
public:
    User();
    User(const User& orig);
    virtual ~User();
    

    char* GetNickname() const {
        return nickname;
    }

    void SetNickname(char* nickname) {
        strcpy(this->nickname,nickname);
    }

    char* GetUsername() const {
        return username;
    }

    void SetUsername(char* username) {
        strcpy(this->username,username);
    }
    int GetRoomNumber() const {
        return roomNumber;
    }

    void SetRoomNumber(int roomNumber) {
        this->roomNumber = roomNumber;
    }

    int GetState() const {
        return state;
    }

    void SetState(int state) {
        this->state = state;
    }
    char* GetAccessToken() const {
        return accessToken;
    }

    void SetAccessToken(char* accessToken) {
        strcpy(this->accessToken,accessToken);
    }

    bool IsReady() const {
        return ready;
    }

    void SetReady(bool ready) {
        this->ready = ready;
    }

private:

    
    int sockNum;
    bool ready;
    char *username;
    char *nickname;
    char *accessToken;
    int roomNumber;
    int state;//in lobby : 1 in room : 2 in game : 3
    
};

#endif /* USER_H */

