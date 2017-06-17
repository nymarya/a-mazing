#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <deque>
#include "comum.h"

//=== Classe que controla o jogo
class Snake {
    private:
        std::deque < Position > body; //!< Deque de posições que representa a cobra
        char head; //!< Simbolo para a cabeça da cobra

    public:
        //=== Membros especiais
        Snake(char h = '\u142F')
        : head( h )
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