#include "wallet.h"
#include <cstdlib>
#include <time.h>
#include <string>
std :: string wallet :: GetIP(){

    return IP;

}
std :: string wallet :: Generate_IP(){

    bool Confirmed_IP = false;

    std :: string half_IP;

    while(!Confirmed_IP){

        srand(time(0));

        half_IP = std::to_string(rand()%9000 + 1000);

        /*check in data bese if this ip does exist*/
        //TODO
        Confirmed_IP = true;
    }
    return "215"+half_IP;
}
