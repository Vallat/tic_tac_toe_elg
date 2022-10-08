#pragma once
#include "Player.h"
class Human :
    public Player
{
public:
    Human();

    /// <summary>
    /// Scans for mouse input to try to fill FieldCell
    /// </summary>
    /// <returns>true if cell was set to players cell type</returns>
    bool do_action(CELL_TYPE player_cell_type) override;
};

