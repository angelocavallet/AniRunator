#include <iostream>

#include "AniRunator.h"

int main() {
    AniRunator* ani = new AniRunator();
    ani->showHeader();

    bool loaded = ani->load();


    if(!loaded || ani->checkIfWantSetup("Nova config?")) {
        ani->setup();
    }

    std::cout << "Aguardando 10 segundos pra comecar o trabaio, deixa o tibao em primeiro plano" << std::endl;
    Sleep(10000);

    ani->start();

    return 0;
}
