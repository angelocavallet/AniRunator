#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <windows.h>
#include <iostream>
#include <limits>
#include <map>

class KeyBoard
{
    public:
        KeyBoard();
        virtual ~KeyBoard();

        void dance();

        WORD setVK(std::string description);

        void HoldKey(WORD key);
        void ReleaseKey(WORD key);
        void PressVKey(WORD key);

        WORD GetPressedKey();
        WORD listenKeyPress();
        WORD getVirtualKeyByDescription();

        std::string VirtualKeyToString(WORD key);
        WORD StringToVirtualKey(std::string key);
};
#endif
