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

class AniRunator
{
    public:
        KeyBoard* kb;

        TimeUtils* t;

        WORD runeVK;
        WORD foodVK;
        WORD rohVK;
        WORD softVK;

        std::string lastDanceStep;
        int maxMana;
        float regenSec;
        int danceSec;
        int foodSec;
        int runeMana;
        int rohSec;
        int softSec;

        bool hasDoubleRegen;
        bool hasPromotion;
        bool hasRingOfHealing;
        bool hasSoftBoots;
        int hourLeftSoftBoots;
        int minLeftSoftBoots;

        int now;

        int danceTimeoutSeconds;
        int eatTimeoutSeconds;
        int runeTimeoutSeconds;
        int rohTimeoutSeconds;
        int softTimetoutSeconds;

        AniRunator();
        virtual ~AniRunator();

        void setup();
        void start();

        void eat(int foodToEat);
        void rune(int runeToMake);

        void save();
        bool load();

        void configLastDance();
        void configMaxMana();
        void configPromotion();
        void configDoubleRegen();
        void configRingOfHealing();
        void configSoftBoots();

        bool checkIfWantSetup(std::string description);
};

#endif // ANIRUNATOR_H
