#include "UserMap.h"
#include "errorcode.h"

UserMap* UserMap::instance=0;
bool UserMap::UserMapFlag=0;

UserMap* UserMap::getInstance()
{
    if(!UserMapFlag){
        instance = new UserMap();
        UserMapFlag = true;
    }
    return instance;
}
int UserMap::getSize()  // if UserMap not exists then return -1
{
    if(!UserMapFlag)
        return -1;
    
    return usermap.size();
}

void UserMap::addUser(int user_no, User user_obj){
    usermap.insert(make_pair(user_no, user_obj));
}

void UserMap::delUser(int user_no){
    map<int, User>::iterator it = usermap.find(user_no);
    if(it == usermap.end())return;
    usermap.erase(it);
}

map<int, User> UserMap::getMap()
{
    //if(!UserMapFlag)return NULL;
    return usermap;
}

void UserMap::updateUser(int user_no, User user_obj){
    auto it = usermap.begin();
    for(;it!=usermap.end();it++){
        if(it->first == user_no){
            it->second = user_obj;
        }
    }
}
int UserMap::getLastno()
{
    if(!UserMapFlag)return -1;
    for(int i=1;;i++)
    {
        if(usermap.find(i) == usermap.end())return i;
    }
}