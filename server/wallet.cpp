#include "wallet.h"

Wallet::Wallet() {}

int Wallet::withdraw(string coin_name,double amount) // -
{
    if(coin_name == "BTC")
    {
        if((this->BTC_balance - amount) < 0)
            return 3;
        this->BTC_balance -= amount;
        string query = "UPDATE wallet_balance SET BTC=" + to_string(this->BTC_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->BTC_balance += amount;
            return 4;
        }
    }
    else if(coin_name == "ETH")
    {
        if((this->ETH_balance - amount) < 0)
            return 3;
        this->ETH_balance -= amount;
        string query = "UPDATE wallet_balance SET ETH=" + to_string(this->ETH_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->ETH_balance += amount;
            return 4;
        }
    }
    else if(coin_name == "USDT")
    {
        if((this->USDT_balance - amount) < 0)
            return 3;
        this->USDT_balance -= amount;
        string query = "UPDATE wallet_balance SET USDT=" + to_string(this->USDT_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->USDT_balance += amount;
            return 4;
        }
    }
    else if(coin_name == "BNB")
    {
        if((this->BNB_balance - amount) < 0)
            return 3;
        this->BNB_balance -= amount;
        string query = "UPDATE wallet_balance SET BNB=" + to_string(this->BNB_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->BNB_balance += amount;
            return 4;
        }
    }
    else if(coin_name == "SOL")
    {
        if((this->SOL_balance - amount) < 0)
            return 3;
        this->SOL_balance -= amount;
        string query = "UPDATE wallet_balance SET SOL=" + to_string(this->SOL_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->SOL_balance += amount;
            return 4;
        }
    }
    else if(coin_name == "USD")
    {
        if((this->USD_balance - amount) < 0)
            return 3;
        this->USD_balance -= amount;
        string query = "UPDATE wallet_balance SET USD=" + to_string(this->USD_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->USD_balance += amount;
            return 4;
        }
    }else
    {
        return 2;
    }
}

int Wallet::deposit(string coin_name,double amount) // +
{
    if(coin_name == "BTC")
    {
        this->BTC_balance += amount;
        string query = "UPDATE wallet_balance SET BTC=" + to_string(this->BTC_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->BTC_balance -= amount;
            return 4;
        }
    }
    else if(coin_name == "ETH")
    {
        this->ETH_balance += amount;
        string query = "UPDATE wallet_balance SET ETH=" + to_string(this->ETH_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->ETH_balance -= amount;
            return 4;
        }
    }
    else if(coin_name == "USDT")
    {
        this->USDT_balance += amount;
        string query = "UPDATE wallet_balance SET USDT=" + to_string(this->USDT_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->USDT_balance -= amount;
            return 4;
        }
    }
    else if(coin_name == "BNB")
    {
        this->BNB_balance += amount;
        string query = "UPDATE wallet_balance SET BNB=" + to_string(this->BNB_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->BNB_balance -= amount;
            return 4;
        }
    }
    else if(coin_name == "SOL")
    {
        this->SOL_balance += amount;
        string query = "UPDATE wallet_balance SET SOL=" + to_string(this->SOL_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->SOL_balance -= amount;
            return 4;
        }
    }
    else if(coin_name == "USD")
    {
        this->USD_balance += amount;
        string query = "UPDATE wallet_balance SET USD=" + to_string(this->USD_balance) + " WHERE walletIP=" + to_string(this->walletIP) + ";";
        QString qquery = query.c_str();
        DataBase* db = DataBase::getInstance();
        if(db->update(qquery))
        {
            return 1;
        }else
        {
            this->USD_balance -= amount;
            return 4;
        }
    }else
    {
        return 2;
    }
}
