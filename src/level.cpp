#include "level.h"
#include <fstream>
#include <sstream>

//<! Construtor
Level::Level()
: m_rolls(0)
, m_cols(0)
, m_start_roll(0)
, m_start_col(0)
, m_apples(5)
{ /*empty*/ }

//<! carrega os levels enviados
void Level::load( std::string filename )
{
	//<! abre o arquivo contendo as fases
	std::fstream file;
    file.open(filename);

    if(file.is_open()){

    	//<! pega a quantidade de linhas e colunas
        std::string line;
        getline(file, line);
        std::stringstream stream(line);
        
        //<! Guarda o numero de linhas e colunas
        stream >> m_rolls;
        stream >> m_cols;

        size_t roll = 0; //<! linha do mapa que se está verificando
        size_t col  = 0; //<! coluna do mapa que se está verificando

        std::string s; //<! auxiliar
        
        //Guarda os simbolos
        while(file.get() != EOF){

            file.unget();
            char ch = file.get();
            s.push_back( ch );

            //<! verifica se passa para a próxima linha
            if ( ch == '\n' )
            {
                col = -1;
                roll++;
                levels.push_back( s ); 

                s = "";
            }

            //<! verifica se é a posição inicial
            else {
                if ( ch == 'c')
                {
                    m_start_roll = roll;
                    m_start_col  = col;
                }

                     
            }

                col++;   
            }    
        
        levels.push_back( s ); 
    }
}

void Level::print_lvl ()
{
	for( auto i( 0ul ); i < m_rolls; i++){
        for(auto j(0ul); j< m_cols; ++j)
            std::cout << levels[i][j];

        std::cout << std::endl;
    }
}

bool Level::is_blocked ( const Position & pos )
{
	auto roll = pos.roll;
	auto col  = pos.col;

	if ( levels[roll][col] != ' ' ) return true;
	else return false;
}

bool Level::is_solution ( const Position & pos )
{
	auto roll = pos.roll;
	auto col  = pos.col;

	if ( levels[roll][col] == 'm') return true;
	else return false; 
}

int Level::get_apples( )
{
	return m_apples;
}

void Level::generate_apple ()
{
	srand (time(NULL));
	bool aux = true;
	Position apple;
	while ( aux )
	{
		auto r = rand() % m_rolls;
		auto c = rand() % m_cols;
		apple.roll = r;
		apple.col  = c;
		aux = is_blocked( apple );
	}

	levels[apple.roll][apple.col] = 'm';
}

void Level::update_apples ()
{
	m_apples--;
}

void Level::mark_position( const Position & pos )
{
	levels[pos.roll][pos.col] = 'x';
}

void Level::mark_notsolution ( const Position & pos )
{
	levels[pos.roll][pos.col] = '/';
}

void Level::mark_decision ( const Position & pos )
{
	levels[pos.roll][pos.col] = 'd';
}
