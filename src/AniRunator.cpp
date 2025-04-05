#include "AniRunator.h"
#define _SAVE_FILE_NAME "cfg"

AniRunator::AniRunator() {
    srand(static_cast<unsigned int>(time(0)));
    kb = new KeyBoard();
    t = new TimeUtils();

    runeVK = 0;
    foodVK = 0;
    rohVK = 0;
    softVK = 0;

    lastDanceStep = "ArrowUp";
    maxMana = 0;
    regenSec = 0.66;
    danceSec = 600;
    foodSec = 264;
    runeMana = 530;
    rohSec = 450;
    softSec = 0;

    hasPromotion = false;
    hasDoubleRegen = false;
    hasRingOfHealing = false;
    hasSoftBoots = false;
    hourLeftSoftBoots = 4;
    minLeftSoftBoots = 0;

    now = t->getNowSeconds();

    danceTimeoutSeconds = 0;
    eatTimeoutSeconds = 0;
    runeTimeoutSeconds = 0;
    rohTimeoutSeconds = 0;
    softTimetoutSeconds = 0;
}

AniRunator::~AniRunator() {
    //dtor
}

void AniRunator::start() {
    if (hasPromotion) regenSec = 1;
    if (hasDoubleRegen) regenSec *= 2;
    if (hasRingOfHealing) regenSec += 4;
    if (hasSoftBoots) regenSec += 2;

    std::cout << "Regen/seg: " << regenSec << std::endl;

    softSec = (hourLeftSoftBoots * 120) + (minLeftSoftBoots * 60);

    int runeToMakeWhenManaFull = maxMana / runeMana;
    int manaToMakeRunes = runeMana * runeToMakeWhenManaFull;
    int timeToMakeRuneSec = (manaToMakeRunes / regenSec);
    int eatTimes = (foodSec / danceSec) + 1;
    int timeFoodSec = (foodSec * eatTimes);

    while (true) {
        now = t->getNowSeconds();

        if (now > danceTimeoutSeconds) {
            kb->dance(lastDanceStep);
            danceTimeoutSeconds = now + danceSec;
            std::cout << "Proxima danca em " << (danceSec / 60)<< " min (" << danceSec << "s)" << std::endl;
        }

        if (now > eatTimeoutSeconds) {
            eat(eatTimes);
            eatTimeoutSeconds = now + timeFoodSec;
            std::cout << "Proxima comida em " << (timeFoodSec / 60)<< " min (" << timeFoodSec << "s)" << std::endl;
        }

        if (now > runeTimeoutSeconds) {
            rune(runeToMakeWhenManaFull);
            runeTimeoutSeconds = now + timeToMakeRuneSec;
            std::cout << "Proxima runada em " << (timeToMakeRuneSec / 60)<< " min (" << timeToMakeRuneSec << "s)" << std::endl;
        }

        if (now > rohTimeoutSeconds) {
            kb->PressVKey(rohVK);
            rohTimeoutSeconds = now + (rohSec + 5);
            std::cout << "Botou Ring of Healing por " << (rohSec / 60)<< " min (" << rohSec << "s)" << std::endl;
        }

        if (now > softTimetoutSeconds) {
            kb->PressVKey(softVK);

            softTimetoutSeconds = now + (softSec + 5);

            if (hourLeftSoftBoots < 4) {
                hourLeftSoftBoots = 4;
                minLeftSoftBoots = 0;
                softSec = (hourLeftSoftBoots * 120) + (minLeftSoftBoots * 60);
            }
            std::cout << "Botou soft por " << (softSec / 60)<< " min (" << softSec << "s)" << std::endl;
        }

        Sleep(100);
    }
}

void AniRunator::setup() {
    foodVK = kb->setVK("Comida");
    runeVK = kb->setVK("Runa");

    configLastDance();
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

void AniRunator::configLastDance() {
    std::cout << "Qual lado parar a danca? (N, S, L, O) Padrão Norte " << std::endl;
    std::cin >> lastDanceStep;

    if (lastDanceStep == "N" || lastDanceStep == "n") {
        lastDanceStep = "ArrowUp";

    } else if (lastDanceStep == "S" || lastDanceStep == "s") {
            lastDanceStep = "ArrowDown";
    } else if (lastDanceStep == "L" || lastDanceStep == "l") {
            lastDanceStep = "ArrowRight";
    } else if (lastDanceStep == "O" || lastDanceStep == "o") {
            lastDanceStep = "ArrowLeft";
    } else {
            lastDanceStep = "ArrowUp";
    }
    system("cls");
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
    if (checkIfWantSetup("Meter o loco com Ring of Healing? (~10 rings/hora)")) {
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
