#ifndef WHATKEYPRESS_H
#define WHATKEYPRESS_H

#include <iostream>
#include "enums.h"
#include "database.h"
#include "commands.h"

void keyPress(int keyCode)
{
    Commands obj;
    DataBase db;

    int id;

    switch(keyCode)
    {
        case B00: id = 0;    break;
        case B01: id = 1;    break;
        case B02: id = 2;    break;
        case B03: id = 3;    break;
        case B04: id = 4;    break;
        case B05: id = 5;    break;
        case B06: id = 6;    break;
        case B07: id = 7;    break;
        case B08: id = 8;    break;
        case B09: id = 9;    break;
        case B10: id = 10;   break;
        case B11: id = 11;   break;
        case B12: id = 12;   break;
        case B13: id = 13;   break;
        case B14: id = 14;   break;
        case B15: id = 15;   break;
        case B16: id = 16;   break;
        case B17: id = 17;   break;
        case B18: id = 18;   break;
        case B19: id = 19;   break;
    }

    obj.runCommand(obj.createCommand(db.searchCommandType(id), db.searchCommand(id).toStdString()));

}


#endif // WHATKEYPRESS_H
