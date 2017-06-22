/**
 * @file level.cpp
 * @authors Gabriel Araújo de Souza e Mayra Dantas de Azevedo
 * @date 21 Junho 2017
 * @brief Arquivo contendo as implementações da classe Level.
 */

#include "level.h"
#include <fstream>
#include <sstream>

//<! Construtor
Level::Level()
{
    std::list<data> lvl;
    levels = lvl;
    m_current_lvl = 1;
    m_total_lvl = 1;
}

//<! carrega os levels enviados
void Level::load( std::string filename )
{
	//<! abre o arquivo contendo as fases
	std::fstream file;
    file.open(filename);
    bool ok = false; //<! verifica se o labirinto é válido.

    if(file.is_open()){
        while( file.get() != EOF )
        {
            file.unget();
            // pega a quantidade de linhas e colunas do 1º lvl
            std::string line;
            getline(file, line);
            std::stringstream stream(line);
            
            //<! Guarda o numero de linhas e colunas
            size_t rolls_;
            size_t cols_;
            stream >> rolls_;
            stream >> cols_;

            //<! construindo dados de uma fase
            data d;
            d.m_rolls = rolls_;
            d.m_cols = cols_;
            d.m_apples = 5;

            std::string s; //<! auxiliar
            char ch;
                                    
            for ( auto i(0u); i < rolls_; ++i )
            {   
                ch = file.get();
                //std::cout << "Oprimeiro:: " << ch << std::endl;
                auto j(0u);
                while ( (ch != '\n') and (ch != EOF)) 
                {
                    if ( j <= cols_)
                    {
                        s.push_back(ch);
                        if ( ch == '*' )
                        {
                            d.m_start_roll = i;
                            d.m_start_col  = j;
                            ok = true;
                        }
                        j++;
                    }
                    ch = file.get();
                    
                }
                d.lvl.push_back( s );
                s.clear();
            }

            if ( ok )
            {
                levels.push_back( d ); 
                ok = false;
            }
        }
    }
    m_total_lvl = levels.size();
    file.close();
}

//<! Recebe um mapa e retorna um novo objeto referente ao mapa
void Level::load( std::vector<std::string> new_map){
    data d;
    d.m_rolls = new_map.size();
    d.m_cols = new_map[0].size();

    for( auto i(0ul); i < new_map.size() ; ++i){
        for(auto j(0ul); j < new_map[0].size(); ++j){
            if( new_map[i][j] == '*'){
                d.m_start_roll = i;
                d.m_start_col  = j;
            }
        }
        d.lvl.push_back( new_map[i] );
    }

    levels.push_back( d );
}

//<!  Imprime uma fase
void Level::print_lvl ()
{
    auto current_lvl = levels.front();

	for( auto i( 0ul ); i < current_lvl.m_rolls; i++){
        for(auto j(0ul); j< current_lvl.m_cols; ++j)
            std::cout << current_lvl.lvl[i][j];

        std::cout << std::endl;
    }
}

//<! Verifica se uma posição do mapa é bloqueada
bool Level::is_blocked ( const Position & pos )
{
	auto roll = pos.roll;
	auto col  = pos.col;

    auto current_lvl = levels.front();

	if ( (current_lvl.lvl[roll][col] != ' ') and 
         (current_lvl.lvl[roll][col] != 'm') )
            return true;
	else return false;
}

//<! Verifica se uma posição é a solução
bool Level::is_solution ( const Position & pos )
{
	auto roll = pos.roll;
	auto col  = pos.col;

    auto current_lvl = levels.front();

	if ( current_lvl.lvl[roll][col] == 'm') return true;
	else return false; 
}

//<! Recupera a quantidade de maçãs restantes
int Level::get_apples( )
{
    auto current_lvl = levels.front();
	return current_lvl.m_apples;
}

//<! Gera aleatoriamente uma nova maçã no jogo
void Level::generate_apple ()
{
    auto current_lvl = levels.begin();

    (*current_lvl).lvl[m_apple_pos.roll][m_apple_pos.col] = ' ';

	srand (time(NULL));
	bool aux = true;
	Position apple;
	while ( aux )
	{
		auto r = rand() % ((*current_lvl).m_rolls -2 ) + 1;
		auto c = rand() % ( (*current_lvl).m_cols -2 ) + 1;
		apple.roll = r;
		apple.col  = c;
		aux = is_blocked( apple ) or apple == m_apple_pos;
	}

	(*current_lvl).lvl[apple.roll][apple.col] = 'm';
    m_apple_pos = apple;
}

//<! Atualiza a quantidade de maçãs restantes
void Level::update_apples ()
{
    auto current_lvl = levels.begin();
	((*current_lvl).m_apples)--;
}

//<! marca uma posição como visitada
void Level::mark_position( const Position & pos )
{
    auto current_lvl = levels.begin();
	(*current_lvl).lvl[pos.roll][pos.col] = 'x';
}

//<! Marca uma posição como não faz parte da solução
void Level::mark_notsolution ( const Position & pos )
{
    auto current_lvl = levels.begin();
	(*current_lvl).lvl[pos.roll][pos.col] = '/';
}

//<! marca um ponto de decisão tomado para achar a solução
void Level::mark_decision ( const Position & pos )
{
    auto current_lvl = levels.begin();
	(*current_lvl).lvl[pos.roll][pos.col] = 'd';
}

//<! retorna a posição inicial que a cobra deve está em uma fase
Position Level::get_start_position ()
{
    auto current_lvl = levels.begin();
	Position pos;
	pos.roll = (*current_lvl).m_start_roll;
	pos.col  = (*current_lvl).m_start_col;

	return pos;
}

//<! retorna o mapa do level atual
type_level Level::get_level ()
{
    auto current_lvl = levels.front();
	return current_lvl.lvl;
}

//<! avança um nível
void Level::next_level ()
{
    levels.pop_front();
    m_current_lvl++;
}

//<! pega o total de vidas
int Level::get_total_lvls ()
{
    return m_total_lvl;
}

//<! diz em qual nível está no momento
int Level::get_current_lvl ()
{
    return m_current_lvl;
}

//<! pega a quantidade de linha do mapa
size_t Level::get_rolls () const
{
    return levels.front().m_rolls;
}

//<! pega a quantidade de colunas do mapa atual
size_t Level::get_cols () const
{
    return levels.front().m_cols;
}

//<! verifica se uma dada posição é um ponto de decisão
bool Level::is_decision ( const Position & pos )
{
    auto roll = pos.roll;
    auto col  = pos.col;

    auto current_lvl = levels.front();

    if ( current_lvl.lvl[roll][col] == 'd' ) return true;
    else return false;
}
