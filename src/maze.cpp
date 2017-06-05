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

        //Guarda os simbolos
        while(file.get() != EOF){
            std::string s;
            file.unget();
            s.push_back( file.get() );
            map.push_back( s );          
        }
    }
}

void Maze::render(){

    for( auto i( map.begin() ); i != map.end(); ){
        std::cout << *i++;
    }
}