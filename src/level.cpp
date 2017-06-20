#include "level.h"
#include <fstream>
#include <sstream>

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

void Level::print_lvl ()
{
    auto current_lvl = levels.front();

	for( auto i( 0ul ); i < current_lvl.m_rolls; i++){
        for(auto j(0ul); j< current_lvl.m_cols; ++j)
            std::cout << current_lvl.lvl[i][j];

        std::cout << std::endl;
    }
}

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

bool Level::is_solution ( const Position & pos )
{
	auto roll = pos.roll;
	auto col  = pos.col;

    auto current_lvl = levels.front();

	if ( current_lvl.lvl[roll][col] == 'm') return true;
	else return false; 
}

int Level::get_apples( )
{
    auto current_lvl = levels.front();
	return current_lvl.m_apples;
}

void Level::generate_apple ()
{
    auto current_lvl = levels.begin();

    (*current_lvl).lvl[m_apple_pos.roll][m_apple_pos.col] = ' ';

	srand (time(NULL));
	bool aux = true;
	Position apple;
	while ( aux )
	{
		auto r = rand() % (*current_lvl).m_rolls;
		auto c = rand() % (*current_lvl).m_cols;
		apple.roll = r;
		apple.col  = c;
		aux = is_blocked( apple );
	}

	(*current_lvl).lvl[apple.roll][apple.col] = 'm';
    m_apple_pos = apple;
}

void Level::update_apples ()
{
    auto current_lvl = levels.begin();
	((*current_lvl).m_apples)--;
}

void Level::mark_position( const Position & pos )
{
    auto current_lvl = levels.begin();
	(*current_lvl).lvl[pos.roll][pos.col] = 'x';
}

void Level::mark_notsolution ( const Position & pos )
{
    auto current_lvl = levels.begin();
	(*current_lvl).lvl[pos.roll][pos.col] = '/';
}

void Level::mark_decision ( const Position & pos )
{
    auto current_lvl = levels.begin();
	(*current_lvl).lvl[pos.roll][pos.col] = 'd';
}

Position Level::get_start_position ()
{
    auto current_lvl = levels.begin();
	Position pos;
	pos.roll = (*current_lvl).m_start_roll;
	pos.col  = (*current_lvl).m_start_col;

	return pos;
}

type_level Level::get_level ()
{
    auto current_lvl = levels.front();
	return current_lvl.lvl;
}

void Level::next_level ()
{
    levels.pop_front();
    m_current_lvl++;
}

int Level::get_total_lvls ()
{
    return m_total_lvl;
}

int Level::get_current_lvl ()
{
    return m_current_lvl;
}

size_t Level::get_rolls () const
{
    return levels.front().m_rolls;
}

size_t Level::get_cols () const
{
    return levels.front().m_cols;
}

bool Level::is_decision ( const Position & pos )
{
    auto roll = pos.roll;
    auto col  = pos.col;

    auto current_lvl = levels.front();

    if ( current_lvl.lvl[roll][col] == 'd' ) return true;
    else return false;
}
