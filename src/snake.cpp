#include "snake.h"

/// 
void Snake::move( Position pos){
    //!< Retira a cauda
    body.pop_back();

    //!< Cobra vai para a frente
    body.push_front(pos);
}

/// Atualiza a cobra após a maçã ser comida
void Snake::grow( Position pos){
    //!< Quando a cobra comer a maçã, a maçã vira a cabeça da cobra
    body.push_front(pos);
}