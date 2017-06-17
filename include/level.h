#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "comum.h"

using type_level = std::vector<std::string>;

class Level
{

/*
 * CÓDIGOS DO LEVEL
 * # -> parede
 * . -> parede invisível
 * m -> maça
 * c -> cobra
 * x -> local vizitado
 * d -> ponto de decisão
 * / -> vizitado e não faz parte da solução
 */

private:
	size_t m_rolls;
	size_t m_cols;
	size_t m_start_roll;
	size_t m_start_col;
	int m_apples;
	type_level levels;

public:
	
	Level();

	/**
	 * @brief      Carrega o labirinto atravez de um arquivo passafo
	 *
	 * @param[in]  filename  O arquivo contendo os lvls
	 */
	void load ( std::string filename );

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
};


#endif