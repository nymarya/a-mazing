#ifndef _COMUM_H_
#define _COMUM_H_

#include <iostream>

struct Position{
    int roll; //<! linha do mapa 
    int col;  //<! coluna do mapa
};

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
// " " -> não foi vizitado

struct Direction{
    std::size_t height; //<! 
    std::size_t weight; //<! 

    Direction( std::size_t h=0, std::size_t w=0)
    :height(h), weight(w)
    {/*empty*/}
};

#endif