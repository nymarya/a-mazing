#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "comum.h"
#include "List/list.h"


using type_level = std::vector<std::string>;

class Level
{

/*
 * CÓDIGOS DO LEVEL
 * # -> parede
 * . -> parede invisível
 * m -> maça
 * * -> ponto inicial
 * c -> cobra
 * x -> local visitado
 * d -> ponto de decisão
 * / -> visitado e não faz parte da solução
 */

private:

	struct data
	{
		size_t m_rolls;
		size_t m_cols;
		size_t m_start_roll;
		size_t m_start_col;
		int m_apples;
		type_level lvl;

		/**
		 * @brief      Construtor básico
		 */
		data ( )
			: m_rolls(0)
			, m_cols(0)
			, m_start_roll(0)
			, m_start_col(0)
			, m_apples(5)
		{/*empty*/}
	};

	ls::list<data> levels;
	int m_current_lvl;
	int m_total_lvl;
	Position m_apple_pos;
	

public:
	
	/**
	 * @brief      Construtor
	 */
	Level();

	/**
	 * @brief      Destroi o objeto
	 */
	~Level() = default;

	/**
	 * @brief      Carrega o labirinto atravez de um arquivo passafo
	 *
	 * @param[in]  filename  O arquivo contendo os lvls
	 */
	void load ( std::string filename );

	void load ( std::vector< std::string > new_map);

	/**
	 * @brief      Imprime um level
	 *
	 * @param      lvl   O level
	 */
	void print_lvl ();

	/**
	 * @brief      Verifica se um dada posição que a snake
	 *             deseja ir é bloqueada.
	 *
	 * @param[in]  pos   A posição
	 *
	 * @return     True se bloqueado, False caso contrário.
	 */
	bool is_blocked ( const Position & pos );

	/**
	 * @brief      Verifica se uma posição que a cobra deseja ir
	 *             é o seu objetivo final, ou seja, a maçã
	 *
	 * @param[in]  pos   A posição
	 *
	 * @return     True se for a solução, False caso contrário.
	 */
	bool is_solution ( const Position & pos );

	/**
	 * @brief      Recupera a quantidade de maçãs restantes na fase
	 *
	 * @return     A quantidade de maçãs
	 */
	int get_apples ();

	/**
	 * @brief      Gera uma maçã no labirinto
	 */
	void generate_apple ();

	/**
	 * @brief      Reduz uma maçã da quantidade restante do level.
	 */
	void update_apples ();

	/**
	 * @brief      Marca uma posição como visitada
	 *
	 * @param[in]  pos   A posição.
	 */
	void mark_position ( const Position & pos );

	/**
	 * @brief      Marca uma posição como visitada e não 
	 *             faz parte da solução
	 *
	 * @param[in]  pos   A posição
	 */
	void mark_notsolution ( const Position & pos );

	/**
	 * @brief      Marca uma posição como um ponto de decisão
	 *
	 * @param[in]  pos   A posição
	 */
	void mark_decision ( const Position & pos );

	/**
	 * @brief      Pega a posição inicial da cobra
	 *
	 * @return     A posição inicial
	 */
	Position get_start_position ();

	/**
	 * @brief      Pega o level
	 *
	 * @return     o level atual.
	 */
	type_level get_level ();

	/**
	 * @brief      Avança para o próximo level
	 */
	void next_level ();

	/**
	 * @brief      Pega a quantidade total de levels
	 *
	 * @return     O total de levels
	 */
	int get_total_lvls ();

	/**
	 * @brief      Pega o nível atual
	 *
	 * @return     O nível atual.
	 */
	int get_current_lvl ();

	size_t get_rolls() const;

	size_t get_cols() const;

	/**
	 * @brief      Verifica se uma posição é um ponto de 
	 *             decisão
	 *
	 * @param[in]  pos   A posição
	 *
	 * @return     True se decisão, False caso contrário.
	 */
	bool is_decision ( const Position & pos );

};


#endif