#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stack>
#include "level.h"
#include "snake.h"
#include "Vector/vector.h"
#include "Hash/hash_tbl.h"
#include "comum.h"

struct Move
{
	Position pos;
	std::vector<direction_t> dir;

	Move & operator=( const Move & rhs )
	{
		pos.roll = rhs.pos.roll;
		pos.col = rhs.pos.col;

		dir = rhs.dir;
		return *this;
	}
};

class Player
{

	private:
		
		std::vector<direction_t> m_solution;
		int m_lifes;

		Snake * snk;
		Level *lvl;
		

	public:

		/**
		* @brief      Construtor default;
		*/
		Player();

		/**
		* @brief      Retorna uma direção para a snake que faz parte da 
		*             solução encontrada.
		*
		* @return     Uma direção da solução
		*/
		direction_t next_move();

		/**
		* @brief      Procura por um solução para o labirinto
		*
		* @return     True se existe posição, false caso contrário
		*/
		bool find_solution ( std::vector<std::string> & map, Position initial_pos );

		void print();

};


#endif