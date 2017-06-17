#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <deque>
#include "comum.h"

//=== Classe que controla o jogo
class Snake {
    public:
        enum class snake_state : int
        {
            RUN = 0,  
            CRASH,      // ( 0,  1) => (1, 0)
            DEAD,       // (-1,  0) => (0, -1)
            WIN,       // ( 1,  0) => (0, 1)
        };

    private:
        std::deque < Position > body; //!< Deque de posições que representa a cobra
        std::string head; //!< Simbolo para a cabeça da cobra

        snake_state state;

    public:
        //=== Membros especiais
        Snake(std::string h = "\u142F")
        : head( h )
        , state( snake_state::RUN )
        {/*empty*/}

        /**
         * @brief      Atualiza o corpo da cobra
         *
         * @param[in]  new_pos Posição para a qual a cabeça da cobra irá mover
         */
        void move(Position new_pos);

        /**
         * @brief      Atualiza símbolo da cabeça da cobra
         *
         * @param[in]  dir Simbolo que representa a direção da cabeça
         */
        void set_head( char dir);

        /**
         * @brief      Atualiza o tamanho da cobra
         *
         * @param[in]  new_pos Posição que será adicionada à cobra
         */
        void grow(Position new_pos);
};
#endif