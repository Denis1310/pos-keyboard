#ifndef ENUMS_H
#define ENUMS_H

#ifdef _WIN32 || _WIN64
#include <windows.h>
#endif

enum POSButton
{
    B00 = 1023,
    B01 = 930,
    B02 = 852,
    B03 = 787,
    B04 = 731,
    B05 = 682,
    B06 = 639,
    B07 = 602,
    B08 = 568,
    B09 = 538,
    B10 = 512,
    B11 = 487,
    B12 = 465,
    B13 = 445,
    B14 = 426,
    B15 = 409,
    B16 = 393,
    B17 = 379,
    B18 = 365,
    B19 = 353
};

enum OS
{
    MacOS = 3,
    Linux = 2,
    Windows = 1,
    Other = 0
};

enum commandType
{
    openLink = 0,
    openProgram = 1,
    openFile = 2,
    openDirectory = 3,
    shortcut = 4,
    hotKey = 5,
    termCommand = 6,
    specialKey = 7
};

#endif // ENUMS_H
