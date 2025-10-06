#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "Layer.h"


class GameLayer  : public Core::Layer{
public:
    GameLayer();

    virtual ~GameLayer();


    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnEvent(Core::Event& event) override;
};



#endif //GAMELAYER_H
