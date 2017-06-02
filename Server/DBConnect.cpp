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
#include "errorcode.h"

DBConnect::DBConnect() {
}



int DBConnect::makeDBConnect() {
    //DBConnect Success : 0;
    //Failed  : 1;
    mysql_init(&conn);

    connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *) NULL, 0);

    if (connection == NULL) {
        fprintf(stderr, "Mysql connection error\n");
        return 1;
    } else return 0;

}

DBConnect::DBConnect(const DBConnect& orig) {

}



DBConnect::~DBConnect() {
}

int DBConnect::getUserKeyWithId(const char* id) {

    char query[256];
    char _char_user_key[10];
    memset(query,0,sizeof(query));
    
    
     if (makeDBConnect() != 0) {
        fprintf(stderr, "DB connection failed :signUp");
        return INTERNAL_SERVER_ERROR;
    }
    strcat(query,"select * from userinfo where (id='");
    strcat(query,id);
    strcat(query,"');");
    
    query_stat = mysql_query(connection, query);
    if (query_stat != 0) {
        fprintf(stderr, "mysql query error : %s\n", mysql_error(&conn));
        return INTERNAL_SERVER_ERROR;
    }

    sql_result = mysql_store_result(connection);

    while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
        strcpy(_char_user_key,sql_row[0]);
         mysql_close(connection);
        return atoi(_char_user_key);
    }
    if(sql_row==NULL){
         mysql_close(connection);
        return CANNOT_FOUND_USER_KEY_FROM_DB;//cannot found user_key
    }
}


int DBConnect::signUp(const char* id, const char* passwd, const char* nickname) {
    //signUp failed : 1
    //signUp successed : 0
    if (makeDBConnect() != 0) {
        fprintf(stderr, "DB connection failed :signUp");
        return INTERNAL_SERVER_ERROR;
    }
    char query[256];
    memset(query, 0, sizeof (256));

    strcat(query, "select * from userinfo where (id=\"");
    strcat(query, id);
    strcat(query, "\"");
    strcat(query, ");");


    query_stat = mysql_query(connection, query);
    if (query_stat != 0) {
        fprintf(stderr, "mysql query error : %s\n", mysql_error(&conn));
        return INTERNAL_SERVER_ERROR;
    }

    sql_result = mysql_store_result(connection);

    while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
        fprintf(stderr, "already exist user : %s\n", sql_row[0]);
        return ID_ALREADY_EXISTS;
    }
    if (sql_row == NULL) {
        memset(query, 0, sizeof (query));

        strcat(query, "insert into userinfo(id,passwd,nickname)VALUES(");
        strcat(query, "'");
        strcat(query, id);
        strcat(query, "','");

        strcat(query, passwd);
        strcat(query, "',");
        strcat(query, "'");
        strcat(query, nickname);
        strcat(query, "');");
        

        
        query_stat = mysql_query(connection, query);
        if (query_stat != 0) {
            fprintf(stderr, "mysql query error : %s\n", mysql_error(&conn));
            return INTERNAL_SERVER_ERROR;
        }
        sql_result = mysql_store_result(connection);
        mysql_close(connection);
        return SUCCESS;
    }

}

int DBConnect::login(const char* id, const char* passwd) {
    //return value : person_key;

    //login success : integer bigger than 1;
    //login failed : 1 -> -1;
    if (makeDBConnect() != 0) {
        fprintf(stderr, "DB connnection failed : login\n");
        return INTERNAL_SERVER_ERROR;
    }
    char _id[16];
    char _passwd[16];
    char query[256];
    char passwd_from_server[16];
    strcpy(_id, id);
    strcpy(_passwd, passwd);
    memset(query, 0, sizeof (256));
    strcat(query, "select * from userinfo where (id=\"");
    strcat(query, id);
    strcat(query, "\"");
    strcat(query, ");");
    puts(query);
    query_stat = mysql_query(connection, query);
    if (query_stat != 0) {
        fprintf(stderr, "mysql query error : %s\n", mysql_error(&conn));

        return INTERNAL_SERVER_ERROR;
    }
    sql_result = mysql_store_result(connection);

    while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
        printf("%s %s %s\n", sql_row[1], sql_row[2], sql_row[3]);
        printf("user_key : %s\n",sql_row[0]);
        //0 : user_key    1 : id     2: passwd     3 : nickname
        strcpy(passwd_from_server, sql_row[2]);

        if (strcmp(_passwd, sql_row[2]) != 0) {
            fprintf(stderr, "passwd incorrect\n");
            return INCORRECT_PASSWORD;
        } else
            return SUCCESS;
    }
    if (sql_row == NULL)
        return INTERNAL_SERVER_ERROR;

    mysql_close(connection);
    return SUCCESS;
}




int DBConnect::insertLadderInfo(const char* nickname, const char* timestamp) {
    //insert successed : 0;
    //insert failed : 1;

    if (makeDBConnect() != 0) {
        fprintf(stderr, "DB connection failed : insertLadderInfo");
        return 1;
    }
    char query[256];
    memset(query, 0, sizeof (256));

    strcat(query, "insert into ladder VALUES(");
    strcat(query, "'");
    strcat(query, nickname);
    strcat(query, "','");
    strcat(query, timestamp);
    strcat(query, "'");
    strcat(query, ");");

    puts(query);
    query_stat = mysql_query(connection, query);
    if (query_stat != 0) {
        fprintf(stderr, "mysql query error : %s\n", mysql_error(&conn));
        return 1;
    }
    sql_result = mysql_store_result(connection);
    mysql_close(connection);
    return 0;
}

ladderInfo * DBConnect::searchLadderInfo(const char* nickname) {//search successed : ladderInfo return;
    //search failed :  NULL
    ladderInfo * foundLadderInfo = (ladderInfo *) malloc(sizeof (ladderInfo *)*1);
    memset(foundLadderInfo->nickname, 0, sizeof (foundLadderInfo->nickname));
    memset(foundLadderInfo->timeStamp, 0, sizeof (foundLadderInfo->timeStamp));


    if (makeDBConnect() != 0) {
        fprintf(stderr, "DB connnection failed : searchLadderInfo\n");
        return NULL;
    }
    char query[256];
    char _nickname[25];
    strcpy(_nickname, nickname);

    memset(query, 0, sizeof (256));
    strcat(query, "select * from ladder where (nickname=\"");
    strcat(query, nickname);
    strcat(query, "\"");
    strcat(query, ");");
    puts(query);
    query_stat = mysql_query(connection, query);
    if (query_stat != 0) {
        fprintf(stderr, "mysql query error : %s\n", mysql_error(&conn));

        return NULL;
    }
    sql_result = mysql_store_result(connection);

    while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
        printf("%s %s %s\n", sql_row[0], sql_row[1], sql_row[2]);
        strcpy(foundLadderInfo->nickname, sql_row[0]);
        strcpy(foundLadderInfo->timeStamp, sql_row[1]);

        return foundLadderInfo;

    }
    if (sql_row == NULL)
        return NULL;

    mysql_close(connection);
}

int DBConnect::searchUserInfo(const char* id , userInfo *result) {
    //search successed : userInfo return;
    //search failed :  NULL

    /*userInfo * foundUser = (userInfo *) malloc(sizeof (userInfo )*1);
    memset(foundUser->id, 0, sizeof (foundUser->id));
    memset(foundUser->passwd, 0, sizeof (foundUser->passwd));
    memset(foundUser->nickname, 0, sizeof (foundUser->nickname));*/


    if (makeDBConnect() != 0) {
        fprintf(stderr, "DB connnection failed : login\n");
        mysql_close(connection);
        return INTERNAL_SERVER_ERROR;
    }
    char _id[16];
    char _passwd[16];
    char query[256];
    char passwd_from_server[16];
    strcpy(_id, id);

    memset(query, 0, sizeof (256));
    strcat(query, "select * from userinfo where (id=\"");
    strcat(query, id);
    strcat(query, "\"");
    strcat(query, ");");
    puts(query);
    query_stat = mysql_query(connection, query);
    if (query_stat != 0) {
        fprintf(stderr, "mysql query error : %s\n", mysql_error(&conn));
        mysql_close(connection);
        return INTERNAL_SERVER_ERROR;
    }
    sql_result = mysql_store_result(connection);

    while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
        printf("%s %s %s %s\n", sql_row[0], sql_row[1], sql_row[2],sql_row[3]);
       
        strcpy(result->id, sql_row[1]);
        strcpy(result->passwd, sql_row[2]);
        strcpy(result->nickname, sql_row[3]);
        mysql_close(connection);
        return SUCCESS;

    }
    if (sql_row == NULL)
    {
        mysql_close(connection);
        return INTERNAL_SERVER_ERROR;
    }
    


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
