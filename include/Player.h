#pragma once

enum class CELL_TYPE;

class Player
{
public:
	Player();
	virtual bool do_action(CELL_TYPE player_cell_type) = 0;
};

