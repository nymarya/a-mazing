#include "level.h"
#include <fstream>
#include <sstream>

Level::Level()
{
    ls::list<data> lvl;
    levels = lvl;
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

    file.close();
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

	if ( current_lvl.lvl[roll][col] != ' ' ) return true;
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
}
