#include <iostream>
#include "Core/Application.h"
#include "GameLayer.h"

int main() {
    Core::Application Game({"Labyrinth"});
    Game.PushLayer<GameLayer>();
    Game.Run();
    return 0;
}