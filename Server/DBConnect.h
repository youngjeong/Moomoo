/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DBConnect.h
 * Author: admin
 *
 * Created on 2017년 5월 27일 (토), 오후 11:41
 */

#ifndef DBCONNECT_H
#define DBCONNECT_H

using namespace std;

#include<iostream>
#include<cstring>
#include <mysql/mysql.h>
#include <cstdio>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "moomoo"
#define DB_NAME "moomooDB"
#define USER_DB "userinfo"
#define LADDER_DB "ladder"
typedef struct userInfo
{
    char id[16];
    char passwd[16];
    char nickname[16];
}userinfo;
typedef struct ladderInfo
{
    char nickname[16];
    char timeStamp[16];
}ladderInfo;
class DBConnect {
public:
    DBConnect();
    DBConnect(const DBConnect& orig);
    virtual ~DBConnect();
    
    int makeDBConnect();
    int getUserKeyWithId(const char *id);
    int signUp(const char *id, const char *passwd, const char *nickname);
    int searchUserInfo(const char* id, userInfo*);
    int insertLadderInfo(const char *nickname,const char *timestamp);
    ladderInfo * searchLadderInfo(const char *nickname);
    int login(const char *id, const char *passwd);
    
    
    MYSQL *connection=NULL,conn;
    MYSQL_RES *sql_result;
    MYSQL_ROW sql_row;
    int query_stat;
    
  
private:

};

#endif /* DBCONNECT_H */

