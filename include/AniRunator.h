#ifndef ANIRUNATOR_H
#define ANIRUNATOR_H

#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <ctime>

#include "KeyBoard.h"

class AniRunator
{
    public:
        KeyBoard* kb;

        WORD runeVK;
        WORD foodVK;
        WORD rohVK;
        WORD softVK;

        int maxMana;
        float regenSec;

        bool hasDoubleRegen;
        bool hasPromotion;
        bool hasRingOfHealing;
        bool hasSoftBoots;
        int hourLeftSoftBoots;
        int minLeftSoftBoots;

        AniRunator();
        virtual ~AniRunator();

        void setup();
        void start();

        void eat(int foodToEat);
        void rune(int runeToMake);

        void save();
        bool load();

        void configMaxMana();
        void configPromotion();
        void configDoubleRegen();
        void configRingOfHealing();
        void configSoftBoots();

        bool checkIfWantSetup(std::string description);
};

#endif // ANIRUNATOR_H
