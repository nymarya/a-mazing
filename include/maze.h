#ifndef _MAZE_H_
#define _MAZE_H_

#include <iostream>
#include <vector>
#include <string>

class Maze{

	private:

		std::vector< std::string > map; //<! mapa
		std::size_t m_rolls;			//<! quantidade de linhas
		std::size_t m_cols; 			//<! quantidade de colunas
		std::size_t m_start_roll;		//<! linha inicial
		std::size_t m_start_col;		//<! coluna inicial

	public:

		struct Position{
			int roll; //<! linha do mapa 
			int col;  //<! coluna do mapa
		};

		enum class direction_t : int
        {
            NORTH = 0,  // ( 0, -1) => (-1, 0)
            SOUTH,      // ( 0,  1) => (1, 0)
            EAST,       // (-1,  0) => (0, -1)
            WEST,       // ( 1,  0) => (0, 1)
		};

		// * -> posição inicial
		// # -> parede
		// . -> parede invisível
		// $ -> saída
		// x -> já passou e é válido
		// / -> sem saída
		// " " -> não foi vizitado


		struct Direction{
			std::size_t height; //<! 
			std::size_t weight; //<! 
		};

		Maze();

		void load( std::string filename);

		Position get_start_position();
		bool is_outside(const Position& pos);
		bool is_blocked(const Position& pos, const Direction& dir);
		void mark_cell(const Position& pos );
		void unmark_cell(const Position& pos );
		bool is_marked(const Position& pos);

		void render();
};

#endif