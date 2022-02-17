#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <string.h>
#include "enums.h"

using std::string;

class Commands
{
public:
    string createCommand(int, string);
    bool runCommand(string);
};

#endif // COMMANDS_H
