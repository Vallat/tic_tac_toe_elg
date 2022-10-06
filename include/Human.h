#pragma once
#include "Player.h"
class Human :
    public Player
{
public:
    Human();
    bool do_action(CELL_TYPE player_cell_type) override;
};

