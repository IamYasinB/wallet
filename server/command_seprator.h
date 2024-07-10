#ifndef COMMAND_SEPRATOR_H
#define COMMAND_SEPRATOR_H
#include <sstream>
#include <vector>

using namespace std;

class Command_seprator
{
public:
    Command_seprator();

    static vector<string> command_seperator(const string& command);
};

#endif // COMMAND_SEPRATOR_H
