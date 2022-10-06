#pragma once
#include "Player.h"
class AI :
    public Player
{
public:
    AI();
    bool do_action(CELL_TYPE player_cell_type) override;
};

