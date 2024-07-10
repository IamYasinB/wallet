#include "command_seprator.h"

Command_seprator::Command_seprator() {}

vector<string> Command_seprator::command_seperator(const string& command){
    vector<string> words;
    istringstream iss(command);
    string word;
    while(iss>>word){
        words.push_back(word);
    }
    return words;
}
