/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RoomMap.h
 * Author: admin
 *
 * Created on 2017년 5월 30일 (화), 오후 8:15
 */

#ifndef ROOMMAP_H
#define ROOMMAP_H
#include"protocol.h"
#include"DBConnect.h"
#include"Room.h"
#include<cstdio>
#include<iostream>
#include <map>
using namespace std;
class RoomMap {
public:
    RoomMap();
    RoomMap(const RoomMap& orig);
    virtual ~RoomMap();
    static RoomMap * getInstance();
     std::map<int,Room*> getRooms();
    void delRoom(int room_no, Room room_obj);
    void addRoom(int room_no, Room *room_obj);
     
    int getRoomSize();
     
private:
    static bool RoomMapFlag;
    std::map<int, Room*> rooms;
    static RoomMap * instance;

};

#endif /* ROOMMAP_H */

