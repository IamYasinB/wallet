#ifndef USERSMANAGEMENT_H
#define USERSMANAGEMENT_H

#include <vector>
#include <string>
#include <mutex>
#include "validators.h"
#include "database.h"

using namespace std;

class PersonNode;

class UsersManagement
{
private:

    static vector<PersonNode> PersonsRefInstant;
    static mutex usrmutex;
    UsersManagement();
public:
    // TODO : creat a loader to load all users from database

    static vector<PersonNode> getAllPersons()
    {
        return PersonsRefInstant;
    }

    static int signup(const string& _email,const string& _password,const string& _username,int inviterID);
    /*
     * if successful return 1
     * if email exist return 2
     * if user name exist return 3
     * if email is not valid return 4
     * if user name is not valid return 5
     * if password is not valid return 6
     * if failed insert into datatbase return 7
    */


    // static bool login(string emailOrUsername,string password);
    // static int change_password(string emailOrUsername,string password);
    // static int reset_password(string userame,string email,string newPasswprd);
};


class PersonNode
{
public:
    // esential data
    int userId;
    string email;
    string password;
    string userName;

    // supplementary data
    int inviterID;
    int level;
    string name;
    string phone;
    string address;
};

#endif //USERSMANAGEMENT_H
