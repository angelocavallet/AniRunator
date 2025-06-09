#ifndef ANIRUNATOR_H
#define ANIRUNATOR_H

#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <ctime>
#include <cmath>
#include <stdexcept>

#include "TimeUtils.h"
#include "KeyBoard.h"

struct AniRunatorConfig {
    int foodVK;
    int runeVK;
    int rohVK;
    int softVK;

    //std::string lastDanceStep;
    int maxMana;
    double regenSec;
    int danceSec;
    int foodSec;
    int runeMana;
    int rohSec;
    int softSec;

    bool hasPromotion;
    bool hasDoubleRegen;
    bool hasRingOfHealing;
    bool hasSoftBoots;
    int hourLeftSoftBoots;
    int minLeftSoftBoots;
};

class AniRunator
{
    public:
        void showHeader();

        AniRunator();
        virtual ~AniRunator();

        void setup();
        void start();
        bool load();
        bool checkIfWantSetup(std::string description);

    private:
        AniRunatorConfig config;

        KeyBoard* kb;
        TimeUtils* t;

        int now;
        int danceTimeoutSeconds;
        int eatTimeoutSeconds;
        int runeTimeoutSeconds;
        int rohTimeoutSeconds;
        int softTimetoutSeconds;

        void eat(int foodToEat);
        void rune(int runeToMake);

        void save();

        void configLastDance();
        void configMaxMana();
        void configPromotion();
        void configDoubleRegen();
        void configRingOfHealing();
        void configSoftBoots();
};

#endif // ANIRUNATOR_H
