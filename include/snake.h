#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <deque>
#include "comum.h"
#include "level.h"

//=== Classe que controla o jogo
class Snake {
    public:
        enum class SnakeState : int
        {
            RUN = 0,  
            CRASH,      // ( 0,  1) => (1, 0)
            DEAD,       // (-1,  0) => (0, -1)
            WIN,       // ( 1,  0) => (0, 1)
        };

    private:
        std::deque < Position > body; //!< Deque de posições que representa a cobra
        std::string head; //!< Simbolo para a cabeça da cobra

        SnakeState state;
        Level *lvl;

        int m_lifes;

    public:
        //=== Membros especiais
        Snake(std::string h = "\u142F")
        : head( h )
        , state( SnakeState::RUN )
        {/*empty*/}

        /**
         * @brief      Retorna posição atual da cobra
         *
         * @return     Posição onde a cabeça da cobra está
         */
        Position get_position( void );

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
        void set_head( direction_t dir);

        /**
         * @brief      Recupera símbolo da cabeça da cobra
         *
         * @return     Simbolo que representa a direção da cabeça
         */
        std::string get_head() const ;

        /**
         * @brief      Atualiza o tamanho da cobra
         *
         * @param[in]  new_pos Posição que será adicionada à cobra
         */
        void grow(Position new_pos);

        /**
         * @brief      Atualiza o estado da cobra
         *
         * @param[in]  new_state Novo estado
         */
        void update_state( SnakeState new_state);

        /**
         * @brief      Recupera o estado da cobra
         *
         * @return     Estado atual da cobra
         */
        Snake::SnakeState get_state( void ) const;

        std::deque < Position > get_body( ) const;

        /**
         * @brief      Recupera o tamanho da cobra
         *
         * @return     Tamanho atual da cobra
         */
        std::size_t size() const;

        int get_lifes() const;

        void die();
};
#endif