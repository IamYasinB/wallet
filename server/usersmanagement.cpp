#include "usersmanagement.h"

UsersManagement::UsersManagement() {}
int UsersManagement::signin(const string& _email,const string& _password,const string& _username,int inviterID = -1)
{
    // check if email or user name exist
    for (int i = 0; i < PersonsRefInstant.size(); ++i)
    {
        if(PersonsRefInstant[i].email == _email)
        {
            return 2;
        }
        if(PersonsRefInstant[i].userName == _username)
        {
            return 3;
        }
    }

    //validating data ...
    if(!Validators::isValidEmail(_email))
    {
        return 4;
    }
    if(!Validators::isValidUsername(_username))
    {
        return 5;
    }
    if(!Validators::isValidPassword(_password,_username))
    {
        return 6;
    }
    // iserting into database
    string query = "INSERT INTO Accounts (email,password,username,level) VALUES ('" + _email + "','" + _password + "','" + _username + "','" + to_string(1) + "');";
    QString qqery = query.c_str();
    DataBase * db = DataBase::getInstance();
    if(db->insert(qqery))
    {
        if(inviterID != -1)
        {
            query = "SELECT userId FROM Accounts WHERE username = '" + _username + "';";
            qqery = query.c_str();
            db = DataBase::getInstance();
            vector<string> invitedID = db->select(qqery);
            if(invitedID.size() == 0)
                throw runtime_error("can not find new inserted person");

            query = "INSERT INTO invitation (inviter,invited) VALUES ('" + to_string(inviterID) + "','" + invitedID[0] + "');";
            qqery = query.c_str();
            db = DataBase::getInstance();
            db->insert(qqery);
            // TODO : save these changes in persons vector
            int i;
            for(i = 0;i < PersonsRefInstant.size();i++)
            {
                PersonsRefInstant[i].userId == inviterID;
            }
        }
        return 1;
    }else
    {
        return 7;
    }
    if()

}
