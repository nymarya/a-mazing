#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <string>
#include <vector>
#include <iostream>

class Level
{

private:
	size_t m_rolls;
	size_t m_cols;
	size_t m_start_roll;
	size_t m_start_col;
	std::vector<std::string> levels;

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



};


#endif