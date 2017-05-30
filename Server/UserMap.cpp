#include "UserMap.h"
#include "errorcode.h"

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
    usermap.insert({user_no, user_obj});
}

void UserMap::delUser(int user_no){
    auto it = usermap.find(user_no);
    usermap.erase(it);
}

map<int, User> UserMap::getMap()
{
    if(!UserMapFlag)return NULL;
    return usermap;
}