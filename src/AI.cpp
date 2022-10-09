#include "AI.h"
#include "GameField.h"
#include "Globals.h"
#include <random>
#include <thread>

weight_pattern::weight_pattern(size_t weight_, std::vector<bool> pattern_)
{
	weight = weight_;
	pattern = pattern_;
}


AI::AI(FIELD_SIZE field_size)
{
	switch (field_size)
	{
	case FIELD_SIZE::SIZE_3x3:
		ai_patterns.push_back(weight_pattern(5000, std::vector<bool> {true, true, true}));
		ai_patterns.push_back(weight_pattern(3500, std::vector<bool> {false, true, true}));
		ai_patterns.push_back(weight_pattern(2000, std::vector<bool> {false, false, true}));
		ai_patterns.push_back(weight_pattern(1000, std::vector<bool> {false, false, false}));
		break;
	case FIELD_SIZE::SIZE_5x5:
		ai_patterns.push_back(weight_pattern(10000, std::vector<bool> {false, true, true, true, true}));
		ai_patterns.push_back(weight_pattern(5000, std::vector<bool> {false, false, true, true, true}));
		ai_patterns.push_back(weight_pattern(3500, std::vector<bool> {false, false, false, true, true}));
		ai_patterns.push_back(weight_pattern(2000, std::vector<bool> {false, false, false, false, true}));
		ai_patterns.push_back(weight_pattern(1000, std::vector<bool> {false, false, false, false, false}));
		break;
	}
}

bool AI::do_action(CELL_TYPE player_cell_type)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	std::vector<FieldCell*> field_cells_array = GameField::get_instance()->get_field_cells_array();
	size_t line_len = (GameField::get_instance()->get_field_size() == FIELD_SIZE::SIZE_3x3) ? 3 : 5;

	if (GameField::get_instance()->get_last_filled_cell() == nullptr)
	{
		FieldCell* field_cell = field_cells_array[(line_len * line_len - 1) / 2];
		return GameField::get_instance()->try_to_fill_cell(field_cell, player_cell_type);
	}
	else
	{
		FieldCell* field_cell = field_cells_array[(line_len * line_len - 1) / 2];
		if (field_cell->get_current_type() == CELL_TYPE::CELL_EMPTY)
		{
			return GameField::get_instance()->try_to_fill_cell(field_cell, player_cell_type);
		}
	}

	std::vector<field_line> field_lines = scan_for_lines(line_len, field_cells_array);
	std::vector<field_line> field_diagonal_lines = scan_for_dioganal_lines(line_len, field_cells_array);
	for (size_t i = 0; i < field_diagonal_lines.size(); i++)
	{
		field_lines.insert(field_lines.begin(), field_diagonal_lines[i]);
	}
	field_line max_attack_weight_line = get_max_weight_line(field_lines, player_cell_type);

	CELL_TYPE opponent_cell_type = (player_cell_type == CELL_TYPE::CELL_CROSS) ? CELL_TYPE::CELL_ZERO : CELL_TYPE::CELL_CROSS;
	field_line max_defence_weight_line = get_max_weight_line(field_lines, opponent_cell_type);

	field_line line_to_put_cell;
	if (max_attack_weight_line.weight == max_defence_weight_line.weight && max_attack_weight_line.weight == 0)
	{
		line_to_put_cell = get_available_line(field_lines);
	}
	else
	{
		line_to_put_cell = (max_attack_weight_line.weight > max_defence_weight_line.weight * 0.95) ? max_attack_weight_line : max_defence_weight_line;
	}

	std::vector<FieldCell*> empty_cells;
	for (size_t i = 0; i < line_len; i++)
	{
		FieldCell* field_cell = line_to_put_cell.cells_in_line[i];
		if (field_cell->get_current_type() == CELL_TYPE::CELL_EMPTY)
		{
			empty_cells.push_back(field_cell);
		}
	}

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> line_num(0, empty_cells.size() - 1);
	
	FieldCell* field_cell = empty_cells[line_num(generator)];
	return GameField::get_instance()->try_to_fill_cell(field_cell, player_cell_type);


	return false;
}


field_line AI::get_max_weight_line(std::vector<field_line>lines_array, CELL_TYPE player_cell_type)
{
	size_t max_value = 0;
	field_line max_weight_line;
	for (size_t line_num = 0; line_num < lines_array.size(); line_num++)
	{
		field_line line = lines_array[line_num];
		std::vector<bool> sanitized_line;

		for (size_t line_cell_num = 0; line_cell_num < line.cells_in_line.size(); line_cell_num++)
		{
			FieldCell* field_cell = line.cells_in_line[line_cell_num];
			if (field_cell->get_current_type() == CELL_TYPE::CELL_EMPTY)
			{
				sanitized_line.insert(sanitized_line.begin(), false);
			}
			else if (field_cell->get_current_type() == player_cell_type)
			{
				sanitized_line.push_back(true);
			}
			else
			{
				sanitized_line.clear();
				break;
			}
		}

		if (!sanitized_line.size())
		{
			continue;
		}

		for (size_t pattern_num = 0; pattern_num < ai_patterns.size(); pattern_num++)
		{
			weight_pattern* holder = &ai_patterns[pattern_num];
			
			if (sanitized_line == holder->pattern && holder->weight > max_value)
			{
				max_value = holder->weight;
				line.weight = max_value;
				max_weight_line = line;
			}
		}
	}
	return max_weight_line;
}


field_line AI::get_available_line(std::vector<field_line> lines_array)
{
	std::vector<field_line> possible_lines;
	for (size_t line_num = 0; line_num < lines_array.size(); line_num++)
	{
		field_line line = lines_array[line_num];
		for (size_t i = 0; i < line.cells_in_line.size(); i++)
		{
			FieldCell* field_cell = line.cells_in_line[i];
			if (field_cell->get_current_type() == CELL_TYPE::CELL_EMPTY)
			{
				possible_lines.push_back(line);
				break;
			}
		}
	}

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> line_num(0, possible_lines.size() - 1);
	return possible_lines[line_num(generator)];
}


std::vector<field_line> AI::scan_for_lines(size_t line_len, std::vector<FieldCell*>&field_cells_array)
{
	std::vector<field_line> lines_array;
	for (size_t y = 0; y < line_len; y++)
	{
		field_line horizontal_line;
		field_line vertical_line;
		for (size_t x = 0; x < line_len; x++)
		{
			size_t array_index = x + y * line_len;
			FieldCell* field_cell = field_cells_array[array_index];
			horizontal_line.cells_in_line.push_back(field_cell);
	
			array_index = y + x * line_len;
			field_cell = field_cells_array[array_index];
			vertical_line.cells_in_line.push_back(field_cell);
		}
		lines_array.push_back(horizontal_line);
		lines_array.push_back(vertical_line);
	}
	return lines_array;
}


std::vector<field_line> AI::scan_for_dioganal_lines(size_t line_len, std::vector<FieldCell*>& field_cells_array)
{
	std::vector<field_line> diagonal_lines;
	field_line line_to_right;
	field_line line_to_left;

	for (size_t i = 0; i < line_len; i++)
	{
		size_t array_index = i + i * line_len;
		FieldCell* field_cell = field_cells_array[array_index];
		line_to_right.cells_in_line.push_back(field_cell);

		array_index = line_len - i - 1 + i * line_len;
		field_cell = field_cells_array[array_index];
		line_to_left.cells_in_line.push_back(field_cell);
	}
	diagonal_lines.push_back(line_to_left);
	diagonal_lines.push_back(line_to_right);

	return diagonal_lines;
}