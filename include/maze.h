#ifndef _MAZE_H_
#define _MAZE_H_

#include <iostresam>
#include <vector>
#include <string>

class Maze{

	private:
		struct Position{
			int x;
			int y;
		};

		enum class direction_t : int
        {
            NORTH = 0,  // ( 0, -1).
            SOUTH,      // ( 0,  1)
            EAST,       // (-1,  0)
            WEST,       // ( 1,  0)
		};

		struct Direction{
			Position pos;
			direction_t type;
		};

		std::vector< std::string > map;
		std::size_t m_rolls;
		std::size_t m_cols; 
		std::size_t start_roll;
		std::size_t start_col;

	public:

		Maze();
		~Maze();

		Position get_start_position();
		bool is_outside(const Position& pos);
		bool is_blocked(const Position& pos, const Direction& dir);
		void mark_cell(const Position& pos );
		void unmark_cell(const Position& pos );
		bool is_marked(const Position& pos);
};

#endif