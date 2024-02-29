#include "./Game/Game.h"
#include <ctime>


int main() {
    srand(time(nullptr));
    Game game(640, 480, "Overthink Physics 2D Engine");
    game.run();

    return 0;
}
