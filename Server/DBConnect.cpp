/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DBConnect.cpp
 * Author: admin
 * 
 * Created on 2017년 5월 27일 (토), 오후 11:41
 */

#include "DBConnect.h"

DBConnect::DBConnect() {
}

int DBConnect::makeDBConnect() {
    //DBConnect Success : 0;
    //Failed  : 1;
    mysql_init(&conn);
    
    connection=mysql_real_connect(&conn,DB_HOST,DB_USER,DB_PASS,DB_NAME,3306,(char *)NULL,0);
    
    if(connection==NULL)
    {
        fprintf(stderr,"Mysql connection error\n");
        return 1;
    }
    else return 0;
    
}

DBConnect::DBConnect(const DBConnect& orig) {
     
}

DBConnect::~DBConnect() {
}
int DBConnect::signUp(const char* id, const char* passwd, const char* nickname)
{
    //signUp failed : 1
    //signUp successed : 0
    if(makeDBConnect()!=0)
    {
        fprintf(stderr,"DB connection failed :signUp");
        return 1;
    }
    char query[256];
    memset(query,0,sizeof(256));
    
    strcat(query,"insert into userinfo VALUES(");
    strcat(query,"'");
    strcat(query,id);
    strcat(query,"','");

    strcat(query,passwd);
    strcat(query,"',");
    strcat(query,"'");
    strcat(query,nickname);
    strcat(query,"');");
    
    query_stat = mysql_query(connection,query);
    if(query_stat!=0)
    {
        fprintf(stderr,"mysql query error : %s\n", mysql_error(&conn));
        return 1;
    }
    sql_result=mysql_store_result(connection);
    mysql_close(connection);
    return 0;
    
    
}

int DBConnect::login(const char* id, const char* passwd) {

    
    //login success : 0;
    //login failed : 1;
    if(makeDBConnect()!=0)
    {
     fprintf(stderr,"DB connnection failed : login\n");
     return 1;
    }
    char _id[16];
    char _passwd[16];
    char query[256];
    char passwd_from_server[16];
    strcpy(_id,id);
    strcpy(_passwd,passwd);
    memset(query,0,sizeof(256));
    strcat(query,"select * from userinfo where (id=\"");
    strcat(query,id);
    strcat(query,"\"");
    strcat(query,");");
    puts(query);
    query_stat = mysql_query(connection,query);
    if(query_stat!=0)
    {
        fprintf(stderr,"mysql query error : %s\n", mysql_error(&conn));
        
        return 1;
    }
    sql_result=mysql_store_result(connection);
    
    while((sql_row=mysql_fetch_row(sql_result))!=NULL)
    {
        printf("%s %s %s\n",sql_row[0],sql_row[1],sql_row[2]);
        strcpy(passwd_from_server,sql_row[1]);
    
        if(strcmp(_passwd,sql_row[1])!=0)
         {
             fprintf(stderr,"passwd incorrect\n");
             return 1;
         }
        else
             return 0;   
    }
    if(sql_row==NULL)
        return 1;

    mysql_close(connection);
    return 0;
}

int DBConnect::insertLadderInfo(const char* nickname, const char* timestamp) {
    //insert successed : 0;
    //insert failed : 1;
    
    if(makeDBConnect()!=0)
    {
        fprintf(stderr,"DB connection failed : insertLadderInfo");
        return 1;
    }
    char query[256];
    memset(query,0,sizeof(256));
    
    strcat(query,"insert into ladder VALUES(");
    strcat(query,"'");
    strcat(query,nickname);
    strcat(query,"','");
    strcat(query,timestamp);
    strcat(query,"'");
    strcat(query,");");
    
    puts(query);
    query_stat = mysql_query(connection,query);
    if(query_stat!=0)
    {
        fprintf(stderr,"mysql query error : %s\n", mysql_error(&conn));
        return 1;
    }
    sql_result=mysql_store_result(connection);
    mysql_close(connection);
    return 0;
}

ladderInfo * DBConnect::searchLadderInfo(const char* nickname)
{//search successed : ladderInfo return;
    //search failed :  NULL
    ladderInfo * foundLadderInfo = (ladderInfo *)malloc(sizeof(ladderInfo *)*1);
    memset(foundLadderInfo->nickname,0,sizeof(foundLadderInfo->nickname));
    memset(foundLadderInfo->timeStamp,0,sizeof(foundLadderInfo->timeStamp));
    
    
    if(makeDBConnect()!=0)
    {
     fprintf(stderr,"DB connnection failed : searchLadderInfo\n");
     return NULL;
    }
     char query[256];
     char _nickname[25];
     strcpy(_nickname,nickname);
    
    memset(query,0,sizeof(256));
    strcat(query,"select * from ladder where (nickname=\"");
    strcat(query,nickname);
    strcat(query,"\"");
    strcat(query,");");
    puts(query);
    query_stat = mysql_query(connection,query);
    if(query_stat!=0)
    {
        fprintf(stderr,"mysql query error : %s\n", mysql_error(&conn));
        
        return NULL;
    }
    sql_result=mysql_store_result(connection);
    
    while((sql_row=mysql_fetch_row(sql_result))!=NULL)
    {
        printf("%s %s %s\n",sql_row[0],sql_row[1],sql_row[2]);
        strcpy(foundLadderInfo->nickname,sql_row[0]);
        strcpy(foundLadderInfo->timeStamp,sql_row[1]);
        
        return foundLadderInfo;
        
    }
    if(sql_row==NULL)
        return NULL;

    mysql_close(connection);
}

userInfo * DBConnect::searchUserInfo(const char* id)
{
    //search successed : userInfo return;
    //search failed :  NULL
    userInfo * foundUser = (userInfo *)malloc(sizeof(userInfo *)*1);
    memset(foundUser->id,0,sizeof(foundUser->id));
    memset(foundUser->passwd,0,sizeof(foundUser->passwd));
    memset(foundUser->nickname,0,sizeof(foundUser->nickname));
    
    
    if(makeDBConnect()!=0)
    {
     fprintf(stderr,"DB connnection failed : login\n");
     return NULL;
    }
    char _id[16];
    char _passwd[16];
    char query[256];
    char passwd_from_server[16];
    strcpy(_id,id);
    
    memset(query,0,sizeof(256));
    strcat(query,"select * from userinfo where (id=\"");
    strcat(query,id);
    strcat(query,"\"");
    strcat(query,");");
    puts(query);
    query_stat = mysql_query(connection,query);
    if(query_stat!=0)
    {
        fprintf(stderr,"mysql query error : %s\n", mysql_error(&conn));
        
        return NULL;
    }
    sql_result=mysql_store_result(connection);
    
    while((sql_row=mysql_fetch_row(sql_result))!=NULL)
    {
        printf("%s %s %s\n",sql_row[0],sql_row[1],sql_row[2]);
        strcpy(foundUser->id,sql_row[0]);
        strcpy(foundUser->passwd,sql_row[1]);
        strcpy(foundUser->nickname,sql_row[2]);
        
        return foundUser;
        
    }
    if(sql_row==NULL)
        return NULL;

    mysql_close(connection);

    
}
 
//    DBConnect DBConnect;
//    DBConnect.makeDBConnect();
    
//    if(DBConnect.login("20122472","1234")==0)
//    {
//        puts("login success");
//    }
//    else
//        puts("login failes");
    
//    userInfo *userinfo;
//    
//    if(userinfo=DBConnect.searchUserInfo("20122472")!=NULL)
//    {
//        puts(userinfo->id);
//        puts(userinfo->passwd);
//        puts(userinfo->nickname);
//    }
//    else
//    {
//        puts("search failed");
//    }
    
  /*  ladderInfo *ladder;
    ladder= DBConnect.searchLadderInfo("dordong");
    if(ladder!=NULL)
    {
        puts(ladder->nickname);
        puts(ladder->timeStamp);
    }
    else
        puts("ladder info not found");
    */
    //DBConnect.signUp("1","1","1");
    //DBConnect.insertLadderInfo("dordong","05:05");