#include "maze.h"
#include <fstream>
#include <sstream>

//<! Construtor
Maze::Maze()
: m_rolls(0)
, m_cols(0)
, m_start_roll(0)
, m_start_col(0)
{ /*empty*/ }


void Maze::load( std::string filename){
    std::fstream file;

    file.open(filename);

    if(file.is_open()){

        std::string line;
        getline(file, line);
        std::stringstream stream(line);
        
        //Guarda o numero de linhas e colunas
        stream >> m_cols;
        stream >> m_rolls;

        size_t roll = 0; //<! linha do mapa que se está verificando
        size_t col  = 0; //<! coluna do mapa que se está verificando

        //Guarda os simbolos
        while(file.get() != EOF){
            //<! avança a coluna
            col++;
            std::string s;
            file.unget();
            s.push_back( file.get() );

            //<! verifica se passa para a próxima linha
            if ( s == "\n" )
            {
                col = 0;
                roll++;
            }

            //<! verifica se é a posição inicial
            else {
                if ( s == "*")
                {
                    m_start_roll = roll;
                    m_start_col  = col;
                }
                map.push_back( s );      
            }    
        }
    }
}

Maze::Position Maze::get_start_position()
{
    Position aux;
    aux.roll = m_start_roll;
    aux.col = m_start_col;

    return aux;
}

bool Maze::is_outside(const Position& pos)
{
    auto r = pos.roll;
    auto c = pos.col;

    //if ( map[r][c] == "." ) return true;

    return  false;
}

// bool is_blocked(const Position& pos, const Direction& dir);

void Maze::mark_cell(const Position& pos ){
    auto location = pos.roll * m_cols + pos.col-1;
    *(map.begin()+location) = 'x';

    std::cout << map[ pos.roll ][ pos.col ] << std::endl;
}
void Maze::render(){
    auto cont(0);
    for( auto i( map.begin() ); i != map.end(); ){
        std::cout << *i++;
        cont++;
        if( std::distance(map.begin(), i)%m_cols == 0)
            std::cout <<std::endl;
    }
}

