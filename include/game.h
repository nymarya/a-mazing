#ifndef _GAME_H_
#define _GAME_H_

#include <iostream> //cout
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <thread>    // std::this_thread::sleep_for
#include <chrono>    // std::chrono::seconds
#include "comum.h"
#include "snake.h"
#include "player.h"
#include "level.h"

//=== Classe que controla o jogo
class Game{

    //=== Membros privados
    private:
        Snake snake;  //!< Instancia da classe Snake
        //Player player;//!< Instancia da classe Player 
        Level level; //!< Instancia da classe Level

        unsigned int m_levels; //!< Número de levels
    
    public:

        static const int MIN_SIZE = 1;      //<! Menor valor para linha ou coluna
        static const int MAX_SIZE = 100;     //<! Maior valor para linha ou soluna

        struct Result{
            bool success;
            std::string message;

            Result( bool s=true, std::string m="")
            :success(s), message(m)
            {/*empty*/}
        };

        //=== Public interface 

         /**
          * @brief      Valida a aposta informada pelo jogador
          * @param[in]  filename  Nome do arquivo contendo os níveis
          * @return     Resultado com sucesso, caso o arquivo contenha niveis validos,
          *             erro, caso contrário
          */
        Result validate ( std::string filename);

        /**
         * @brief      Inicializa os elementos do jogo
         * @param[in]  filename  Nome do arquivo contendo os níveis
         *
         */
        void initialize (std::string filename);

        void process_events();

        void update();

        void render();

        bool game_over();

        void teste( std::string file);
};


#endif