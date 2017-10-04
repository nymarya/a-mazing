/**
 * @file player.h
 * @authors Gabriel Araújo de Souza e Mayra Dantas de Azevedo
 * @date 21 Junho 2017
 * @brief Arquivo contendo as definições da classe Player.
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stack>
#include <list>
#include "level.h"
#include "snake.h"
#include "Vector/vector.h"
#include "Hash/hash_tbl.h"
#include "comum.h"

/**
 * @brief      Define o que significa um movimento
 */
struct Move
{
	Position pos; //<! A posição do movimento
	std::vector<direction_t> dir; //<! As direções tomadas para chegar nessa posição
	std::deque < Position > snake_body;	//<! A posição da snake naquela posição

	/**
	 * @brief      Atribui um novo movimento
	 *
	 * @param[in]  rhs   O novo movimento para ser atribuido
	 *
	 * @return     O novo movimento 
	 */
	Move & operator=( const Move & rhs )
	{
		pos.roll = rhs.pos.roll;
		pos.col = rhs.pos.col;

		dir = rhs.dir;
		return *this;
	}
};

/**
 * @brief      Classe para o Player
 */
class Player
{
	private:
		std::vector<direction_t> m_solution; //<! Direções para se chegar a uma solução
		int m_lifes; //<! quantidade de vidas restates

		Snake * snk; //<! Ponteiro para a snake
		Level * lvl; //<! Ponteiro para o level
		

	public:
		/**
		* @brief      Construtor default;
		*/
		Player ();

		/**
		 * @brief      Destrói o objeto
		 */
		~Player () = default;

		/**
		 * @brief      Faz o jogador ter acesso ao level atual
		 *
		 * @param      l_    o level atual
		 */
		void bind_level ( Level & l_ );

		/**
		 * @brief      Faz o jogador ter acesso a snake
		 *
		 * @param      s_   snake
		 */
		void bind_snake ( Snake & s_ );

		/**
		* @brief      Retorna uma direção para a snake que faz parte da 
		*             solução encontrada.
		*
		* @return     Uma direção da solução
		*/
		direction_t next_move ();

		/**
		* @brief      Procura por um solução para o labirinto
		*
		* @return     True se existe posição, false caso contrário
		*/
		bool find_solution ( Position initial_pos );

		/**
		 * @brief      Imprime a solução encontrada pelo player
		 */
		void print ();

};

#endif