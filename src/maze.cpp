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


        std::string s;
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
                map.push_back( s ); 

                s = "";
            }

            //<! verifica se é a posição inicial
            else {
                if ( ch == '*')
                {
                    m_start_roll = roll;
                    m_start_col  = col;
                }

                     
            }

                col++;   
            }    
        
        map.push_back( s ); 
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

    if ( map[r][c] == '.' ) return true;

    return  false;
}

bool Maze::is_blocked(const Position& pos, const Direction& dir)
{
    auto r = pos.roll + dir.height;
    auto c = pos.col + dir.weight;

    if ( map[r][c] == '#' ) return true;

    return false;
}

void Maze::mark_cell(const Position& pos ){
    if(not is_marked(pos) and not is_wall(pos))
        map[ pos.roll ][ pos.col ] = 'x';
}

bool Maze::is_marked(const Position& pos){
    return (map[ pos.roll ][ pos.col ] == 'x' or map[pos.roll][pos.col] == '/');
}

void Maze::unmark_cell(const Position& pos ){
    if(is_marked(pos) and not is_wall(pos))
        map[ pos.roll ][ pos.col ] = ' ';
}

bool Maze::is_wall( const Position& pos ){
    return (map[ pos.roll ][ pos.col ] == '#' or map[ pos.roll ][ pos.col ]=='.');
}

void Maze::render(){
    for( auto i( 0ul ); i < m_rolls; i++){
        for(auto j(0ul); j< m_cols; ++j)
            std::cout << map[i][j];

        std::cout << std::endl;
    }
}

