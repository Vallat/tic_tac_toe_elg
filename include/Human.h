#pragma once
#include "Player.h"
class Human :
    public Player
{
public:
    Human();
    bool do_action() override;
};

