/**
 * @file comum.h
 * @authors Gabriel Araújo de Souza e Mayra Dantas de Azevedo
 * @date 21 Junho 2017
 * @brief Arquivo contendo as definições comuns para as classes implementadas.
 */

#ifndef _COMUM_H_
#define _COMUM_H_

#include <iostream>
#include "Vector/vector.h"

/**
 * @brief      Classe para as possíveis direções.
 */
enum class direction_t : int
{
    NORTH = 0,  // ( 0, -1) => (-1, 0)
    WEST,       // ( 1,  0) => (0, 1)
    SOUTH,      // ( 0,  1) => (1, 0)
    EAST,       // (-1,  0) => (0, -1)
    STATIC,     // (0, 0)
    NONE,
};

// * -> posição inicial
// # -> parede
// . -> parede invisível
// $ -> saída
// x -> já passou e é válido
// / -> já visitou e não é válido
// " " -> não foi visitado

/**
 * @brief      Direções a se tomar
 */
struct Direction{
    int height; //<! 
    int weight; //<! 

    Direction( int h=0, int w=0)
    :height(h), weight(w)
    {/*empty*/}
};

/**
 * @brief      define o que é uma posição no mapa
 */
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

    /**
     * @brief      Verifica se duas posições são iguais
     *
     * @param[in]  rhs   A posição a ser comparada
     *
     * @return     True se iguais, False caso contrário
     */
    bool operator==( const Position & rhs)
    {
        return (roll == rhs.roll and col == rhs.col);
    }

    /**
     * @brief      Verifica se duas posições são diferentes
     *
     * @param[in]  rhs   A posição a ser comparada
     *
     * @return     True se diferentes, False caso contrário
     */
    bool operator!=( const Position & rhs )
    {
        return (roll != rhs.roll) or (col != rhs.col);
    }

    /**
     * @brief      Atribui uma posição 
     *
     * @param[in]  rhs   Posição a ser atribuida
     *
     * @return     A nova posição
     */
    Position & operator=( const Position & rhs )
    {
        roll = rhs.roll;
        col = rhs.col;

        return *this;
    }

};

#endif