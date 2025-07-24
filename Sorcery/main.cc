#include <iostream>
#include <string>
#include "player.h"
#include "game.h"


int main(int argc, char* argv[]) {
    std::string deck1 = "default.deck";
    std::string deck2 = "default.deck";
    std::string initFile = "";
    bool isTesting = false;
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
        } else {
            std::cerr << "Unknown or incomplete argument: " << arg << std::endl;
            return 1;
        }
    }

    

    return 0;
}