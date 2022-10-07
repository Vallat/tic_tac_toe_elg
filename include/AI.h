#pragma once
#include "Player.h"
#include <FieldCell.h>
#include <vector>
#include <map>

struct weight_pattern
{
    std::vector<bool> pattern;
    size_t weight = 0;

    weight_pattern(size_t weight_, std::vector<bool> pattern_);
};


struct field_line
{
    std::vector<FieldCell*> cells_in_line;
    size_t value = 0;
};


class AI :
    public Player
{
public:
    AI(FIELD_SIZE field_size);
    bool do_action(CELL_TYPE player_cell_type) override;

    std::vector<field_line> scan_for_lines(size_t line_len, std::vector<FieldCell*>& field_cells_array, CELL_TYPE player_cell_type);
    std::vector<field_line> scan_for_dioganal_lines(size_t line_len, std::vector<FieldCell*>& field_cells_array, CELL_TYPE player_cell_type);

    field_line get_max_weight_line(std::vector<field_line> lines_array, CELL_TYPE player_cell_type);

    field_line get_available_line(std::vector<field_line> lines_array);

private:
    std::vector<weight_pattern> ai_patterns;
};

