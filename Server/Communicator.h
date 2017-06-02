/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Comunicator.h
 * Author: skriex
 *
 * Created on 2017년 5월 28일 (일), 오후 7:53
 */

#ifndef COMUNICATOR_H
#define COMUNICATOR_H
#include <vector>

class Communicator
{
public:
    static int parse(int sock);
    
private:
    Communicator(){}
    static void readBody(int sock, char* body_buf, int size);
    
    
};

#endif /* COMUNICATOR_H */

