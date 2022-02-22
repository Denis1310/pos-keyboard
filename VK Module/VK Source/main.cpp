#include <iostream>
#include <windows.h>
#include "VKe.h"

int toVKCode(std::string key)
{
         if (key == "Backspace")     return VK_BACK;
    else if (key == "Tab")           return VK_TAB;
    else if (key == "Clear")         return VK_CLEAR;
    else if (key == "Enter")         return VK_RETURN;
    else if (key == "Shift")         return VK_SHIFT;
    else if (key == "Shift_L")       return VK_LSHIFT;
    else if (key == "Shift_R")       return VK_RSHIFT;
    else if (key == "Control")       return VK_CONTROL;
    else if (key == "Control_L")     return VK_LCONTROL;
    else if (key == "Control_R")     return VK_RCONTROL;
    else if (key == "Alt")           return VK_MENU;
    else if (key == "Alt_L")         return VK_LMENU;
    else if (key == "Alt_R")         return VK_RMENU;
    else if (key == "Pause")         return VK_PAUSE;
    else if (key == "Capslock")      return VK_CAPITAL;
    else if (key == "Escape")        return VK_ESCAPE;
    else if (key == "Space")         return VK_SPACE;
    else if (key == "PgUp")          return VK_PRIOR;
    else if (key == "PgDown")        return VK_NEXT;
    else if (key == "End")           return VK_END;
    else if (key == "Home")          return VK_HOME;
    else if (key == "LeftArrow")     return VK_LEFT;
    else if (key == "UpArrow")       return VK_UP;
    else if (key == "RightArrow")    return VK_RIGHT;
    else if (key == "DownArrow")     return VK_DOWN;
    else if (key == "Select")        return VK_SELECT;
    else if (key == "Print")         return VK_PRINT;
    else if (key == "Execute")       return VK_EXECUTE;
    else if (key == "PrntScr")       return VK_SNAPSHOT;
    else if (key == "Insert")        return VK_INSERT;
    else if (key == "Delete")        return VK_DELETE;
    else if (key == "Help")          return VK_HELP;
    else if (key == "Win_L")         return VK_LWIN;
    else if (key == "Win_R")         return VK_RWIN;
    else if (key == "Multiply")      return VK_MULTIPLY;
    else if (key == "Add")           return VK_ADD;
    else if (key == "Separator")     return VK_SEPARATOR;
    else if (key == "Subtract")      return VK_SUBTRACT;
    else if (key == "Decimal")       return VK_DECIMAL;
    else if (key == "Divide")        return VK_DIVIDE;
    else if (key == "0")             return VK_0;
    else if (key == "1")             return VK_1;
    else if (key == "2")             return VK_2;
    else if (key == "3")             return VK_3;
    else if (key == "4")             return VK_4;
    else if (key == "5")             return VK_5;
    else if (key == "6")             return VK_6;
    else if (key == "7")             return VK_7;
    else if (key == "8")             return VK_8;
    else if (key == "9")             return VK_9;
    else if (key == "Num0")          return VK_NUMPAD0;
    else if (key == "Num1")          return VK_NUMPAD1;
    else if (key == "Num2")          return VK_NUMPAD2;
    else if (key == "Num3")          return VK_NUMPAD3;
    else if (key == "Num4")          return VK_NUMPAD4;
    else if (key == "Num5")          return VK_NUMPAD5;
    else if (key == "Num6")          return VK_NUMPAD6;
    else if (key == "Num7")          return VK_NUMPAD7;
    else if (key == "Num8")          return VK_NUMPAD8;
    else if (key == "Num9")          return VK_NUMPAD9;
    else if (key == "NumLock")       return VK_NUMLOCK;
    else if (key == "ScrollLock")    return VK_SCROLL;
    else if (key == "F1")            return VK_F1;
    else if (key == "F2")            return VK_F2;
    else if (key == "F3")            return VK_F3;
    else if (key == "F4")            return VK_F4;
    else if (key == "F5")            return VK_F5;
    else if (key == "F6")            return VK_F6;
    else if (key == "F7")            return VK_F7;
    else if (key == "F8")            return VK_F8;
    else if (key == "F9")            return VK_F9;
    else if (key == "F10")           return VK_F10;
    else if (key == "F11")           return VK_F11;
    else if (key == "F12")           return VK_F12;
    else if (key == "F13")           return VK_F13;
    else if (key == "F14")           return VK_F14;
    else if (key == "F15")           return VK_F15;
    else if (key == "F16")           return VK_F16;
    else if (key == "F17")           return VK_F17;
    else if (key == "F18")           return VK_F18;
    else if (key == "F19")           return VK_F19;
    else if (key == "F20")           return VK_F20;
    else if (key == "F21")           return VK_F21;
    else if (key == "F22")           return VK_F22;
    else if (key == "F23")           return VK_F23;
    else if (key == "F24")           return VK_F24;
    else if (key == "A")             return VK_A;
    else if (key == "B")             return VK_B;
    else if (key == "C")             return VK_C;
    else if (key == "D")             return VK_D;
    else if (key == "E")             return VK_E;
    else if (key == "F")             return VK_F;
    else if (key == "G")             return VK_G;
    else if (key == "H")             return VK_H;
    else if (key == "I")             return VK_I;
    else if (key == "J")             return VK_J;
    else if (key == "K")             return VK_K;
    else if (key == "L")             return VK_L;
    else if (key == "M")             return VK_M;
    else if (key == "N")             return VK_N;
    else if (key == "O")             return VK_O;
    else if (key == "P")             return VK_P;
    else if (key == "Q")             return VK_Q;
    else if (key == "R")             return VK_R;
    else if (key == "S")             return VK_S;
    else if (key == "T")             return VK_T;
    else if (key == "U")             return VK_U;
    else if (key == "V")             return VK_V;
    else if (key == "W")             return VK_W;
    else if (key == "X")             return VK_X;
    else if (key == "Y")             return VK_Y;
    else if (key == "Z")             return VK_Z;

    else if (key == "Mute")          return VK_VOLUME_MUTE;
    else if (key == "Down")          return VK_VOLUME_DOWN;
    else if (key == "Up")            return VK_VOLUME_UP;
    else if (key == "NextTrack")     return VK_MEDIA_NEXT_TRACK;
    else if (key == "PreviousTrack") return VK_MEDIA_PREV_TRACK;
    else if (key == "Stop")          return VK_MEDIA_STOP;
    else if (key == "PlayPause")     return VK_MEDIA_PLAY_PAUSE;
    else if (key == "Play")          return VK_PLAY;
    else if (key == "Zoom")          return VK_ZOOM;
    else if (key == "Clear")         return VK_OEM_CLEAR;
    else
    {
        std::cerr << "Error: Non-existent key - " << key << std::endl;
        return 0;
    }
}

bool codeEvent(std::string action, int *codes)
{
    if (action == "key")
    {
        for (short i{}; i < 4; ++i)
        {
            if(codes[i])
            {
                keybd_event(codes[i], 0, 0, 0);
            }
        }
    }
    else if (action == "keyup")
    {
        for (short i{}; i < 4; ++i)
        {
            if(codes[i])
            {
                keybd_event(codes[i], 0, 1, 0);
            }
        }
    }
    else
    {
        if (action != "key" || action != "keyup")
        {
            std::cerr << "Error: Not a valid parameter - " << action << std::endl;
        }

        return 0;
    }
}

int main(int argc, char **argv)
{
    short keyI{}, keyJ{};
    char keys[4][12] {};
    int  keysCode[4] {};
    std::string action(argv[1]);

    for (short i{}; argv[2][i] != '\0'; ++i)
    {
        if (argv[2][i] == '+')
        {
            ++keyI;
            keyJ = 0;
            continue;
        }
        else
        {
            keys[keyI][keyJ] = argv[2][i];
            ++keyJ;
        }
    }

    for (short i{}; i < 4; ++i)
    {
        if (keys[i] != "")
        {
            keysCode[i] = toVKCode(keys[i]);
        }
    }

    codeEvent(action, keysCode);

    system("pause");
    return 0;
}
