#include "snake.h"

Position Snake::get_position( void) 
{
    return body.front();
}

/// 
void Snake::move( Position pos)
{
    //!< Retira a cauda
    body.pop_back();

    //!< Cobra vai para a frente
    body.push_front(pos);
}

/// Recupera simbolo da cabeça da cobra
std::string Snake::get_head() const{
    return head;
}

/// Atualiza a cobra após a maçã ser comida
void Snake::grow( Position pos){
    //!< Quando a cobra comer a maçã, a maçã vira a cabeça da cobra
    body.push_front(pos);
}

/// Consulta o estado da cobra
Snake::SnakeState Snake::get_state( void ) const 
{
    return state;
}

/// Atualiza Atualiza o estado da cobra
void Snake::update_state( Snake::SnakeState new_state)
{
    state = new_state;
}

/// Retorna corpo da cobra
std::deque < Position > Snake::get_body( ) const{
    return body;
}

/// Recupera tamanho da cobra
std::size_t Snake::size() const{
    return body.size();
}