/**
 * @file level.h
 * @authors Gabriel Araújo de Souza e Mayra Dantas de Azevedo
 * @date 21 Junho 2017
 * @brief Arquivo contendo as definições da classe Snake.
 */

#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <deque>
#include "comum.h"
#include "level.h"
#include <algorithm>


//=== Classe que controla o jogo
class Snake
{
    private:
        std::deque < Position > body; //!< Deque de posições que representa a cobra
        std::string head; //!< Simbolo para a cabeça da cobra

        SnakeState state;
        Level *lvl;

        int m_lifes;

    public:
        enum class SnakeState : int
        {
            RUN = 0,  
            CRASH,      // ( 0,  1) => (1, 0)
            DEAD,       // (-1,  0) => (0, -1)
            WIN,       // ( 1,  0) => (0, 1)
        };

        //=== Membros especiais
        Snake(std::string h = "\u142F") : head( h ), state( SnakeState::RUN ), m_lifes( 3 )
        {/*empty*/}

        void bind_level ( Level & l_ );

        /**
         * @brief      Retorna posição atual da cobra
         *
         * @return     Posição onde a cabeça da cobra está
         */
        Position get_position ( void );

        /**
         * @brief      Atualiza o corpo da cobra
         *
         * @param[in]  new_pos Posição para a qual a cabeça da cobra irá mover
         */
        void move ( Position new_pos );

        /**
         * @brief      Atualiza símbolo da cabeça da cobra
         *
         * @param[in]  dir Simbolo que representa a direção da cabeça
         */
        void set_head ( direction_t dir );

        /**
         * @brief      Recupera símbolo da cabeça da cobra
         *
         * @return     Simbolo que representa a direção da cabeça
         */
        std::string get_head () const ;

        /**
         * @brief      Atualiza o tamanho da cobra
         *
         * @param[in]  new_pos Posição que será adicionada à cobra
         */
        void grow ( Position new_pos );

        /**
         * @brief      Atualiza o estado da cobra
         *
         * @param[in]  new_state Novo estado
         */
        void update_state ( SnakeState new_state );

        /**
         * @brief      Recupera o estado da cobra
         *
         * @return     Estado atual da cobra
         */
        Snake::SnakeState get_state ( void ) const;

        /**
         * @brief      Pega o corpo da cobra
         *
         * @return     O corpo da cobra.
         */
        std::deque < Position > get_body ( ) const;

        /**
         * @brief      Recupera o tamanho da cobra
         *
         * @return     Tamanho atual da cobra
         */
        std::size_t size () const;

        /**
         * @brief      Recupera a quantidade de vidas
         *
         * @return     As vidas restantes
         */
        int get_lifes () const;  

        /**
         * @brief      Faz a cobra morrer
         */
        void die ();

        /**
         * @brief      Verifica se em uma posição encontra-se alguma
         *             parte da snake
         *
         * @param[in]  pos   A snake
         *
         * @return     True se snake, False caso contrário.
         */
        bool is_snake ( const Position & pos );

        /**
         * @brief      Seta um novo corpo para a cobra
         *
         * @param      newBody  O novo corpo
         */
        void set_body (  std::deque < Position > & newBody );

        /**
         * @brief      Reseta a posição da cobra
         */
        void reset ()
        {
            body.clear();
        }
        
};

#endif