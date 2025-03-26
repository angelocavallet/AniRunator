#include "KeyBoard.h"

static std::string danceStepList[4] = {
    "ArrowUp", "ArrowDown", "ArrowLeft", "ArrowRight"
};

static std::map<std::string, WORD> keyMap = {
    {"ArrowUp", 0x26},   {"ArrowDown", 0x28},
    {"ArrowLeft", 0x25}, {"ArrowRight", 0x27},
    {"A", 0x41}, {"B", 0x42}, {"C", 0x43}, {"D", 0x44}, {"E", 0x45},
    {"F", 0x46}, {"G", 0x47}, {"H", 0x48}, {"I", 0x49}, {"J", 0x4A},
    {"K", 0x4B}, {"L", 0x4C}, {"M", 0x4D}, {"N", 0x4E}, {"O", 0x4F},
    {"P", 0x50}, {"Q", 0x51}, {"R", 0x52}, {"S", 0x53}, {"T", 0x54},
    {"U", 0x55}, {"V", 0x56}, {"W", 0x57}, {"X", 0x58}, {"Y", 0x59}, {"Z", 0x5A},
    {"0", 0x30}, {"1", 0x31}, {"2", 0x32}, {"3", 0x33}, {"4", 0x34},
    {"5", 0x35}, {"6", 0x36}, {"7", 0x37}, {"8", 0x38}, {"9", 0x39},
    {"F1", 0x70},  {"F2", 0x71},  {"F3", 0x72},
    {"F4", 0x73},  {"F5", 0x74},  {"F6", 0x75},
    {"F7", 0x76},  {"F8", 0x77},  {"F9", 0x78},
    {"F10", 0x79}, {"F11", 0x7A}, {"F12", 0x7B},
    {"CapsLock", 0x14},
    {"NumLock", 0x90},
    {"ScrollLock", 0x91},
    {"Space", 0x20},
    {"Enter", 0x0D},
    {"Escape", 0x1B},
    {"Tab", 0x09},
    {"Shift", 0x10},
    {"Control", 0x11},
    {"Alt", 0x12},
    {"Insert", 0x2D},
    {"Home", 0x24},
    {"PageUp", 0x21},
    {"PageDown", 0x22},
    {"Delete", 0x2E},
    {"End", 0x23}
};

KeyBoard::KeyBoard()
{
}

KeyBoard::~KeyBoard()
{
    //dtor
}

WORD KeyBoard::setVK(std::string description){
    std::cout << "Configurando hotkey para " << description << std::endl;
    WORD vk = listenKeyPress();
    system("cls");
    return vk;
}

void KeyBoard::dance() {
    int danceStepLength = rand() % 8 + 3;
    std::cout << "Dancando " << danceStepLength << " passos [";

    HoldKey(0x11); //segura ctrl
    for (int i=0; i < danceStepLength; i++) {
        std::string side = danceStepList[rand() % 3];
        std::cout << side << (i < danceStepLength ? ", " : "]");
        WORD sideKey = StringToVirtualKey(side);
        PressVKey(sideKey);
    }
    ReleaseKey(0x11); //solta ctrl
    std::cout << std::endl;
}

void KeyBoard::HoldKey(WORD key) {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.wScan = 0;
    input.ki.dwFlags = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    SendInput(1, &input, sizeof(INPUT));

    int pressDelay = rand() % 127 + 60;
    Sleep(pressDelay);
}

void KeyBoard::ReleaseKey(WORD key) {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.wScan = 0;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    SendInput(1, &input, sizeof(INPUT));

    int releaseDelay = rand() % 127 + 60;
    Sleep(releaseDelay);
}

void KeyBoard::PressVKey(WORD key) {
    HoldKey(key);
    int releaseDelay = rand() % 127 + 60;
    Sleep(releaseDelay);
    ReleaseKey(key);
}

WORD KeyBoard::StringToVirtualKey(std::string key) {
    if (keyMap.find(key) != keyMap.end()){
        return keyMap[key];
    }

    std::cerr << "Tecla nao mapeada: " << key << std::endl;
    return 0;
}

std::string KeyBoard::VirtualKeyToString(WORD key) {
    static std::map<WORD, std::string> keyMapVKString = {
        {0x41, "A"}, {0x42, "B"}, {0x43, "C"}, {0x44, "D"}, {0x45, "E"},
        {0x46, "F"}, {0x47, "G"}, {0x48, "H"}, {0x49, "I"}, {0x4A, "J"},
        {0x4B, "K"}, {0x4C, "L"}, {0x4D, "M"}, {0x4E, "N"}, {0x4F, "O"},
        {0x50, "P"}, {0x51, "Q"}, {0x52, "R"}, {0x53, "S"}, {0x54, "T"},
        {0x55, "U"}, {0x56, "V"}, {0x57, "W"}, {0x58, "X"}, {0x59, "Y"},
        {0x5A, "Z"},
        {0x30, "0"}, {0x31, "1"}, {0x32, "2"}, {0x33, "3"}, {0x34, "4"},
        {0x35, "5"}, {0x36, "6"}, {0x37, "7"}, {0x38, "8"}, {0x39, "9"},
        {0x20, "Space"}, {0x0D, "Enter"}, {0x1B, "Escape"},
        {0x09, "Tab"}, {0x10, "Shift"}, {0x11, "Control"}, {0x12, "Alt"},
        {0x14, "CapsLock"}, {0x70, "F1"}, {0x71, "F2"}, {0x72, "F3"}, {0x73, "F4"},
        {0x74, "F5"}, {0x75, "F6"}, {0x76, "F7"}, {0x77, "F8"}, {0x78, "F9"},
        {0x79, "F10"}, {0x7A, "F11"}, {0x7B, "F12"},
        {0x90, "NumLock"}, {0x91, "ScrollLock"},
        {0x2D, "Insert"}, {0x24, "Home"}, {0x21, "PageUp"}, {0x2E, "Delete"},
        {0x23, "End"}, {0x22, "PageDown"},
        {0x26, "ArrowUp"}, {0x28, "ArrowDown"}, {0x25, "ArrowLeft"}, {0x27, "ArrowRight"}
    };

    if (keyMapVKString.find(key) != keyMapVKString.end()) {
        return keyMapVKString[key];
    }

    std::cerr << "Codigo virtual nao mapeado: " << key << std::endl;
    return "";
}

WORD KeyBoard::GetPressedKey() {
    for (int key = 0; key < 256; key++) {
        SHORT keyStateValue = GetAsyncKeyState(key);

        if (keyStateValue & 0x8000) {
            return static_cast<WORD>(key);
        }
    }
    return 0;
}

WORD KeyBoard::listenKeyPress() {
    WORD key = 0;

    DWORD dwMode;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hInput, &dwMode);
    SetConsoleMode(hInput, dwMode & (~ENABLE_ECHO_INPUT));

    std::cout << "Pressione Enter para iniciar gravacao" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Pressione a tecla" << std::endl;

    while (true) {
        key = GetPressedKey();

        if (key == 0x0D) { //Filtro Enter
            continue;
        }

        if (key != 0 && VirtualKeyToString(key) != "") {
            std::cout << "Tecla pressionada: " << VirtualKeyToString(key) << " (Codigo WORD: " << key << ")" << std::endl;
            while (GetAsyncKeyState(key) & 0x8000) { //Espera soltar a hotkey
                Sleep(5);
            }
            break;
        }
        Sleep(100);
    }

    std::cout << "Pressione Enter para finalizar gravacao" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    SetConsoleMode(hInput, dwMode);
    return key;
}

WORD KeyBoard::getVirtualKeyByDescription() {
    std::string key;
    std::cout << "Digite o nome da tecla (ex: 'A', 'Enter', 'Espaco'): ";
    std::getline(std::cin, key);
    WORD vkCode = StringToVirtualKey(key);
    if (vkCode != 0)
    {
        std::cout << "O código virtual da tecla '" << key << "' é: " << std::hex << vkCode << std::dec << std::endl;
    }
    return vkCode;
}

