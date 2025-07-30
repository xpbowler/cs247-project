#include <iostream>
#include <string>
#include "game.h"


int main(int argc, char* argv[]) {
    std::string deck1 = "default.deck";
    std::string deck2 = "default.deck";
    std::string initFile = "";
    bool isTesting = false;
    bool bonusFeatures = false;
    for (int i=1;i<argc;++i) {
        std::string arg = argv[i];
        if (arg=="-deck1" && i+1<argc) {
            deck1 = argv[++i];
        } else if (arg=="-deck2" && i+1<argc) {
            deck2 = argv[++i];
        } else if (arg=="-init" && i+1<argc) {
            initFile = argv[++i];
        } else if (arg=="-testing") {
            isTesting = true;
        } else if (arg=="-enableBonus") {
            // enables the game's bonus features
            bonusFeatures = true;
        } else {
            std::cerr << "Unknown or incomplete argument: " << arg << std::endl;
            return 1;
        }
    }

    if (initFile=="") {
        throw std::invalid_argument("initialization file was not provided.");
    }

    Game game = Game{deck1, deck2, initFile, isTesting, bonusFeatures};
    game.play();

    return 0;
}
