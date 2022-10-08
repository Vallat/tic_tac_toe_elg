#pragma once
#include "Player.h"
#include <FieldCell.h>
#include <vector>
#include <map>

/// <summary>
/// Structure to store weighted AI behaviour patterns
/// </summary>
struct weight_pattern
{
    std::vector<bool> pattern;
    size_t weight = 0;

    weight_pattern(size_t weight_, std::vector<bool> pattern_);
};

/// <summary>
/// Structure to analyze line of cells and give it its weight if it matches any of AI patterns
/// </summary>
struct field_line
{
    std::vector<FieldCell*> cells_in_line;
    size_t weight = 0;
};


class AI :
    public Player
{
public:
    AI(FIELD_SIZE field_size);
    bool do_action(CELL_TYPE player_cell_type) override;

    /// <summary>
    /// Scans for all vertical and horizontal lines on the game field
    /// </summary>
    /// <returns>vector of lines structure</returns>
    std::vector<field_line> scan_for_lines(size_t line_len, std::vector<FieldCell*>& field_cells_array, CELL_TYPE player_cell_type);

    /// <summary>
    /// Scans for two diagonal lines on the game field
    /// </summary>
    /// <returns>vector of lines structure</returns>
    std::vector<field_line> scan_for_dioganal_lines(size_t line_len, std::vector<FieldCell*>& field_cells_array, CELL_TYPE player_cell_type);

    /// <summary>
    /// Scans for the line with max weight based on AI patterns
    /// </summary>
    /// <returns>the line with max weight</returns>
    field_line get_max_weight_line(std::vector<field_line> lines_array, CELL_TYPE player_cell_type);

    /// <summary>
    /// Scans for any line where we can put our symbol
    /// </summary>
    /// <returns>any available line</returns>
    field_line get_available_line(std::vector<field_line> lines_array);

private:
    std::vector<weight_pattern> ai_patterns;
};

