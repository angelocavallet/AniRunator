#include "AniRunator.h"
#define _SAVE_FILE_NAME "cfg"

void AniRunator::showHeader() {
    std::cout << R"(
   _____         .____________                     __
  /  _  \   ____ |__\______   \__ __  ____ _____ _/  |_  ___________
 /  /_\  \ /    \|  ||       _/  |  \/    \\__  \\   __\/  _ \_  __ \
/    |    \   |  \  ||    |   \  |  /   |  \/ __ \|  | (  <_> )  | \/
\____|__  /___|  /__||____|_  /____/|___|  (____  /__|  \____/|__|
        \/     \/           \/           \/     \/

                        A N I H U N A T O R
    )" << std::endl;
}

AniRunator::AniRunator() {
    srand(static_cast<unsigned int>(time(0)));
    kb = new KeyBoard();
    t = new TimeUtils();

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
    int maxAfkTime = 840;
    int manaToMakeAvalanche = 530;
    int maxfoodTime = 1200;
    int brownMushroomSec = 264;
    int eatTimes = maxfoodTime / brownMushroomSec;

    config.foodSec = brownMushroomSec * eatTimes;
    config.runeMana = manaToMakeAvalanche;
    config.danceSec = maxAfkTime;

    if (config.hasPromotion) config.regenSec = 1;
    if (config.hasDoubleRegen) config.regenSec *= 2;
    if (config.hasRingOfHealing) config.regenSec += 4;
    if (config.hasSoftBoots) config.regenSec += 2;
    if (config.hasSoftBoots) config.softSec = (config.hourLeftSoftBoots * 120) + (config.minLeftSoftBoots * 60);

    int runeToMakeWhenManaFull = config.maxMana / config.runeMana;
    int manaToMakeRunes = config.runeMana * runeToMakeWhenManaFull;
    int timeToMakeRuneSec = (manaToMakeRunes / config.regenSec);

    std::cout << "AFK Time (s): " << config.danceSec << std::endl;
    std::cout << "Food Time (s): " << config.foodSec << std::endl;
    std::cout << "Rune Time (s): " << timeToMakeRuneSec << std::endl;
    std::cout << "Regen/seg: " << config.regenSec << std::endl;

    while (true) {
        now = t->getNowSeconds();

        if (now > danceTimeoutSeconds) {
            kb->dance(/*config.lastDanceStep*/);
            danceTimeoutSeconds = now + config.danceSec;
            std::cout << "Proxima danca em " << (config.danceSec / 60)<< " min (" << config.danceSec << "s)" << std::endl;
        }

        if (now > eatTimeoutSeconds) {
            eat(eatTimes);
            eatTimeoutSeconds = now + config.foodSec;
            std::cout << "Proxima comida em " << (config.foodSec / 60)<< " min (" << config.foodSec << "s)" << std::endl;
        }

        if (now > runeTimeoutSeconds) {
            rune(runeToMakeWhenManaFull);
            runeTimeoutSeconds = now + timeToMakeRuneSec;
            std::cout << "Proxima runada em " << (timeToMakeRuneSec / 60)<< " min (" << timeToMakeRuneSec << "s)" << std::endl;
        }

        if (config.hasRingOfHealing && now > rohTimeoutSeconds) {
            kb->PressVKey(config.rohVK);
            rohTimeoutSeconds = now + (config.rohSec + 5);
            std::cout << "Botou Ring of Healing por " << (config.rohSec / 60)<< " min (" << config.rohSec << "s)" << std::endl;
        }

        if (config.hasSoftBoots && now > softTimetoutSeconds) {
            kb->PressVKey(config.softVK);

            softTimetoutSeconds = now + (config.softSec + 5);

            if (config.hourLeftSoftBoots < 4) {
                config.hourLeftSoftBoots = 4;
                config.minLeftSoftBoots = 0;
                config.softSec = (config.hourLeftSoftBoots * 120) + (config.minLeftSoftBoots * 60);
            }
            std::cout << "Botou soft por " << (config.softSec / 60)<< " min (" << config.softSec << "s)" << std::endl;
        }

        Sleep(100);
    }
}

void AniRunator::setup() {
    config.foodVK = kb->setVK("Comida");
    config.runeVK = kb->setVK("Runa");

    //configLastDance();
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
        kb->PressVKey(config.foodVK);
        Sleep(rand() % 150);
    }
    std::cout << std::endl;
}

void AniRunator::rune(int runeToMake) {
    std::cout << "Runando " << runeToMake << " runas [";
    for (int i=0; i < runeToMake; i++) {
        kb->PressVKey(config.runeVK);
        std::cout << i + 1 << (i + 1 < runeToMake ? ", " : "]");
        Sleep(rand() % 150 + 2000);
    }
    std::cout << std::endl;
}

void AniRunator::configLastDance() {
    std::cout << "Qual lado parar a danca? (N, S, L, O) Padrao Norte " << std::endl;

    std::cin.ignore();
/*
    std::getline(std::cin, config.lastDanceStep);

    std::cout << "Entrada lida: '" << config.lastDanceStep << "'" << std::endl;

    if (config.lastDanceStep == "N" || config.lastDanceStep == "n") {
        config.lastDanceStep = "ArrowUp";
    } else if (config.lastDanceStep == "S" || config.lastDanceStep == "s") {
        config.lastDanceStep = "ArrowDown";
    } else if (config.lastDanceStep == "L" || config.lastDanceStep == "l") {
        config.lastDanceStep = "ArrowRight";
    } else if (config.lastDanceStep == "O" || config.lastDanceStep == "o") {
        config.lastDanceStep = "ArrowLeft";
    } else {
        config.lastDanceStep = "ArrowUp";
    }
    std::cout << "Direcao final: " << config.lastDanceStep << std::endl;
*/
    system("cls");
}

void AniRunator::configMaxMana() {
    std::cout << "Qual e o maximo de mana?" << std::endl;
    std::cin >> config.maxMana;
    std::cin.ignore();
    system("cls");
}

void AniRunator::configPromotion() {
    config.hasPromotion = checkIfWantSetup("Tem promotion?");
    system("cls");
}

void AniRunator::configDoubleRegen() {
    config.hasDoubleRegen = checkIfWantSetup("Voce ta com regeneracao dobrada?");
    system("cls");
}

void AniRunator::configRingOfHealing() {
    if (checkIfWantSetup("Meter o loco com Ring of Healing? (~10 rings/hora)")) {
        config.hasRingOfHealing = true;
        config.rohVK = kb->setVK("Ring of Healing");
    }
}

void AniRunator::configSoftBoots() {
    if (checkIfWantSetup("Ta de Soft seu safado?")) {
        config.hasSoftBoots = true;
        config.softVK = kb->setVK("Soft Boots");

        if(!checkIfWantSetup("A soft ta novinha?")) {
            std::cout << "Seu pobre. Quantas horas inteiras ainda tem?" << std::endl;
            std::cin >> config.hourLeftSoftBoots;
            std::cin.ignore();

            std::cout << "Ta e os minutos?" << std::endl;
            std::cin >> config.minLeftSoftBoots;
            std::cin.ignore();
            system("cls");
        }
    }
}

bool AniRunator::checkIfWantSetup(std::string description) {
    char option;
    std::cout << description << " (s/n): ";
    std::cin >> option;
    std::cin.ignore();

    if (std::tolower(option) == 's') return true;
    return false;
}

void AniRunator::save() {
    std::ofstream file(_SAVE_FILE_NAME, std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir configuracao " << _SAVE_FILE_NAME << " para escrita!" << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&config), sizeof(AniRunatorConfig));
    file.close();

    if (!file) {
        std::cerr << "Erro ao salvar os dados!" << std::endl;
    } else {
        std::cout << "Configuracao salva com sucesso." << std::endl;
    }
}

bool AniRunator::load() {
    std::ifstream file(_SAVE_FILE_NAME, std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir configuracao " << _SAVE_FILE_NAME << " para leitura!" << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&config), sizeof(AniRunatorConfig));
    file.close();

    if (!file || file.gcount() != sizeof(AniRunatorConfig)) {
        std::cerr << "Erro ao ler os dados do arquivo ou estrutura incompativel." << std::endl;
        return false;
    }

    std::cout << "Configuracao carregada com sucesso." << std::endl;
    return true;
}
