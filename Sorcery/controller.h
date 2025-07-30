#include <string>

class Game;

class Controller {
    Game& game;
    public:
        Controller(Game& game);
        void play();
        void executeCommand(const std::string& cmd);
        void initGame(const std::string& initFilePath);
};
