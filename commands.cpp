#include "commands.h"

string Commands::createCommand(int type, string path)
{
    string command;

    if (type == commandType::termCommand)
    {
        return path;
    }
    else
    {
        switch (type)
        {
        #ifdef _WIN32 || _WIN64
            case commandType::openLink:
            case commandType::openProgram:
            case commandType::openFile:
            case commandType::openDirectory:
                command = "start";
                break;

            case commandType::shortcut:
            case commandType::specialKey:
                command = "VK key";
                break;
        #elif __linux__
            case commandType::openLink:
            case commandType::openFile:
            case commandType::openDirectory:
                command = "open";
                break;

            case commandType::openProgram:
                command = "./";
                break;

            case commandType::shortcut:
                command = "xdotool key";
                break;
        #endif
        }

        command += " " + path;

        return command;
    }
}

bool Commands::runCommand(string command)
{
    char do_command[command.length() + 1];
    strcpy(do_command, command.c_str());

    #ifdef _WIN32 || _WIN64
        if (command.find("VK key") != -1)
    #elif __linux__
        if ((int)command.find("xdotool key") != -1)
    #endif
    {
        system(do_command);

        #ifdef _WIN32 || _WIN64
            command.replace(3, 3, "keyup");
        #elif __linux__
            command.replace(8, 3, "keyup");
        #endif
    }

    return !system(do_command);
}
