#ifndef _COMUM_H_
#define _COMUM_H_

#include <iostream>
#include "Vector/vector.h"


enum class direction_t : int
{
    NORTH = 0,  // ( 0, -1) => (-1, 0)
    SOUTH,      // ( 0,  1) => (1, 0)
    EAST,       // (-1,  0) => (0, -1)
    WEST,       // ( 1,  0) => (0, 1)
    STATIC,     //(0, 0)
    NONE,
};

// * -> posição inicial
// # -> parede
// . -> parede invisível
// $ -> saída
// x -> já passou e é válido
// / -> já visitou e não é válido
// " " -> não foi visitado

struct Direction{
    int height; //<! 
    int weight; //<! 

    Direction( int h=0, int w=0)
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
    bool operator!=( const Position & rhs )
    {
        return (roll != rhs.roll) or (col != rhs.col);
    }

};

#endif