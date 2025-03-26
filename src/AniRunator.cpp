#include "AniRunator.h"
#define _SAVE_FILE_NAME "cfg"

AniRunator::AniRunator() {
    srand(static_cast<unsigned int>(time(0)));
    kb = new KeyBoard();

    runeVK = 0;
    foodVK = 0;
    rohVK = 0;
    softVK = 0;

    maxMana = 0;
    regenSec = 0.66;

    hasPromotion = false;
    hasDoubleRegen = false;
    hasRingOfHealing = false;
    hasSoftBoots = false;
    hourLeftSoftBoots = 4;
    minLeftSoftBoots = 0;
}

AniRunator::~AniRunator() {
    //dtor
}

void AniRunator::start() {
    int afkSec = 600;
    int foodSec = 264;
    int runeMana = 530;

    if (hasPromotion) regenSec = 1;
    if (hasDoubleRegen) regenSec *= 2;

    int runeToMakeWhenManaFull = maxMana / runeMana;
    int manaToMakeRunes = runeMana * runeToMakeWhenManaFull;
    int waitFillManaMiliSec = (manaToMakeRunes / regenSec) * 1000;
    int danceBetweenRune = waitFillManaMiliSec / (afkSec * 1000);
    int eatBetweenPauses = ceil(afkSec / foodSec);
    int sleepPause = waitFillManaMiliSec / danceBetweenRune;

    while (true) {
        std::cout << danceBetweenRune << " Pausas para comer e dancar " << std::endl;
        for(int i=0; i < danceBetweenRune; i++) {
            eat(eatBetweenPauses);
            kb->dance();

            std::cout << "Dormindo por " << ((sleepPause / 1000) / 60)<< "min" << std::endl;
            Sleep(sleepPause);
        }
        rune(runeToMakeWhenManaFull);
    }
}

void AniRunator::setup() {
    foodVK = kb->setVK("Comida");
    runeVK = kb->setVK("Runa");

    configMaxMana();
    configPromotion();
    configDoubleRegen();
    configRingOfHealing();
    configSoftBoots();

    save();
}

void AniRunator::eat(int foodToEat) {
    std::cout << "Comendo " << foodToEat << " comidas [";
    for (int i=0; i < foodToEat; i++) {
        std::cout << "munch" << (i + 1 < foodToEat ? ", " : "]");
        kb->PressVKey(foodVK);
        Sleep(rand() % 150);
    }
    std::cout << std::endl;
}

void AniRunator::rune(int runeToMake) {
    std::cout << "Runando " << runeToMake << " runas [";
    for (int i=0; i < runeToMake; i++) {
        kb->PressVKey(runeVK);
        std::cout << i + 1 << (i + 1 < runeToMake ? ", " : "]");
        Sleep(rand() % 150 + 2000);
    }
    std::cout << std::endl;
}

void AniRunator::configMaxMana() {
    std::cout << "Qual e o maximo de mana?" << std::endl;
    std::cin >> maxMana;
    system("cls");
}

void AniRunator::configPromotion() {
    hasPromotion = checkIfWantSetup("Tem promotion?");
    system("cls");
}

void AniRunator::configDoubleRegen() {
    hasDoubleRegen = checkIfWantSetup("Voce ta com regeneracao dobrada?");
    system("cls");
}

void AniRunator::configRingOfHealing() {
    if (checkIfWantSetup("Meter o loco com Ring of Healing? (~15 rings/hora)")) {
        hasRingOfHealing = true;
        rohVK = kb->setVK("Ring of Healing");
    }
}

void AniRunator::configSoftBoots() {
    if (checkIfWantSetup("Ta de Soft seu safado?")) {
        hasSoftBoots = true;
        softVK = kb->setVK("Soft Boots");

        if(!checkIfWantSetup("A soft ta novinha?")) {
            std::cout << "Seu pobre. Quantas horas inteiras ainda tem?" << std::endl;
            std::cin >> hourLeftSoftBoots;

            std::cout << "Ta e os minutos?" << std::endl;
            std::cin >> minLeftSoftBoots;
            system("cls");
        }
    }
}

bool AniRunator::checkIfWantSetup(std::string description) {
    char option;
    std::cout << description << " (s/n): ";
    std::cin >> option;

    if (std::tolower(option) == 's') return true;
    return false;
}

void AniRunator::save() {
    std::ofstream file(_SAVE_FILE_NAME, std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo para escrita!" << std::endl;
        return;
    }
    file.write(reinterpret_cast<const char*>(this), sizeof(AniRunator));
    file.close();
}

bool AniRunator::load() {
    std::ifstream file(_SAVE_FILE_NAME, std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo para leitura!" << std::endl;
        return false;
    }
    file.read(reinterpret_cast<char*>(this), sizeof(AniRunator));
    file.close();
}
