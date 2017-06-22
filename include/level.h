/**
 * @file level.h
 * @authors Gabriel Araújo de Souza e Mayra Dantas de Azevedo
 * @date 21 Junho 2017
 * @brief Arquivo contendo as definições da classe Level.
 */


#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <iostream>
#include <cstdlib>
#include "comum.h"
#include "List/list.h"

//<! tipo de um mapa do level
using type_level = std::vector<std::string>;

/**
 * @brief      Classe para os leveis do jogo
 */
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

	/**
	 * @brief      Dados de um jogo
	 */
	struct data
	{
		size_t m_rolls;  //<! números de linhas
		size_t m_cols;	 //<! número de colunas
		size_t m_start_roll; //<! linha inicial da cobra
		size_t m_start_col;	 //<! coluna inicial da cobra
		int m_apples;		//<! quantidade de maçãs do nível
		type_level lvl;		//<! mapa do level

		/**
		 * @brief      Construtor básico
		 */
		data ( )
			: m_rolls(0)
			, m_cols(0)
			, m_start_roll(0)
			, m_start_col(0)
			, m_apples(5)
		{
			/*empty*/ 
		}

		/**
		 * @brief      atribui um novo dara
		 *
		 * @param[in]  rhs   o data a ser atribuido
		 *
		 * @return    	o novo data
		 */
		data & operator=( const data & rhs )
		{
			std::cout << rhs.lvl.size() << std::endl;

			m_rolls = rhs.m_rolls;
			m_cols = rhs.m_cols;
			m_start_roll = rhs.m_start_roll;
			m_start_col = rhs.m_start_col;
			m_apples = rhs.m_apples;
			lvl = rhs.lvl;

			return *this;
		}
	};

	std::list<data> levels; //<! lista contendo os níveis
	int m_current_lvl;		//<! level atual
	int m_total_lvl;		//<! Total de level carregados 
	Position m_apple_pos;	//<! Posição da maçã no level
	

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

	/**
	 * @brief      Constroi um novo objeto por meio de um mapa
	 *
	 * @param[in]  new_map  O novo mapa
	 */
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

	/**
	 * @brief      Recupera a quantidade de linhas de uma fase
	 *
	 * @return     A quantidade de linhas
	 */
	size_t get_rolls() const;

	/**
	 * @brief      Recupera a quantidades de colunas de uma fase
	 *
	 * @return     A quantidade de colunas
	 */
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

	/**
	 * @brief      Atribui um novo nível
	 *
	 * @param[in]  rhs   O nível a ser atribuido
	 *
	 * @return     O novo level
	 */
	Level & operator=( const Level & rhs )
	{
		levels.resize( rhs.levels.size() );
		std::cout << rhs.levels.size() << std::endl;
		std::copy(rhs.levels.begin(), rhs.levels.end(), levels.begin() );
		//levels = rhs.levels;
		m_current_lvl = rhs.m_current_lvl;
		m_total_lvl = rhs.m_total_lvl;
		m_apple_pos = rhs.m_apple_pos;

		return *this;
	}

	/**
	 * @brief      Recupera a posição da maçã
	 *
	 * @return     A posição da maçã
	 */
	Position get_apple()
	{
		return m_apple_pos;
	}

};


#endif