#ifndef _COMUM_H_
#define _COMUM_H_

#include <iostream>

enum class direction_t : int
{
    NORTH = 0,  // ( 0, -1) => (-1, 0)
    SOUTH,      // ( 0,  1) => (1, 0)
    EAST,       // (-1,  0) => (0, -1)
    WEST,       // ( 1,  0) => (0, 1)
};

// * -> posição inicial
// # -> parede
// . -> parede invisível
// $ -> saída
// x -> já passou e é válido
// / -> já visitou e não é válido
// " " -> não foi visitado

struct Direction{
    std::size_t height; //<! 
    std::size_t weight; //<! 

    Direction( std::size_t h=0, std::size_t w=0)
    :height(h), weight(w)
    {/*empty*/}
};

struct Position{
    size_t roll; //<! linha do mapa 
    size_t col;  //<! coluna do mapa

    Position( size_t r=0, size_t c=0)
    :roll(r), col(c)
    {/*empty*/}

    Position& operator+(Direction dir){
        roll += dir.height;
        col += dir.weight;

        return *this;
    }

    bool operator==( Position rhs)
    {
        return (roll == rhs.roll and col == rhs.col);
    }

};

#endif