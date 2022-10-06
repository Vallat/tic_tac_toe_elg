#pragma once
#include "Player.h"
class AI :
    public Player
{
public:
    AI();
    bool do_action() override;
};

