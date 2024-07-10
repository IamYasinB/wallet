#include "usersmanagement.h"

vector<PersonNode> UsersManagement::PersonsRefInstant;

UsersManagement::UsersManagement() {}
int UsersManagement::signup(const string& _email,const string& _password,const string& _username,int inviterID = -1)
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
        query = "SELECT userId FROM Accounts WHERE username = '" + _username + "';";
        qqery = query.c_str();
        db = DataBase::getInstance();
        vector<string> invitedID = db->select(qqery);
        if(invitedID.size() == 0)
            throw runtime_error("can not find new inserted person");

        if(inviterID != -1)
        {
            query = "INSERT INTO invitation (inviter,invited) VALUES ('" + to_string(inviterID) + "','" + invitedID[0] + "');";
            qqery = query.c_str();
            db = DataBase::getInstance();
            db->insert(qqery);

            // check for level up!!
            query = "SELECT invited FROM invitation WHERE inviter='" + to_string(inviterID) + "';";
            qqery = query.c_str();
            vector<string> allInviteds = db->select(qqery);
            if(allInviteds.size() > 4)
            {
                int i;
                for(i = 0;i < PersonsRefInstant.size();i++)
                {
                    if(PersonsRefInstant[i].userId == inviterID && PersonsRefInstant[i].level != 2)
                    {
                        PersonsRefInstant[i].level = 2;
                        query = "UPDATE Accounts SET level = '2' WHERE userID='" + to_string(PersonsRefInstant[i].userId) + "';";
                        qqery = query.c_str();
                        db->update(qqery);
                        break;
                    }
                }
            }
        }
        // TODO : save these changes in persons vector
        PersonNode p1;
        p1.userId = stoi(invitedID[0]);
        p1.userName = _username;
        p1.email = _email;
        p1.password = _password;
        p1.level = 1;
        PersonsRefInstant.push_back(p1);
        return 1;
    }else
    {
        return 7;
    }

}
