#include <iostream>

#include "AniRunator.h"

int main() {
    AniRunator* ani = new AniRunator();

    ani->load();

    if(ani->checkIfWantSetup("Nova config?")) {
        ani->setup();
    }

    std::cout << "Aguardando 10 segundos pra comecar o trabaio, deixa o tibao em primeiro plano" << std::endl;
    Sleep(1000);

    ani->start();

    return 0;
}
