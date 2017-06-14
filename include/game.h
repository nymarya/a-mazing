#ifndef _GAME_H_
#define _GAME_H_

#include "snake.h"
#include "player.h"
#include "level.h"

//=== Classe que controla o jogo
class Game{

    //=== Membros privados
    private:
        //Snake snake;  //!< Instancia da classe Snake
        //Player player;//!< Instancia da classe Player 
    
    public:

        //=== Public interface 

         /**
          * @brief      Valida a aposta informada pelo jogador
          * @param[in]  filename  Nome do arquivo contendo os níveis
          * @return     Sim, caso o arquivo contenha niveis validos,
          *             não, caso contrário
          */
        bool validate ( std::string filename);

        bool initialize (std::string filename);

        void process() const;

        void update();

        void render();
};


#endif