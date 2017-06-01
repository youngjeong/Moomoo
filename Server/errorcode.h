/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   errorcode.h
 * Author: eldkq
 *
 * Created on 2017년 5월 30일 (화), 오후 3:55
 */

#ifndef ERRORCODE_H
#define ERRORCODE_H

enum ErrorCode{
    SUCCESS = 0x00000000,
    INTERNAL_SERVER_ERROR,
    ID_ALREADY_EXISTS,
    INCORRECT_PASSWORD,
    CANNOT_FOUND_USER_KEY_FROM_DB
};


#endif /* ERRORCODE_H */

